#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
	this->current = 0;

}
//Theta(1)

void SMIterator::first(){
	this->current = 0;
}
//Theta(1)

void SMIterator::next(){
	if (this->current == this->map.nrPairs) {
	    throw exception();
	} else {
	    this->current++;
	}
}
//Theta(1)

bool SMIterator::valid() const{
	if (this->current < this->map.nrPairs) {
        return true;
	}
	return false;
}
//Theta(1)

TElem SMIterator::getCurrent() const{
	if (this->current == this->map.nrPairs) {
	    throw exception();
	}
    return this->map.elements[this->current];
}
//Theta(1)


