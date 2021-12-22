#pragma once
#include "Map.h"
class MapIterator
{
	//DO NOT CHANGE THIS PART
	friend class Map;
private:
	const Map& map;
	int currentElement;
	int firstElement;

	MapIterator(const Map& m);
public:
	void first();
	void previous();
	void next();
	TElem getCurrent();
	bool valid() const;
};


