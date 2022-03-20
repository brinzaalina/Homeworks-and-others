#include <stdlib.h>
#include "undoredorepository.h"

UndoRedoRepository createUndoRedoRepo(int capacity) {
    ///Function to create the Undo Redo Repository with an initial capacity
    ///\param capacity - the initial capacity
    ///\return - the undo_redo_repository
    UndoRedoRepository undo_redo_repository;
    undo_redo_repository.undo = (Repository*)malloc(capacity * sizeof(Repository)); // allocate space for the undo list
    undo_redo_repository.length_undo = 0;
    undo_redo_repository.capacity_undo = capacity;
    undo_redo_repository.redo = (Repository*)malloc(capacity * sizeof(Repository)); // allocate space for the redo list
    undo_redo_repository.length_redo = 0;
    undo_redo_repository.capacity_redo = capacity;
    return undo_redo_repository;
}

void destroyUndoRedoRepository(UndoRedoRepository *undo_redo_repo) {
    /// Function to deallocate the arrays from the repository
    /// \param undo_redo_repo - the undo redo repository
    int index;
    for (index = 0; index < undo_redo_repo->length_redo; index++)
        free(undo_redo_repo->redo[index].dynamicArray.data); // deallocate all the arrays in the array redo
    free(undo_redo_repo->redo); // deallocate the redo array
    for (index = 0; index < undo_redo_repo->length_undo; index++)
        free(undo_redo_repo->undo[index].dynamicArray.data); // deallocate all the arrays in the array undo
    free(undo_redo_repo->undo);// deallocate the undo array
}

void addUndoElement(UndoRedoRepository *undo_redo_repo, Repository *repo) {
    ///Function to add an element to the undo array
    /// \param undo_redo_repo - the undo redo repository
    /// \param repo - the current repository for the countries
    if (undo_redo_repo->length_undo == undo_redo_repo->capacity_undo)
        resizeArrayUndo(undo_redo_repo); // if the array is full, resize
    //allocate space for the elements to be copied
    undo_redo_repo->undo[undo_redo_repo->length_undo].dynamicArray.data = (Country *)malloc(repo->dynamicArray.capacity*sizeof(Country));
    //copy the elements
    for (int index = 0; index < repo->dynamicArray.length; index++)
        undo_redo_repo->undo[undo_redo_repo->length_undo].dynamicArray.data[index] = repo->dynamicArray.data[index];
    undo_redo_repo->undo[undo_redo_repo->length_undo].dynamicArray.length = repo->dynamicArray.length;
    undo_redo_repo->undo[undo_redo_repo->length_undo].dynamicArray.capacity = repo->dynamicArray.capacity;
    undo_redo_repo->length_undo++;
}

void addRedoElement(UndoRedoRepository *undo_redo_repo, Repository *repo) {
    ///Function to add an element to the redo array
    /// \param undo_redo_repo - the undo redo repository
    /// \param repo - the current repository for the countries
    if (undo_redo_repo->length_redo == undo_redo_repo->capacity_redo)
        resizeArrayRedo(undo_redo_repo);// if the array is full, resize
    //allocate space for the elements to be copied
    undo_redo_repo->redo[undo_redo_repo->length_redo].dynamicArray.data = (Country *)malloc(repo->dynamicArray.capacity*sizeof(Country));
    //copy the elements
    for (int index = 0; index < repo->dynamicArray.length; index++)
        undo_redo_repo->redo[undo_redo_repo->length_redo].dynamicArray.data[index] = repo->dynamicArray.data[index];
    undo_redo_repo->redo[undo_redo_repo->length_redo].dynamicArray.length = repo->dynamicArray.length;
    undo_redo_repo->redo[undo_redo_repo->length_redo].dynamicArray.capacity = repo->dynamicArray.capacity;
    undo_redo_repo->length_redo++;
}

void popLastUndo(UndoRedoRepository *undo_redo_repo, Repository *repo) {
    /// Function to replace the actual repository with the last element in the undo array
    /// \param undo_redo_repo - the undo redo repository
    /// \param repo - the current repository for the countries
    free(repo->dynamicArray.data); // free the current repo
    //copy the elements
    repo->dynamicArray.data = undo_redo_repo->undo[undo_redo_repo->length_undo - 1].dynamicArray.data;
    repo->dynamicArray.length = undo_redo_repo->undo[undo_redo_repo->length_undo - 1].dynamicArray.length;
    repo->dynamicArray.capacity = undo_redo_repo->undo[undo_redo_repo->length_undo -1].dynamicArray.capacity;
    //delete the las element of the undo array
    Repository *temp;
    temp = (Repository*)malloc(undo_redo_repo->capacity_undo* sizeof(Repository));
    for (int index = 0; index < undo_redo_repo->length_undo - 1; index++)
        temp[index] = undo_redo_repo->undo[index];
    free(undo_redo_repo->undo);
    undo_redo_repo->undo = temp;
    undo_redo_repo->length_undo--;
}

void popLastRedo(UndoRedoRepository *undo_redo_repo, Repository *repo) {
    /// Function to replace the actual repository with the last element in the redo array
    /// \param undo_redo_repo - the undo redo repository
    /// \param repo - the current repository for the countries
    free(repo->dynamicArray.data); // free the current repo
    //copy the elements
    repo->dynamicArray.data = undo_redo_repo->redo[undo_redo_repo->length_redo - 1].dynamicArray.data;
    repo->dynamicArray.length = undo_redo_repo->redo[undo_redo_repo->length_redo - 1].dynamicArray.length;
    repo->dynamicArray.capacity = undo_redo_repo->redo[undo_redo_repo->length_redo -1].dynamicArray.capacity;
    //delete the las element of the redo array
    Repository *temp;
    temp = (Repository*)malloc(undo_redo_repo->capacity_redo* sizeof(Repository));
    for (int index = 0; index < undo_redo_repo->length_redo - 1; index++)
        temp[index] = undo_redo_repo->redo[index];
    free(undo_redo_repo->redo);
    undo_redo_repo->redo = temp;
    undo_redo_repo->length_redo--;
}

void resizeArrayUndo(UndoRedoRepository *undo_redo_repo) {
    ///Function to resize the undo array
    /// \param undo_redo_repo - the undo redo repository
    //create a temporary array for moving the elements in a bigger one
    Repository *temp;
    temp = (Repository*)malloc(undo_redo_repo->capacity_undo * 2 * sizeof(Repository));
    for (int index = 0; index < undo_redo_repo->length_undo - 1; index++)
        temp[index] = undo_redo_repo->undo[index];
    free(undo_redo_repo->undo);
    undo_redo_repo->undo = temp;
    undo_redo_repo->capacity_undo *= 2;
}

void resizeArrayRedo(UndoRedoRepository *undo_redo_repo) {
    ///Function to resize the redo array
    /// \param undo_redo_repo - the undo redo repository
    //create a temporary array for moving the elements in a bigger one
    Repository *temp;
    temp = (Repository*)malloc(undo_redo_repo->capacity_redo * 2 * sizeof(Repository));
    for (int index = 0; index < undo_redo_repo->length_redo - 1; index++)
        temp[index] = undo_redo_repo->redo[index];
    free(undo_redo_repo->redo);
    undo_redo_repo->redo = temp;
    undo_redo_repo->capacity_redo *= 2;
}