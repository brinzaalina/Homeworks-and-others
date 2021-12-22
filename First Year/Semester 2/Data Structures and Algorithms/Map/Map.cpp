#include <cmath>
#include "Map.h"
#include "MapIterator.h"

int Map::hash(TKey c) const {
    return abs(c) % this->m;
}

Map::Map() {
    this->m = 13;
    this->length = 0;
    this->elems = new TElem[this->m];
    this->next = new int[this->m];
    int index;
    for(index = 0; index < this->m; index++) {
        this->elems[index] = NULL_TELEM;
        this->next[index] = -1;
    }
    this->firstEmpty = 0;

}
//Theta(capacity)

Map::~Map() {
	delete[] this->next;
	delete[] this->elems;
}
//Theta(1)

void Map::resizeAndRehash() {
    int currentLength = this->length;
    int currentM = this->m;
    this->m = this->m * 2;
    int index;
    auto oldElements = new TElem[currentM];
    for(index = 0; index < currentM; index++) {
        oldElements[index] = this->elems[index];
    }

    delete[] this->elems;
    this->elems = new TElem[this->m];
    delete[] this->next;
    this->next = new int[this->m];

    for(index = 0; index < this->m; index++) {
        this->elems[index] = NULL_TELEM;
        this->next[index] = -1;
    }
    this->firstEmpty = 0;
    for(index = 0; index < currentM; index++) {
        if (oldElements[index] != NULL_TELEM)
            add(oldElements[index].first, oldElements[index].second);
    }
    this->length = currentLength;

    delete[] oldElements;
}
//BC: Theta(newCapacity), WC: Theta(newCapacity * nrElems) -> Total complexity: O(newCapacity * nrElems)

void Map::changeFirstEmpty() {
    this->firstEmpty = this->firstEmpty + 1;
    while(this->firstEmpty < this->m && this->elems[this->firstEmpty] != NULL_TELEM)
        this->firstEmpty = this->firstEmpty + 1;
}
//BC: Theta(1), WC: Theta(capacity) -> Total complexity: O(capacity)

TValue Map::add(TKey c, TValue v){
    TValue returnValue = NULL_TVALUE;
    TElem element;
    element.first = c;
    element.second = v;
	int hashValue = this->hash(c);
	if (this->elems[hashValue] == NULL_TELEM) {
	    if(hashValue == firstEmpty)
            this->changeFirstEmpty();
        this->elems[hashValue] = element;
        this->next[hashValue] = -1;
        this->length++;
	} else {
        if(this->firstEmpty == this->m)
            this->resizeAndRehash();
        int currentPosition = hashValue;
        while (this->next[currentPosition] != -1 && this->elems[currentPosition].first != c) {
            currentPosition = this->next[currentPosition];
        }
        if (this->elems[currentPosition].first == c) {
            returnValue = this->elems[currentPosition].second;
            this->elems[currentPosition].second = v;
        } else if (this->next[currentPosition] == -1) {
            this->elems[this->firstEmpty] = element;
            this->next[this->firstEmpty] = -1;
            this->next[currentPosition] = this->firstEmpty;
            this->changeFirstEmpty();
            this->length++;
        }
	}
	return returnValue;
}
//BC: Theta(1), WC: Theta(nrElements) amortized-> Total complexity: O(nrElements)

TValue Map::search(TKey c) const{
    TValue returnValue = NULL_TVALUE;
    int currentPosition = this->hash(c);
    while (this->next[currentPosition] != -1 && this->elems[currentPosition].first != c) {
        currentPosition = this->next[currentPosition];
    }
    if (this->elems[currentPosition].first == c) {
        returnValue = this->elems[currentPosition].second;
    }
	return returnValue;
}
//BC: Theta(1), WC: Theta(nrElements) -> Total complexity: O(nrElements)

TValue Map::remove(TKey c){
	TValue returnValue = NULL_TVALUE;
	int current = this->hash(c);
	int prev = -1;
	while (current != -1 && this->elems[current].first != c) {
	    prev = current;
	    current = this->next[current];
	}

	if (current == -1) {
        returnValue = NULL_TVALUE;
	} else{
	    returnValue = this->elems[current].second;
	    bool over = false;
	    do {
	        int position = this->next[current];
	        int prevPosition = current;
	        while (position != -1 && this->hash(this->elems[position].first) != current) {
                prevPosition = position;
	            position = this->next[position];
	        }
	        if (position == -1)
	            over = true;
	        else {
                this->elems[current] = this->elems[position];
                prev = prevPosition;
                current = position;
	        }
	    } while (!over);
	    if (prev == -1) {
	        int idx = 0;
	        while (idx < this->m && prev == -1)
	            if (this->next[idx] == current) {
                    prev = idx;
                }else {
                    idx = idx + 1;
                }
	    }
	    if (prev != -1)
            this->next[prev] = this->next[current];
        this->length--;
        this->elems[current] = NULL_TELEM;
        this->next[current] = -1;
        if (this->firstEmpty > current)
            this->firstEmpty = current;
	}
    return returnValue;
}
//BC: Theta(capacity), WC: Theta(NrElems^2)-> Total Complexity: O(nrElems^2)

int Map::size() const {
	return this->length;
}
//Theta(1)

bool Map::isEmpty() const{
	if (this->length == 0)
        return true;
	return false;
}
//Theta(1)

MapIterator Map::iterator() const {
	return MapIterator(*this);
}
//Theta(!)


