#include "list.h"
#include <iostream>

PNode recursiveCreate(){
    TElem element;
    std::cout << "element=";
    std::cin >> element;
    if (element == 0)
        return nullptr;
    else {
        auto pNode = new Node();
        pNode->elem = element;
        pNode->next = recursiveCreate();
        return pNode;
    }
}

List create(){
    List list;
    list.first = recursiveCreate();
}

void recursivePrint(PNode node){
    if (node != nullptr){
        std::cout << node->elem << " ";
        recursivePrint(node->next);
    }
}

void printList(List list){
    recursivePrint(list.first);
    std::cout << "\n";
}

void recursiveDestroy(PNode pNode){
    if (pNode != nullptr){
        recursiveDestroy(pNode->next);
        delete pNode;
    }
}

void destroy(List list) {
	//free the memory allocated for the nodes of the list
    recursiveDestroy(list.first);
}

bool recursiveSearchElement(PNode currentNode, int value) {
    //Base case: end of the list, the element is not found in the list
    if (currentNode == nullptr)
        return false;
        //Case: if the value is in the current node
    else if (currentNode->elem == value)
        return true;
    else
        //Case: the value is not found in the current node, we continue to search in the next ones
        return recursiveSearchElement(currentNode->next, value);
}

bool searchElement(List list, int value) {
    return recursiveSearchElement(list.first, value);
}

int recursiveGetCount(PNode currentNode) {
    //Base case
    if (currentNode == nullptr)
        return 0;
    else
        return 1 + recursiveGetCount(currentNode->next);
}

bool recursiveTestInclusion(PNode currentNode1, List list2) {
    //  Base case: empty list, all the elements have been found in the second list by now
    if (currentNode1 == nullptr)
        return true;
    //Case: element is not found in the second list
    else if (!searchElement(list2, currentNode1->elem))
        return false;
    else
        //Case: the value is found in the second list, we continue to search for the rest of the values
        return recursiveTestInclusion(currentNode1->next, list2);
}

bool testInclusion(List list1, List list2) {
    return recursiveTestInclusion(list1.first, list2);
}

bool compare(List list1, List list2) {
    return recursiveGetCount(list1.first) < recursiveGetCount(list2.first);
}

PNode recursiveEliminate(PNode currentNode, int value) {
    //Base case: empty list
    if (currentNode == nullptr)
        return nullptr;
    //If the current element is the one we are looking for, we delete it
    else if (currentNode->elem == value) {
        PNode nextNode = currentNode->next;
        free(currentNode);
        return recursiveEliminate(nextNode, value);
    //If it's not the one, we continue the search without it
    } else {
        currentNode->next = recursiveEliminate(currentNode->next, value);
        return currentNode;
    }
}

List eliminateElement(List list, int value) {
    List newList;
    newList.first = recursiveEliminate(list.first, value);
}

bool recursiveIsSet(PNode currentNode) {
    if (currentNode == nullptr)
        return true;
    else if (recursiveSearchElement(currentNode->next, currentNode->elem))
        return false;
    else
        return recursiveIsSet(currentNode->next);
}

bool isSet(List list) {
    return recursiveIsSet(list.first);
}
