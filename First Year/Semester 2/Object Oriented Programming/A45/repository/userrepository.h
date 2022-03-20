#ifndef A45_911_BRINZA_ALINA_ELENA_USERREPOSITORY_H
#define A45_911_BRINZA_ALINA_ELENA_USERREPOSITORY_H

#include <dynamicarray.h>

class UserRepository {
private:
    DynamicArray<Dog>* adoptionList;
public:
    ///Constructor for the UserRepository class
    ///\param adoptionList1 - the list of dogs that the user is adopting
    UserRepository(DynamicArray<Dog> * adoptionList1);

    ///Method to get all the elements of the UserRepository
    ///\return - the list of elements from the UserRepository
    Dog * getAllUserRepo();

    ///Method to get the number of elements from the UserRepository
    ///\return - the number of elements
    int getNrElems();

    ///Method to get the capacity of the dynamic array used in the UserRepository
    ///\return - the capacity
    int getCap();

    ///Method to add an element to the UserRepository
    ///\param dog - the element to be added
    void addUserRepo(const Dog& dog);

    ///Destructor
    ~UserRepository();
};
#endif //A45_911_BRINZA_ALINA_ELENA_USERREPOSITORY_H
