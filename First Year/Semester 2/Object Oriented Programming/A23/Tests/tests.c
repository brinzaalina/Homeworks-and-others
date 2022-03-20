#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "tests.h"

//DOMAIN TESTS
void testDomain() {
    //Create a country
    Country c1 = createCountry("Romania", "Europe", 100);
    assert(strcmp(c1.name, "Romania") == 0);
    assert(strcmp(c1.continent, "Europe") == 0);
    assert(c1.population == 100);
    //Create another country
    Country c2 = createCountry("Moldova", "Europe", 100);
    assert(strcmp(c1.name, c2.name) != 0);
    assert(strcmp(c2.continent, "Africa") != 0);
    assert(c2.population != 200);
    //Test the getters
    assert(strcmp(getName(&c1), "Romania") == 0);
    assert(strcmp(getContinent(&c1), "Europe") == 0);
    assert(getPopulation(&c1) == 100);
    //Test the to string method
    char str[100];
    toString(c1, str);
    assert(strcmp(str, "Country Romania is a country from Europe and its population is 100.") == 0);
}

//DYNAMIC ARRAY TESTS
void testDynamicArray() {
    //Test create array
    DynamicArray da = createDynamicArray(2);
    assert(da.length == 0);
    assert(da.capacity == 2);
    Country c1 = createCountry("Romania", "Europe", 100);
    //Add an element
    addElement(&da, c1);
    assert(da.length == 1);
    Country c2 = createCountry("Moldova", "Europe", 100);
    //Add another element
    addElement(&da, c2);
    assert(da.length == 2);
    Country c3 = createCountry("Ungaria", "Europe", 100);
    //Add element to test the resize
    addElement(&da, c3);
    assert(da.length == 3);
    assert(da.capacity == 4);
    //Delete an element
    deleteElement(&da, 2);
    assert(da.length == 2);
    assert(da.capacity == 4);
    Country update = createCountry("Roumanie", "Europe", 200);
    //Update an element
    updateElement(&da, 1, update);
    assert(strcmp(da.data[1].name, "Roumanie") == 0);
    assert(strcmp(da.data[1].continent, "Europe") == 0);
    assert(da.data[1].population == 200);
    assert(arrayCapacity(&da) == 4);
    assert(arrayLength(&da) == 2);
    //Destroy the array
    destroyDynamicArray(&da);
}

//REPOSITORY TESTS
void testRepository() {
    //Create repository
    Repository repo = createRepository();
    assert(repo.dynamicArray.length == 10);
    assert(repo.dynamicArray.capacity == 10);
    Country c1 = createCountry("Romania", "Europe", 100);
    //Add a country
    addCountry(&repo, c1);
    assert(repo.dynamicArray.length == 11);
    assert(repo.dynamicArray.capacity == 20);
    //Test the find by name method
    int index_ro = findByName(&repo, c1.name);
    assert(index_ro == 10);
    Country update = createCountry("Roumanie", "Europe", 200);
    //Update a country
    updateCountry(&repo, index_ro, update);
    assert(strcmp(repo.dynamicArray.data[index_ro].name, "Roumanie") == 0);
    assert(strcmp(repo.dynamicArray.data[index_ro].continent, "Europe") == 0);
    assert(repo.dynamicArray.data[index_ro].population == 200);
    Country c2 = createCountry("Moldova", "Europe", 100);
    //Add another country
    addCountry(&repo, c2);
    assert(repo.dynamicArray.length == 12);
    //Update a country
    migrationUpdate(&repo, 11, 10, 100);
    assert(repo.dynamicArray.data[11].population == 0);
    assert(repo.dynamicArray.data[10].population == 300);
    //Delete a country
    deleteCountry(&repo, findByName(&repo, "Moldova"));
    assert(repo.dynamicArray.length == 11);
    //Destroy the repository
    destroyDynamicArray(&repo.dynamicArray);
}

//Undo Redo Repository tests
void testUndoRedoRepository() {
    //Create the undo redo repository
    UndoRedoRepository undo_redo = createUndoRedoRepo(1);
    assert(undo_redo.length_undo == 0);
    assert(undo_redo.length_redo == 0);
    assert(undo_redo.capacity_undo == 1);
    assert(undo_redo.capacity_redo == 1);
    Repository repo = createRepository();
    //Add an element to the undo array
    addUndoElement(&undo_redo, &repo);
    assert(undo_redo.length_undo == 1);
    Country c1 = createCountry("Romania", "Europe", 100);
    addCountry(&repo, c1);
    //Add an element to the redo array
    addRedoElement(&undo_redo, &repo);
    assert(undo_redo.length_redo == 1);
    //test the resize of undo
    addUndoElement(&undo_redo, &repo);
    assert(undo_redo.length_undo == 2);
    assert(undo_redo.capacity_undo == 2);
    //test the resize of redo
    addRedoElement(&undo_redo, &repo);
    assert(undo_redo.length_redo == 2);
    assert(undo_redo.capacity_redo == 2);
    //Pop the last element of the undo array
    popLastUndo(&undo_redo, &repo);
    assert(undo_redo.length_undo == 1);
    //Pop the last element of the redo array
    popLastRedo(&undo_redo, &repo);
    assert(undo_redo.length_redo == 1);
    //Destroy the arrays
    destroyDynamicArray(&repo.dynamicArray);
    free(undo_redo.undo);
    free(undo_redo.redo);
}

