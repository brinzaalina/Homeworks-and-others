#include "PriorityQueue.h"
#include "ShortTest.h"
#include <assert.h>

bool rel(TPriority p1, TPriority p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll() { //call each function and see if it exists
	PriorityQueue pq(rel);
	
	assert(pq.isEmpty() == true);
	
	//adaugam 5, 3, 10, 2, 12 -> rezultat: 2, 3, 5, 10, 12
	pq.push(5, 5);
	assert(pq.top().first == 5);
	assert(pq.top().second == 5);
    assert(pq.priorityOf(5) == 5);
	pq.push(3, 3);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(10, 10);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(2, 2);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	pq.push(12, 12);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	assert(pq.isEmpty() == false);
	assert(pq.pop().second == 2);
	assert(pq.top().second == 3);
	assert(pq.pop().second == 3);
	assert(pq.top().second == 5);
	assert(pq.pop().second == 5);
	assert(pq.top().second == 10);
	assert(pq.pop().second == 10);
	assert(pq.top().second == 12);
	assert(pq.pop().second == 12);
	assert(pq.isEmpty() == true);
    pq.push(5, 3);
    pq.push(5, 5);
    assert(pq.priorityOf(5) == 3);
    assert(pq.priorityOf(3) == -1);
    pq.pop();
    pq.pop();
    assert(pq.isEmpty() == true);
}

