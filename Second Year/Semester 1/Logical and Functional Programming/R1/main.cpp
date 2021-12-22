#include <iostream>
#include "list.h"

void testTheInclusionOfTwoSets() {
    std::cout << "First set: \n";
    List list1;
    list1 = create();
    while (!isSet(list1)) {
        std::cout << "This is not a set, please enter a valid set\n";
        list1 = create();
    }

    std::cout << "Second set: \n";
    List list2;
    list2 = create();
    while (!isSet(list2)) {
        std::cout << "This is not a set, please enter a valid set\n";
        list2 = create();
    }

    printList(list1);
    printList(list2);

    bool included;
    if (compare(list1, list2)) {
        included = testInclusion(list1, list2);
        if (included)
            std::cout << "The first set is included in the second one.\n";
        else
            std::cout <<"No inclusion.\n";
    } else {
        included = testInclusion(list2, list1);
        if (included)
            std::cout << "The second set is included in the first one.\n";
        else
            std::cout <<"No inclusion.\n";
    }

    destroy(list1);
    destroy(list2);
}

void eliminateAllOccurrencesOfAnElement() {
    std::cout << "Enter the list: \n";
    List list;
    list = create();

    TElem elem;
    std::cout << "Enter the element that you want to eliminate from the list: ";
    std::cin >> elem;

    List newList;
    newList = eliminateElement(list, elem);

    printList(newList);

    destroy(newList);
}

void printMenu() {
    std::cout << "Options: \n";
    std::cout << "1. Test the inclusion of two sets, represented as lists.\n";
    std::cout << "2. Eliminate all occurrences of an element from a list.\n";
    std::cout << "3. Exit.\n";
    std::cout << "Enter your option: ";
}

int main() {
    bool done = false;
    while (!done) {
        printMenu();
        int option;
        std::cin >> option;
        if (option == 1) {
            testTheInclusionOfTwoSets();
        } else if (option == 2) {
            eliminateAllOccurrencesOfAnElement();
        } else if (option == 3) {
            done = true;
        } else {
            std::cout << "Bad input!\n";
        }
    }

}
