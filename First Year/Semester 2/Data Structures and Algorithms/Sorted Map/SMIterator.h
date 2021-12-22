#pragma once
#include "SortedMap.h"

//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	SMIterator(const SortedMap& mapionar);
	int current; // the position of the current element from the elements array from the map
public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

