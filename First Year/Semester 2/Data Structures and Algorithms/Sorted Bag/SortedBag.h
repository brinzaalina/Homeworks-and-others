#pragma once
//DO NOT INCLUDE SORTEDBAGITERATOR

#include <utility>

//DO NOT CHANGE THIS PART
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;
struct Node {
    std::pair<TComp, int> info;
    Node* prev;
    Node* next;
};

class SortedBag {
	friend class SortedBagIterator;

private:
	Relation relation;
	Node* head;
	Node* tail;
	int length;

public:
	//constructor
	SortedBag(Relation r);

	//adds an element to the sorted bag
	void add(TComp e);

	//removes one occurrence of an element from a sorted bag
	//returns true if an element was removed, false otherwise (if e was not part of the sorted bag)
	bool remove(TComp e);

	//checks if an element appears is the sorted bag
	bool search(TComp e) const;

	//returns the number of occurrences for an element in the sorted bag
	int nrOccurrences(TComp e) const;

	//returns the number of elements from the sorted bag
	int size() const;

	//returns an iterator for this sorted bag
	SortedBagIterator iterator() const;

	//checks if the sorted bag is empty
	bool isEmpty() const;

	//returns the node that contains the element if it appears in the sorted bag
    Node * getNode(TComp elem) const;

    //keeps only the elements which appear in b as well
    //if an element appears multiple times in both SortedBags, it will be kept multiple times
    // (if it appears 3 times in one SortedBag and 5 times in the other, 3 occurrences will be kept)
    //Obs: Assume the two  Bags have the same relation
    void intersection(const SortedBag& b);


    //destructor
	~SortedBag();
};