#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d)
{
    this->currentElement = 0;
    while (this->currentElement < this->map.m && (this->map.elems[this->currentElement] == NULL_TELEM))
        this->currentElement++;
    this->firstElement = this->currentElement;
}
//BC: Theta(1), WC: Theta(capacity) -> Total complexity: O(capacity)

void MapIterator::first() {
    this->currentElement = 0;
    while (this->currentElement < this->map.m && (this->map.elems[this->currentElement] == NULL_TELEM))
        this->currentElement++;
    this->firstElement = currentElement;
}
//BC: Theta(1), WC: Theta(capacity) -> Total complexity: O(capacity)
//I added the firstElement attribute when I implemented the previous() function and after this the first() function
//can be simplified, setting only currentElement to be the firstElement; in this case, the total complexity: Theta(1)

void MapIterator::previous() {
    if (!this->valid())
        throw exception();
    if (this->currentElement == this->firstElement)
        this->currentElement = this->map.m;
    else {
        this->currentElement--;
        while ((this->map.elems[this->currentElement] == NULL_TELEM) && this->currentElement != this->firstElement)
            this->currentElement--;
    }
}
//BC:Theta(1), WC: Theta(capacity) -> Total complexity: O(capacity)

void MapIterator::next() {
	if (this->currentElement >= this->map.m)
        throw exception();
    this->currentElement++;
    while (this->currentElement < this->map.m && (this->map.elems[this->currentElement] == NULL_TELEM))
        this->currentElement++;
}
//BC: Theta(1), WC: Theta(capacity) -> Total complexity: O(capacity)

TElem MapIterator::getCurrent(){
	if (this->currentElement >= this->map.m)
	    throw exception();
	return this->map.elems[this->currentElement];
}
//Theta(1)

bool MapIterator::valid() const {
	if(this->currentElement < this->map.m)
        return true;
	return false;
}
//Theta(1)



