#include <exception>
#include <assert.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include "SortedMap.h"
#include "SMIterator.h"
#include "ExtendedTest.h"

using namespace std;

bool increasing(TKey c1, TKey c2) {
	if (c1 <= c2) {
		return true;
	} else {
		return false;
	}
}

bool decreasing(TKey c1, TKey c2) {
	if (c1 >= c2) {
		return true;
	} else {
		return false;
	}
}

void testIteratorSteps(SortedMap& m, Relation r) {
	SMIterator li = m.iterator();
	TElem elem = NULL_TPAIR;
	int count = 0;
	if (li.valid()) {
		elem = li.getCurrent();
		count++;
		li.next();
	}
	while (li.valid()) {
		TElem elem2 = li.getCurrent();
		assert(r(elem.first, elem2.first) == true);
		elem = elem2;
		count++;
		li.next();
	}
	assert(count == m.size());
}

void testCreate() {
	cout << "Test create" << endl;
	SortedMap sm(increasing);
	assert(sm.size() == 0);
	assert(sm.isEmpty());

	SMIterator it = sm.iterator();
	it.first();
	assert(!it.valid());
	try {
		it.next();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		it.getCurrent();
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}

	for (int i = 0; i < 10; i++) {
		assert(sm.search(i) == NULL_TVALUE);
	}

	for (int i = -10; i < 10; i++) {
		assert(sm.remove(i) == NULL_TVALUE);
	}
}

void testSearch(Relation r) {
	cout << "Test search" << endl;
	SortedMap sm(r);
	int cMin = 0;
	int cMax = 10;
	try {
		for (int i = cMin; i <= cMax; i++) {
			sm.add(i, i + 1);
		}
		assert(true);
	} catch (exception&) {
		assert(false);
	}
	int intervalDim = 10;
	for (int i = cMin; i <= cMax; i++) {
		assert(sm.search(i) == i + 1);
	}
	testIteratorSteps(sm, r);
	for (int i = cMin - intervalDim; i < cMin; i++) {
		assert(sm.search(i) == NULL_TVALUE);
	}
	for (int i = cMax + 1; i < cMax + intervalDim; i++) {
		assert(sm.search(i) == NULL_TVALUE);
	}
}

void testSearch() {
	testSearch(increasing);
	testSearch(decreasing);
}

vector<int> keysInRandomOrder(int cMin, int cMax) {
	vector<int> keys;
	for (int c = cMin; c <= cMax; c++) {
		keys.push_back(c);
	}
	int n = keys.size();
	for (int i = 0; i < n - 1; i++) {
		int j = i + rand() % (n - i);
		swap(keys[i], keys[j]);
	}
	return keys;
}

void populateSMEmpty(SortedMap& sm, int cMin, int cMax) {
	vector<int> keys = keysInRandomOrder(cMin, cMax);
	int n = keys.size();
	for (int i = 0; i < n; i++) {
		assert(sm.add(keys[i], keys[i]) == NULL_TVALUE);
	}
}

void rePopulateSMShift(SortedMap& sm, int cMin, int cMax, int shift) {
	vector<int> keys = keysInRandomOrder(cMin, cMax);
	int n = keys.size();
	for (int i = 0; i < n; i++) {
		assert(sm.add(keys[i], keys[i] - shift) == keys[i]);
	}
}

void populateSMShift(SortedMap& sm, int cMin, int cMax, int shift) {
	vector<int> keys = keysInRandomOrder(cMin, cMax);
	int n = keys.size();
	for (int i = 0; i < n; i++) {
		sm.add(keys[i], keys[i] - shift);
	}
}

void testAddAndSearch(Relation r) {
	cout << "Test add and search" << endl;
	SortedMap sm(r);
	int cMin = 100;
	int cMax = 200;

	populateSMEmpty(sm, cMin, cMax);
	testIteratorSteps(sm, r);
	for (int c = cMin; c <= cMax; c++) {
		assert(sm.search(c) == c);
	}
	assert(sm.size() == (cMax - cMin + 1));

	rePopulateSMShift(sm, cMin, cMax, 1);
	assert(sm.size() == (cMax - cMin + 1));
	testIteratorSteps(sm, r);
	populateSMShift(sm, 2 * cMax, 3 * cMax, 2 * cMax - cMin);
	for (int c = 2 * cMax; c <= 3 * cMax; c++) {
		assert(sm.search(c) == c - 2 * cMax + cMin);
	}
	testIteratorSteps(sm, r);
	assert(sm.size() == (cMax - cMin + 1) + (cMax + 1));

	SMIterator it = sm.iterator();
	it.first();
	if (it.valid()) {
		TKey cPrec = it.getCurrent().first;
		assert(sm.search(cPrec) != NULL_TVALUE);
		it.next();
		while (it.valid()) {
			TKey c = it.getCurrent().first;
			assert(r(cPrec, c));
			assert(sm.search(c) != NULL_TVALUE);
			cPrec = c;
			it.next();
		}
	}

}

