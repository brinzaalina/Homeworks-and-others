#include <string.h>
#include "service.h"

bool check_if_valid_continent(char continent[]){
    ///Function to check if the continent is valid
    ///\param continent - the name of the continent
    ///\return - true if it is valid, false otherwise
    const char * Continents[] = {"Europe", "Asia", "America", "Africa", "Australia"};
    int index = 0;
    bool valid = false;
    while (index < sizeof(Continents) / sizeof (const char *) && valid == false) {
        if (strcmp(continent, Continents[index]) == 0)
            valid = true;
        index++;
    }
    return valid;
}

int add_country(Repository *country_list, UndoRedoRepository *undo_redo_repo, char name[], char continent[], unsigned long int population) {
    ///ADD functionality
    ///Service function to create the new element and pass it to be added to the list.
    /// \param country_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param name - name of the country
    /// \param continent - name of the continent, one from Europe, Asia, America, Africa or Australia
    /// \param population - the number of people from the country, stored in millions
    /// \return - 1 if the country already exists, 2 if the continent is not valid, 0 if the couuntry was added successfully
    int index;
    for(index=0; index < country_list->dynamicArray.length; index++) {
        if (strcmp(getName(&country_list->dynamicArray.data[index]), name) == 0) // check if we already have the country
            return 1;
    }
    if (check_if_valid_continent(continent) == false) // check if the continent is valid
        return 2;
    Country new_country = createCountry(name, continent, population); // create the element
    addUndoElement(undo_redo_repo, country_list); // pass the current repo to the undo repo
    addCountry(country_list, new_country);
    return 0;
}

bool delete_country(Repository *country_list, UndoRedoRepository *undo_redo_repo, char name[]) {
    /// DELETE functionality
    /// Service function to identify and delete the required element given by the user.
    /// \param country_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param name - name of the country to be deleted
    /// \return - false if the element does not exist, true if it exist and it was deleted
    int deleted_index = findByName(country_list, name); // find the index of the element to be deleted
    if (deleted_index == -1)
        return false;
    else {
        addUndoElement(undo_redo_repo, country_list); // pass the current repo to the undo repo
        deleteCountry(country_list, deleted_index);
        return true;
    }
}

int update_country(Repository *country_list, UndoRedoRepository *undo_redo_repo, char old_name[], char name[], char continent[], unsigned long int new_population) {
    ///UPDATE (first type) functionality
    ///Service function to update the name, continent and/or the population of a specific country.
    /// \param country_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param old_name - the name of the country to be updated
    /// \param new_name - the new name of the country, can be the same as the old one
    /// \param continent - the new name of the continent, can be the same as the old one
    /// \param population - the new number of people in the country, can be the same as the old one
    /// \return - 2 if the continent is not valid, 1 if the country to be updated does not exist, 0 if it exists and it was updated
    if (check_if_valid_continent(continent) == false) // check if the continent is valid
        return 2;
    int update_index = findByName(country_list, old_name); // find the index of the element to be updated
    if (update_index == -1)
        return 1;
    Country updated_country = createCountry(name, continent, new_population); // create the new element
    addUndoElement(undo_redo_repo, country_list); // pass the current repo to the undo repo
    updateCountry(country_list, update_index, updated_country);
    return 0;
}

int migration(Repository *country_list, UndoRedoRepository *undo_redo_repo, char old_name[], char new_name[], unsigned long int migrators) {
    /// UPDATE (second type) functionality
    /// Service function to update the population of two countries through migration.
    /// \param country_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository, for the undo redo functionalities
    /// \param old_name - the name of the country to be updated
    /// \param new_name - the new name of the country, can be the same as the old one
    /// \param migrators - the number of people that want to migrate
    /// \return - 1 if the old country does not exist, 2 if the new country does not exist, 0 if the population mirated successfully
    int index_of_old_country = findByName(country_list, old_name); // find the index of the old country
    int index_of_new_country = findByName(country_list, new_name); // find the index of the new country
    if (index_of_old_country == -1)
        return 1;
    else if (index_of_new_country == -1)
        return 2;
    else {
        addUndoElement(undo_redo_repo, country_list); // pass the current repo to the undo repo
        migrationUpdate(country_list, index_of_old_country, index_of_new_country, migrators);
        return 0;
    }
}

