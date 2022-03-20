#ifndef A45_911_BRINZA_ALINA_ELENA_DYNAMICARRAY_H
#define A45_911_BRINZA_ALINA_ELENA_DYNAMICARRAY_H

#include <domain.h>
template <typename TElem>
class DynamicArray {
private:
    TElem * elements;
    int capacity;
    int nrEntities;

    ///Function to resize the dynamic array when it reaches the maximum capacity
    void resizeDynamicArray();

public:

    ///Constructor for the DynamicArray class
    ///\param capacity - the capacity of the array
    DynamicArray(int capacity);

    ///Method to add an element to the array
    ///\param element - a general element to be added
    void addElem(TElem element);

    ///Method to delete an element based on its index
    ///\param delete_index - the index of the element to be deleted
    void deleteElem(int delete_index);

    ///Method to update an element of the array
    ///\param update_index - the index of the element to be updated
    ///\param element - the element with which the update is done
    void updateElem(int update_index, TElem element);

    ///Getter method for the array of the DynamicArray class
    ///\return - the elements of the array
    TElem * elemGetter();

    ///Getter method for the capacity of the DynamicArray
    ///\return - the capacity of the array
    int capacityGetter() const;

    ///Getter method for the number of elements of the DynamicArray
    ///\return - the number of elements of the array
    int nrEntitiesGetter() const;

    ///Destructor
    ~DynamicArray();
};

template <typename TElem>
DynamicArray<TElem>::DynamicArray(int capacity) {
    if (capacity <= 0){
        throw "Can't have an array with less than an element!";
    }
    this->capacity = capacity;
    this->nrEntities = 0;
    this->elements = new TElem[capacity];

}

template <typename TElem>
void DynamicArray<TElem>::addElem(TElem element) {
    if (this->capacity == this->nrEntities)
        this->resizeDynamicArray();
    this->elements[this->nrEntities] = element;
    this->nrEntities++;
}

template <typename TElem>
void DynamicArray<TElem>::resizeDynamicArray() {
    auto *newElems = new TElem [this->capacity * 2];
    int index;
    for (index = 0; index < this->nrEntities; index++) {
        newElems[index] = this->elements[index];
    }
    delete[] this->elements;
    this->elements = newElems;
    this->capacity *= 2;
}
template <typename TElem>
void DynamicArray<TElem>::deleteElem(int delete_index) {
    int index;
    for (index = delete_index; index < this->nrEntities - 1; index++) {
        this->elements[index] = this->elements[index + 1];
    }
    this->nrEntities--;
}
template <typename TElem>
void DynamicArray<TElem>::updateElem(int update_index, TElem update_element) {
    this->elements[update_index] = update_element;
}
template <typename TElem>
TElem * DynamicArray<TElem>::elemGetter() {
    return this->elements;
}
template <typename TElem>
int DynamicArray<TElem>::capacityGetter() const {
    return this->capacity;
}
template <typename TElem>
int DynamicArray<TElem>::nrEntitiesGetter() const{
    return this->nrEntities;
}
template <typename TElem>
DynamicArray<TElem>::~DynamicArray() {
    delete[] this->elements;

}
#endif //A45_911_BRINZA_ALINA_ELENA_DYNAMICARRAY_H