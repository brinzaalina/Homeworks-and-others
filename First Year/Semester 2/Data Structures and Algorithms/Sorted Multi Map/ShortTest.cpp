#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>

using namespace std;

bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

TValue transformer(TKey key, TValue value) {
    TValue newValue = (value + 10) % 7;
    return  newValue;
}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());

    smm.add(1,2);
    smm.add(2,3);
    assert(smm.size() == 2);
    vector<TValue> values = smm.search(1);
    assert(values.size() == 1);
    assert(values[0] == 2);
    smm.replaceAll(transformer);
    values = smm.search(1);
    assert(values.size() == 1);
    assert(values[0] == 5);
    values = smm.search(2);
    assert(values.size() == 1);
    assert(values[0] == 6);
}

