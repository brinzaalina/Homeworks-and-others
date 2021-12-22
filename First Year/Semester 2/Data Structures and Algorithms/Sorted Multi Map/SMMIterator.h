#pragma once

#include "SortedMultiMap.h"
class Stack {
private:
    BSTNode** elements;
    int nrElements;
    int capacity;
public:
    Stack();
    int getNrElements() const;
    int getCapacity() const;
    void push(BSTNode* element);
    void resize();
    BSTNode* pop();
    TElem operator[](int position) const;
    ~Stack();
};

class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);
    Stack stack{};
    int current;

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
   	void inOrderRecursive(BSTNode* startNode);
};

