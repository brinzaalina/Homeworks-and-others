#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

void testExtra() {
    SortedBag sb(relation1);
    sb.add(5);
    sb.add(6);
    sb.add(0);
    sb.add(5);
    sb.add(10);
    sb.add(8);
    sb.add(10);
    assert(sb.size() == 7);

    SortedBag b(relation1);
    b.add(5);
    b.add(6);
    b.add(0);
    b.add(2);
    assert(b.size() == 4);
    Node* node = b.getNode(6);
    assert(node->info.second == 1);
    assert(b.getNode(1) == nullptr);

    sb.intersection(b);
    assert(sb.nrOccurrences(5) == 1);
    assert(sb.search(10) == false);
    assert(sb.search(8) == false);
    assert(sb.size() == 3);
}

