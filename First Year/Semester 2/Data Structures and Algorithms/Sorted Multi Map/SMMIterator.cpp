#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	BSTNode* startNode = d.root;
    this->current = 0;
    this->inOrderRecursive(startNode);
}
//Theta(nrNodes)

void SMMIterator::first(){
    this->current = 0;
}
//Theta(1)

void SMMIterator::next(){
	if (!valid()) {
        throw std::exception();
	}
    this->current++;
}
//Theta(1)

bool SMMIterator::valid() const{
	if (this->current >= this->stack.getNrElements()) {
        return false;
	}
    return true;
}
//Theta(1)

TElem SMMIterator::getCurrent() const{
	if (!valid()) {
	    throw std::exception();
	}
    return this->stack[this->current];
}
//Theta(1)

void SMMIterator::inOrderRecursive(BSTNode *startNode) {
    if (startNode != nullptr) {
        this->inOrderRecursive(startNode->left);
        this->stack.push(startNode);
        this->inOrderRecursive(startNode->right);
    }
}
//Theta(nrNodes)

Stack::Stack(): nrElements{0}, capacity{10} {
    this->elements = new BSTNode*[capacity];
}
//Theta(1)

int Stack::getNrElements() const {
    return this->nrElements;
}
//Theta(1)

int Stack::getCapacity() const {
    return this->capacity;
}
//Theta(1)

void Stack::push(BSTNode *element) {
    if (this->nrElements == this->capacity)
        this->resize();
    this->elements[this->nrElements] = element;
    this->nrElements++;
}
//Theta(1) amortized

void Stack::resize() {
    auto** newElements = new BSTNode*[this->capacity * 2];
    int index;
    for (index = 0; index < this->nrElements; ++index) {
        newElements[index] = this->elements[index];
    }
    this->capacity = this->capacity * 2;
    delete [] this->elements;
    this->elements = newElements;
}
//Theta(nrElements)

BSTNode *Stack::pop() {
    this->nrElements--;
    return this->elements[this->nrElements];
}
//Theta(1)

TElem Stack::operator[](int position) const {
    return this->elements[position]->info;
}
//Theta(1)

Stack::~Stack() {
    delete [] this->elements;
}
//Theta(1)
