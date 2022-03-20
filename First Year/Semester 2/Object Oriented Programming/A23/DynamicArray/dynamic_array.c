#include <stdlib.h>
#include "dynamic_array.h"

void resizeDynamicArray(DynamicArray * array);

DynamicArray createDynamicArray(int capacity) {
    ///Function to create a dynamic array with an initial capacity.
    ///\param capacity - the initial capacity
    ///\return - the array
    DynamicArray array;
    array.data = (Country *)malloc(capacity* sizeof(Country));
    array.length = 0;
    array.capacity = capacity;
    return array;
}

void destroyDynamicArray(DynamicArray * array) {
    ///Function to deallocate the space of the array
    ///\param array - the dynamic array structure which contains the array to be deallocated
    free(array->data);
}

void addElement(DynamicArray * array, Country element) {
    ///Function to add an element to the dynamic array
    ///\param array- the dynamic array structure
    ///\param element - the element to be added
    if(array->length == array->capacity) // if the data array is full we need to resize the array
        resizeDynamicArray(array);
    array->data[array->length] = element;
    array->length++;
}

void deleteElement(DynamicArray * array, int delete_index) {
    ///Function to delete an element with a given index
    ///\param array - the dynamic array structure
    ///\param delete_index - the index of the element to be deleted
    int index;
    for (index = delete_index; index < array->length; index++)
        array->data[index] = array->data[index + 1]; // move one position to the left all the elements after the one that has to be deleted
    array->length--;
}

void updateElement(DynamicArray * array, int update_index, Country update_element) {
    ///Function to update an element with a given index with the characteristics given
    ///\param array - the dynamic array structure
    ///\param delete_index - the index of the element to be updated
    ///\param update_element - the element which contains the new characteristics
    array->data[update_index] = update_element;
}

void resizeDynamicArray(DynamicArray * array) {
    ///Function to resize the array in case it is full
    ///\param array - the dynamic array structure
    Country * new_data = (Country *)malloc(array->length * 2 * sizeof(Country));
    int index;
    for (index = 0; index < array->length; index++) {
        new_data[index] = array->data[index];
    }
    free(array->data);
    array->data = new_data;
    array->capacity *= 2;
}

int arrayCapacity(DynamicArray * array) {
    ///Getter for the array capacity
    ///\param array - the dynamic array structure
    ///\return - the capacity
    return array->capacity;
}

int arrayLength(DynamicArray * array) {
    ///Getter for the array length
    ///\param array - the dynamic array structure
    ///\return - the length
    return array->length;
}