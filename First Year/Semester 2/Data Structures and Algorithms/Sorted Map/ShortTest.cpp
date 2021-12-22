#include <assert.h>

#include "SortedMap.h"
#include "SMIterator.h"
#include "ShortTest.h"
#include <exception>
using namespace std;

bool relatie1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedMap sm(relatie1);
	assert(sm.size() == 0);
	assert(sm.isEmpty());
    sm.add(1,2);
    assert(sm.size() == 1);
    assert(!sm.isEmpty());
    assert(sm.search(1)!=NULL_TVALUE);
    TValue v =sm.add(1,3);
    assert(v == 2);
    assert(sm.search(1) == 3);
    SMIterator it = sm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	assert(e.second != NULL_TVALUE);
    	it.next();
    }
    sm.replace(1, 3, 5);
    assert(sm.remove(1) == 5);
    sm.add(2, 10);
    assert(sm.search(2) == 10);
    sm.replace(2, 15, 20);
    assert(sm.search(2) == 10);
    sm.remove(2);
    assert(sm.search(100) == NULL_TVALUE);
    sm.replace(100, 5, 20);
    assert(sm.search(100) == NULL_TVALUE);
    assert(sm.isEmpty());
}