int filter_country(Repository *country_list, const char filter_string[], Country valid_countries[]) {
    ///Filter functionality
    ///Function to filter by a given string and by names the existent countries
    /// \param country_list - the repository in which the elements are stored
    /// \param filter_string - the string by which the names are filtered
    /// \param valid_countries - the array in which the valid countries will be stored
    /// \return - the number of elements from the valid_countries array
    int counter = 0;
    int index;
    if(filter_string[0] == '\0') // case for when the string is empty
        for (index = 0; index < country_list->dynamicArray.length; index++) {
            strcpy(valid_countries[counter].name, country_list->dynamicArray.data[index].name);
            strcpy(valid_countries[counter].continent, country_list->dynamicArray.data[index].continent);
            valid_countries[counter].population = country_list->dynamicArray.data[index].population; // copy everything in the array[counter]
            counter++; // increase the number of elements from the array
        }
    else {
        for (index = 0; index < country_list->dynamicArray.length; index++) {
            if (strstr(country_list->dynamicArray.data[index].name, filter_string) != NULL) { // if the string can be found in the name, copy in array[counter]
                strcpy(valid_countries[counter].name, country_list->dynamicArray.data[index].name);
                strcpy(valid_countries[counter].continent, country_list->dynamicArray.data[index].continent);
                valid_countries[counter].population = country_list->dynamicArray.data[index].population;
                counter++; // increase the number of elements from the array
            }
        }
    }
    return counter;
}

int filter_sort_continent(Repository *country_list, Country valid_countries[], char continent_input[], unsigned long int population) {
    ///Filter and sort functionality
    ///Function to find the countries on a given continent that have a population greater than the given population
    /// \param country_list - the repository in which the elements are stored
    /// \param valid_countries - the array of valid countries
    /// \param continent_input - the name of the continent to filter by
    /// \param population - the number for population comparison
    /// \return - -1 if the continent is not empty or valid, the number of elements from the valid_countries array otherwise
    int counter = 0;
    int index;
    if(continent_input[0] == '\0') { // case if the continent input is empty
        for (index = 0; index < country_list->dynamicArray.length; index++)
            if (country_list->dynamicArray.data[index].population > population) {
                strcpy(valid_countries[counter].name, country_list->dynamicArray.data[index].name);
                strcpy(valid_countries[counter].continent, country_list->dynamicArray.data[index].continent);
                valid_countries[counter].population = country_list->dynamicArray.data[index].population;
                counter++; // copy the elements and increase the counter
            }
    }else if (check_if_valid_continent(continent_input) == false) // check if the continent is valid
        return -1;
    else {
        for (index = 0; index < country_list->dynamicArray.length; index++)
            if (strcmp(country_list->dynamicArray.data[index].continent, continent_input) == 0) // if the continent is the same, copy the element and increase the counter
                if (country_list->dynamicArray.data[index].population > population) {
                    strcpy(valid_countries[counter].name, country_list->dynamicArray.data[index].name);
                    strcpy(valid_countries[counter].continent, country_list->dynamicArray.data[index].continent);
                    valid_countries[counter].population = country_list->dynamicArray.data[index].population;
                    counter++;
                }
    }
    // Bubble sort to sort the elements of the array in ascending order
    Country temp; // temporary variable for swapping the elements
    for (int i = 0; i < counter - 1; i++)
        // Last i elements are already in place
        for (int j = 0; j < counter - i - 1; j++)
            if (valid_countries[j].population > valid_countries[j + 1].population) { // if the elements correspond, do the swapping
                temp = valid_countries[j];
                valid_countries[j] = valid_countries[j + 1];
                valid_countries[j + 1] = temp;
            }
    return counter;
}

int ServiceUndo(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    ///UNDO service function
    ///Function to undo the last operation done
    /// \param country_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository
    /// \return - 1 if there are no more operations to be undone, 0 otherwise
    if (undo_redo_repo->length_undo == 0)
        return 1;
    addRedoElement(undo_redo_repo, country_list); // add the current repo for the redo operation
    popLastUndo(undo_redo_repo, country_list);
    return 0;
}

int ServiceRedo(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    ///REDO service function
    ///Function to redo the last operation done
    /// \param country_list - the repository in which the elements are stored
    /// \param undo_redo_repo - the undo and redo repository
    /// \return - 1 if there are no more operations to be redone, 0 otherwise
    if (undo_redo_repo->length_redo == 0)
        return 1;
    addUndoElement(undo_redo_repo, country_list); // add the current repo for the undo operation
    popLastRedo(undo_redo_repo, country_list);
    return 0;
}