void testAdd() {
	testAddAndSearch(increasing);
	testAddAndSearch(decreasing);
}

void testRemoveAndSearch(Relation r) {
	cout << "Test remove and search" << endl;
	SortedMap sm(r);
	int cMin = 10;
	int cMax = 20;
	populateSMEmpty(sm, cMin, cMax);
	testIteratorSteps(sm, r);
	for (int c = cMax + 1; c <= 2 * cMax; c++) {
		assert(sm.remove(c) == NULL_TVALUE);
		testIteratorSteps(sm, r);
	}
	int dim = cMax - cMin + 1;
	assert(sm.size() == dim);
	for (int c = cMin; c <= cMax; c++) {
		assert(sm.remove(c) == c);
		assert(sm.search(c) == NULL_TVALUE);

		SMIterator it = sm.iterator();
		it.first();
		if (it.valid()) {
			TKey cPrec = it.getCurrent().first;
			it.next();
			while (it.valid()) {
				TKey c = it.getCurrent().first;
				assert(r(cPrec, c));
				cPrec = c;
				it.next();
			}
		}

		dim--;
		assert(sm.size() == dim);

	}

	for (int c = cMin; c <= cMax; c++) {
		assert(sm.remove(c) == NULL_TVALUE);
	}
	assert(sm.isEmpty());
	assert(sm.size() == 0);

}

void testRemove() {
	testRemoveAndSearch(increasing);
	testRemoveAndSearch(decreasing);
}

void testIterator(Relation r) {
	cout << "Test iterator" << endl;
	SortedMap sm(r);
	SMIterator it = sm.iterator();
	assert(!it.valid());
	it.first();
	assert(!it.valid());
	int cMin = 100;
	int cMax = 300;
	vector<int> keys = keysInRandomOrder(cMin, cMax);
	int n = keys.size();
	for (int i = 0; i < n; i++) {
		assert(sm.add(keys[i], keys[n - i - 1]) == NULL_TVALUE);
	}

	SMIterator itSM = sm.iterator();
	assert(itSM.valid());
	itSM.first();
	assert(itSM.valid());

	TKey cPrec = itSM.getCurrent().first;
	for (int i=1; i<100; i++){
		assert(cPrec == itSM.getCurrent().first);
	}
    itSM.next();
	while (itSM.valid()) {
		TKey c = itSM.getCurrent().first;
		assert(cMin <= c && c <= cMax);
		assert(sm.search(c) != NULL_TVALUE);
		assert(r(cPrec, c));
		cPrec = c;
		itSM.next();
	}
}

void testQuantity(){
	cout << "Test quantity" << endl;
	SortedMap sm(increasing);
	int cMin = -3000;
	int cMax = 3000;
	vector<int> keys  = keysInRandomOrder(cMin, cMax);
    populateSMEmpty(sm, cMin, cMax);
    for (int c = cMin; c <= cMax; c++){
      	assert(sm.search(c) == c);
    }
	testIteratorSteps(sm, increasing);
    assert(sm.size() == cMax - cMin + 1);
    SMIterator it  = sm.iterator();
    assert(it.valid());
    it.first();
    assert(it.valid());
    for (int i = 0; i < sm.size(); i++) {
    	it.next();
    }
    assert(!it.valid());
    it.first();
    while (it.valid()){
    	TKey c = it.getCurrent().first;
    	assert(sm.search(c) == c);
        TValue v  = it.getCurrent().second;
        assert(c == v);
        it.next();
    }
    assert(!it.valid());
    for (int c = cMin-100; c <= cMax+100; c++){
         sm.remove(c);
         assert(sm.search(c) == NULL_TVALUE);	
		 testIteratorSteps(sm, increasing);
    }
    assert(sm.size() == 0);
    assert(sm.isEmpty());
}

void testIterator() {
	testIterator(increasing);
	testIterator(decreasing);
}

void testAllExtended() {
	testCreate();
	testAdd();
	testSearch();
	testRemove();
	testIterator();
	testQuantity();
}