void testService() {
    UndoRedoRepository undo_redo = createUndoRedoRepo(10);
    Repository repo = createRepository();
    //check if a continent is valid
    bool valid = check_if_valid_continent("Europe");
    assert(valid == true);
    valid= check_if_valid_continent("Eu");
    assert(valid == false);
    //test the undo redo functions
    int undone = ServiceUndo(&repo, &undo_redo);
    int redone = ServiceRedo(&repo, &undo_redo);
    assert(undone == 1);
    assert(redone == 1);
    // add an already existing country
    int added = add_country(&repo, &undo_redo, "Bulgaria", "Europe", 100);
    assert(added == 1);
    // add a country with an invalid continent
    added = add_country(&repo, &undo_redo, "Romania", "Europa", 100);
    assert(added == 2);
    // add a valid country
    added = add_country(&repo, &undo_redo, "Romania", "Europe", 100);
    assert(added == 0);
    //delete a non-existing country
    bool deleted = delete_country(&repo, &undo_redo, "Moldova");
    assert(deleted == false);
    //delete a country
    deleted = delete_country(&repo, &undo_redo, "Romania");
    assert(deleted == true);
    //undo
    undone = ServiceUndo(&repo, &undo_redo);
    assert(undone == 0);
    //redo
    redone = ServiceRedo(&repo, &undo_redo);
    assert(redone == 0);
    //undo
    ServiceUndo(&repo, &undo_redo);
    //update a non existing country
    int updated = update_country(&repo, &undo_redo, "USA", "SUA", "America", 100);
    assert(updated == 1);
    //update a country with invalid continent
    updated = update_country(&repo, &undo_redo, "Romania", "Roumanie", "Mars", 100);
    assert(updated == 2);
    //update a country
    updated = update_country(&repo, &undo_redo, "Romania", "Roumanie", "Europe", 100);
    assert(updated == 0);
    updated = update_country(&repo, &undo_redo, "Roumanie", "Romania", "Europe", 1000);
    assert(updated == 0);
    added = add_country(&repo, &undo_redo, "Moldova", "Europe", 100);
    assert(added == 0);
    //migrate from a country to another
    int migrated = migration(&repo, &undo_redo, "Moldova", "Romania", 100);
    assert(migrated == 0);
    //migrate to a country that doesn't exist
    migrated = migration(&repo, &undo_redo, "Moldova", "Roumanie", 100);
    assert(migrated == 2);
    //migrate from a country that doesn't exist
    migrated = migration(&repo, &undo_redo, "Moldove", "Romania", 100);
    assert(migrated == 1);
    //filter by empty string the names
    char filter_string1[] = "\0";
    Country *valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    int filter = filter_country(&repo, filter_string1, valid_countries);
    assert(filter == repo.dynamicArray.length);
    free(valid_countries);
    //filter so that nothing corresponds
    valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    filter = filter_country(&repo, "z", valid_countries);
    assert(filter == 0);
    free(valid_countries);
    //filter so that one country corresponds
    valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    filter = filter_country(&repo, "Ro", valid_countries);
    assert(filter == 1);
    free(valid_countries);
    //filter and sort by empty string and population 0
    valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    int filter_sort = filter_sort_continent(&repo, valid_countries, filter_string1, 0);
    assert(filter_sort == repo.dynamicArray.length - 1);
    updated = update_country(&repo, &undo_redo, "Moldova", "Moldova", "Europe", 100);
    free(valid_countries);
    //filter and sort after we add a country with non-zero population
    valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    filter_sort = filter_sort_continent(&repo, valid_countries, filter_string1, 0);
    assert(filter_sort == repo.dynamicArray.length);
    free(valid_countries);
    //filter and sort by an invalid continent
    valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    filter_sort = filter_sort_continent(&repo, valid_countries, "EU", 0);
    assert(filter_sort == -1);
    free(valid_countries);
    //filter and sort by valid continent and population different than 0
    valid_countries = (Country*)malloc(repo.dynamicArray.capacity * sizeof(Country));
    filter_sort = filter_sort_continent(&repo, valid_countries, "Asia", 100000);
    assert(filter_sort == 2);
    //test that they are increasing
    assert(valid_countries[0].population < valid_countries[1].population);
    free(valid_countries);
}


void testAll() {
    //Domain tests
    testDomain();
    testDynamicArray();
    testRepository();
    testUndoRedoRepository();
    testService();
}