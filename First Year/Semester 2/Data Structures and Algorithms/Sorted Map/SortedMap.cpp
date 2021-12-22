#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
using namespace std;

SortedMap::SortedMap(Relation r) {
    this->nrPairs = 0;
    this->rel= r;
    this->capacity = 1;
    this->elements = new TElem[this->capacity];
}
//Theta(1)

void SortedMap::resize() {
    int index;
    auto * newElems = new TElem[this->capacity * 2];
    for (index = 0; index < this->nrPairs; index++) {
        newElems[index] = this->elements[index];
    }
    delete[] this->elements;
    this->elements = newElems;
    this->capacity *= 2;
}
//Theta(nrPairs)

TValue SortedMap::add(TKey k, TValue v) {
    TValue returned = NULL_TVALUE;
    int index;
    if (this->capacity == this->nrPairs) {
        this->resize();
    }
    bool found = false;
    index = 0;
    while (!found && index < this->nrPairs && this->rel(this->elements[index].first, k)) {
        if (this->elements[index].first == k) {
            found = true;
            returned = this->elements[index].second;
            this->elements[index].second = v;
        }
        else
            index++;
    }
    if (!found) {
        if (this->nrPairs > 0){
            for(int i = this->nrPairs; i>index; i--)
                this->elements[i] = this->elements[i - 1];
        }
        this->elements[index].first = k;
        this->elements[index].second = v;
        this->nrPairs++;
    }
    return returned;
}//Best case: Theta(1), worst case: Theta(nrPairs) -> Total complexity: O(nrPairs)

TValue SortedMap::search(TKey k) const {
    TValue returned = NULL_TVALUE;
    bool found = false;
    int index = 0;
    while (!found && index < this->nrPairs && this->rel(this->elements[index].first, k)) {
        if (this->elements[index].first == k) {
            found = true;
            returned = this->elements[index].second;
        }else
            index++;
    }
    return returned;
}//Best case: Theta(1), worst case: Theta(nrPairs) -> Total complexity: O(nrPairs)

TValue SortedMap::remove(TKey k) {
	int index = 0;
	bool found = false;
	TValue returned = NULL_TVALUE;
	while (index<this->nrPairs && !found && this->rel(this->elements[index].first, k)) {
	    if (this->elements[index].first == k) {
	        returned = this->elements[index].second;
	        found = true;
	    }else
	        index++;
	}
    if (found) {
        for (int i = index; i < this->nrPairs - 1; i++)
            this->elements[i] = this->elements[i+1];
        this->nrPairs--;
    }
    return returned;
}//Best case: Theta(nrPairs), worst case: Theta(nrPairs) -> Total complexity: Theta(nrPairs)

void SortedMap::replace(TKey k, TValue oldValue, TValue newValue) {
    int index = 0;
    bool found = false;
    while (index < this->nrPairs && !found && this->rel(this->elements[index].first, k)) {
        if (this->elements[index].first == k) {
            found = true;
            if (this->elements[index].second == oldValue)
                this->elements[index].second = newValue;
        }else
            index++;
    }
}
//Best case: Theta(1), worst case: Theta(nrPairs) -> Total complexity: O(nrPairs)

int SortedMap::size() const {
    return this->nrPairs;
}
//Theta(1)

bool SortedMap::isEmpty() const {
	if (this->nrPairs == 0) {
        return true;
	}
	return false;
}
//Theta(1)

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}
//Theta(1)

SortedMap::~SortedMap() {
	delete[] this->elements;
}
//Theta(1)
