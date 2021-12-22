#ifndef LIST_H
#define LIST_H


//generic data type (integer, for now)
typedef int TElem;

//reference to the Node structure
struct Node;

//define PNode as the address of another node
typedef Node* PNode;

struct Node{
    TElem elem;
    PNode next;
};

typedef struct{
//first is the address of the first node in the list
	PNode first;
} List;

//INTERFACE - operations on the list

//creation of a list with values read from the user until 0 is given
List create();

//print the elements of a list
void printList(List list);

// the destructor for a list
void destroy(List list);

bool testInclusion(List list1, List list2);

bool compare(List list1, List list2);

bool searchElement(List list, int value);

List eliminateElement(List list, int value);

bool isSet(List list);

#endif
