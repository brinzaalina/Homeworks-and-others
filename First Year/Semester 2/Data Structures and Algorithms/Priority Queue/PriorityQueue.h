#pragma once
#include <vector>
#include <utility>

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

struct Node {
    Element info;
    int next;
    int prev;
};

class PriorityQueue {
private:
    Relation rel;
	Node* nodes;
	int capacity;
	int head;
	int tail;
	int size;
	int firstEmpty;
    void resize();
public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top() const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

    //returns the priority of elem.
    // If elem appears multiple times the priority of one of them should be returned.
    //if elem is not in the PriorityQueue, return -1.
    TPriority priorityOf(TElem elem) const;

    //destructor
	~PriorityQueue();

};