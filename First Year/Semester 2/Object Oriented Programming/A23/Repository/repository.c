#include <string.h>
#include "repository.h"

void initialiseRepo(Repository *country_list) {
    /// Function to initialise the repository with 10 entries
    /// \param country_list - the repository in which the data is stored
    Country country1 = createCountry("Bulgaria", "Europe", 6948445);
    Country country2 = createCountry("South Africa", "Africa", 59734218);
    Country country3 = createCountry("Vietnam", "Asia", 97338579);
    Country country4 = createCountry("Germany", "Europe", 83783942);
    Country country5 = createCountry("Mexico", "America", 128932462);
    Country country6 = createCountry("Morocco", "Africa", 36910560);
    Country country7 = createCountry("Ukraine", "Europe", 43733762);
    Country country8 = createCountry("Spain", "Europe", 46754778);
    Country country9 = createCountry("Australia", "Australia", 25499884);
    Country country10 = createCountry("China", "Asia", 1439323776);
    addCountry(country_list, country1);
    addCountry(country_list, country2);
    addCountry(country_list, country3);
    addCountry(country_list, country4);
    addCountry(country_list, country5);
    addCountry(country_list, country6);
    addCountry(country_list, country7);
    addCountry(country_list, country8);
    addCountry(country_list, country9);
    addCountry(country_list, country10);
}

Repository createRepository() {
    ///Function to create a repository
    /// \return - the new repository
    Repository country_list;
    DynamicArray array = createDynamicArray(10); // create the dynamic array with initial capacity of 10
    country_list.dynamicArray = array;
    initialiseRepo(&country_list);
    return country_list;
}

void addCountry(Repository *country_list, Country country) {
    ///Function to add a country to the repository
    /// \param country_list - the repository
    /// \param country - the element to be added
    addElement(&country_list->dynamicArray, country);
}

int findByName(Repository *country_list, char name[]) {
    ///Function to find an element's index based on its name
    /// \param country_list - the repository
    /// \param name - the name of the country to be found
    /// \return - the index of the searched element
    int searched_index = -1;
    int index = 0;
    while (index < country_list->dynamicArray.length && searched_index == -1) { // repeat the search while there are still elements and the element that we look for is not found
        if (strcmp(getName(&country_list->dynamicArray.data[index]), name) == 0) {
            searched_index = index;
        }
        index++;
    }
    return searched_index;
}

void deleteCountry(Repository *country_list, int delete_index) {
    ///Function to delete an element based on its index
    ///\param country_list - the repository
    ///\param delete_index - the index of the element to be deleted
    deleteElement(&country_list->dynamicArray, delete_index);
}

void updateCountry(Repository *country_list, int update_index, Country updated_country) {
    ///Function to update an element based on its index with the characteristics of another element
    ///\param country_list - the repository
    ///\param delete_index - the index of the element to be updated
    ///\param updated_country - the element with the new characteristics
    updateElement(&country_list->dynamicArray, update_index, updated_country);
}

void migrationUpdate(Repository *country_list, int old_index, int new_index, unsigned long int migrators) {
    ///Function to update the populations of two countries based on migration
    ///\param country_list - the repository
    ///\param old_index - the index of the old country
    ///\param new_index - the index of the new country
    ///\param migrators - the number of people that migrate from the old country to the new country
    country_list->dynamicArray.data[old_index].population -= migrators;
    country_list->dynamicArray.data[new_index].population += migrators;
}