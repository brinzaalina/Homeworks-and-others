
#include "PriorityQueue.h"
#include <exception>
using namespace std;


PriorityQueue::PriorityQueue(Relation r) {
    this->rel = r;
    this->capacity = 10;
    this->head = -1;
	this->tail = -1;
    this->firstEmpty = 0;
	this->nodes = new Node[capacity];
	for(int i = 0; i < capacity - 1; i++) {
	    nodes[i].next = i+1;
	}
	nodes[capacity - 1].next = -1;
	this->size = 0;
}
//Theta(capacity)

void PriorityQueue::resize() {
	Node* newNodes = new Node[this->capacity * 2];
	int index;
	for (index = 0; index < this->capacity; index++) {
	    newNodes[index] = this->nodes[index];
	}
	for(index = this->capacity; index < this->capacity * 2 -1; index++) {
	    newNodes[index].next = index + 1;
	}
    this->firstEmpty = this->capacity;
    this->capacity *= 2;
    newNodes[this->capacity - 1].next = -1;
    delete[] this->nodes;
    this->nodes = newNodes;
}
//Theta(capacity)

void PriorityQueue::push(TElem e, TPriority p) {
	if (this->size == this->capacity)
        this->resize();
	int newNode = this->firstEmpty;
    this->firstEmpty = this->nodes[firstEmpty].next;
    this->size++;
    if (this->tail == -1) {
        this->nodes[newNode].info.first = e;
        this->nodes[newNode].info.second = p;
        this->nodes[newNode].next = -1;
        this->head = newNode;
        this->tail = newNode;
    } else {
        this->nodes[tail].next = newNode;
        this->nodes[newNode].prev = tail;
        this->nodes[newNode].info.first = e;
        this->nodes[newNode].info.second = p;
        this->nodes[newNode].next = -1;
        this->tail = newNode;
    }
}
//Theta(1) amortized

//throws exception if the queue is empty
Element PriorityQueue::top() const {
	if (this->size == 0)
		throw exception();
	int current = this->head;
     Element elem = this->nodes[this->head].info;
    while (current != this->nodes[this->tail].next) {
        if(this->rel(this->nodes[current].info.second, elem.second)) {
            elem.first = this->nodes[current].info.first;
            elem.second = this->nodes[current].info.second;
        }
        current = this->nodes[current].next;
    }
	return elem;
}
//Theta(size)

Element PriorityQueue::pop() {
	if (this->size == 0) {
        throw exception();
    } else {
        int current = this->head;
        Element topValue = top();
        while (current != this->nodes[this->tail].next && !(this->nodes[current].info.first == topValue.first &&
               this->nodes[current].info.second == topValue.second)) {
            current = this->nodes[current].next;
        }
        Element ret;
        if (current == this->head) {
            ret.first = this->nodes[this->head].info.first;
            ret.second = this->nodes[this->head].info.second;
            if (this->size == 1) {
                this->head = -1;
                this->tail = -1;
                this->nodes[current].next = this->firstEmpty;
                this->firstEmpty = current;
            } else {
                this->head = this->nodes[current].next;
                this->nodes[this->head].prev = -1;
                this->nodes[current].next = this->firstEmpty;
                this->firstEmpty = current;
            }
            this->size--;
        } else if (current == this->tail) {
            ret.first = this->nodes[this->tail].info.first;
            ret.second = this->nodes[this->tail].info.second;
            this->tail = this->nodes[current].prev;
            this->nodes[this->tail].next = -1;
            this->nodes[current].next = this->firstEmpty;
            this->firstEmpty = current;
            this->size--;
        } else if (current != this->nodes[this->tail].next) {
            ret.first = this->nodes[current].info.first;
            ret.second = this->nodes[current].info.second;
            this->nodes[this->nodes[current].prev].next = this->nodes[current].next;
            this->nodes[this->nodes[current].next].prev = this->nodes[current].prev;
            this->nodes[current].next = this->firstEmpty;
            this->firstEmpty = current;
            this->size--;
        }
        return ret;
    }
}
//O(size)

bool PriorityQueue::isEmpty() const {
	if (this->size == 0)
		return true;
	return false;
}

TPriority PriorityQueue::priorityOf(TElem elem) const {
    if (this->size == 0)
        throw exception();
    TPriority return_value = -1;
    int current_node = this->head;
    while (current_node != this->nodes[this->tail].next && this->nodes[current_node].info.first != elem) {
        current_node = this->nodes[current_node].next;
    }
    if (current_node != this->nodes[this->tail].next)
        return_value = this->nodes[current_node].info.second;
    return return_value;
}
//BC: Theta(1), WC: Theta(size) => Total complexity: O(size)

PriorityQueue::~PriorityQueue() {
	delete[] this->nodes;
}



