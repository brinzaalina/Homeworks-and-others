#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"


void option_2(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    char name[50];
    char continent[50];
    char population_string[50];
    unsigned long int population;
    printf("Enter the name of the country, name of the continent and population: \n");
    scanf_s(" %[^\n]", &name, sizeof(name));
    scanf_s("%s", &continent, sizeof(continent));
    scanf_s("%s", &population_string, sizeof(population_string));
    population = strtol(population_string, NULL, 10);
    int added = add_country(country_list, undo_redo_repo, name, continent, population);
    if (added == 1)
        printf("Country %s already exists in the list.\n", name);
    else if (added == 2)
        printf("The continent %s is not a valid one.\n", continent);
    else
        printf("Country %s successfully added.\n", name);
}

void option_3(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    char name_delete[50];
    printf("Enter the name of the country you want to delete: \n");
    scanf_s(" %[^\n]", &name_delete, sizeof(name_delete));
    bool deleted = delete_country(country_list, undo_redo_repo, name_delete);
    if (deleted == false)
        printf("The country you wanted to delete is not in the list.\n");
    else
        printf("Country %s successfully deleted.\n", name_delete);
}

void option_4(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    char option_type_string[5];
    printf("Choose a type of update: \n"
           "1. Update name, continent and/or population.\n"
           "2. Migration. \n");
    scanf_s("%s", &option_type_string, sizeof(option_type_string));
    int option_type = strtol(option_type_string, NULL, 10);
    if (option_type == 1) {
        char old_name[50];
        char name[50];
        char continent[50];
        char population_string[50];
        unsigned long int population;
        printf("Enter the old name of the country, the new name of the country, new name of the continent and/or new population: \n");
        scanf_s(" %[^\n]", &old_name, sizeof(old_name));
        scanf_s(" %[^\n]", &name, sizeof(name));
        scanf_s("%s", &continent, sizeof(continent));
        scanf_s("%s", &population_string, sizeof(population_string));
        population = strtol(population_string, NULL, 10);
        int updated = update_country(country_list, undo_redo_repo, old_name, name, continent, population);
        if (updated == 1)
            printf("Country %s does not exist.\n", name);
        else if (updated == 2)
            printf("Invalid input for the continent.\n");
        else
            printf("Country %s successfully updated.\n", old_name);
    }else if (option_type == 2) {
        char old_name[50];
        char new_name[50];
        char migrators_string[50];
        unsigned long int migrators;
        printf("Enter the name of the old country, the name of the new country and the number of people that migrate: \n");
        scanf_s(" %[^\n]", &old_name, sizeof(old_name));
        scanf_s(" %[^\n]", &new_name, sizeof(new_name));
        scanf_s("%s", &migrators_string, sizeof(migrators_string));
        migrators = strtol(migrators_string, NULL, 10);
        int updated = migration(country_list, undo_redo_repo, old_name, new_name, migrators);
        if (updated == 1)
            printf("Country %s does not exist.\n", old_name);
        else if (updated == 2)
            printf("Country %s does not exist. \n", new_name);
        else
            printf("%ld people migrated from %s to %s.\n", migrators, old_name, new_name);

    }
}

void option_5(Repository *country_list) {
    char filter_string[50];
    Country *valid_countries;

    valid_countries = (Country*)malloc(country_list->dynamicArray.length* sizeof(Country));
    printf("Enter the string by which you want to filter: \n");
    getchar();
    fgets(filter_string, sizeof(filter_string), stdin);
    filter_string[strlen(filter_string) - 1] = '\0';
    int counter = filter_country(country_list, filter_string, valid_countries);
    if (counter == 0)
        printf("There are no countries that have the given string in their names.\n");
    else{
        for (int index = 0; index < counter; index++)
            printf("Country: %s, continent: %s, population: %ld \n", valid_countries[index].name, valid_countries[index].continent, valid_countries[index].population);
    }
    free(valid_countries);
}

void option_6(Repository *country_list) {
    char continent_input[50];
    char population_string[50];
    int population;
    Country *valid_countries;
    valid_countries = (Country*)malloc(country_list->dynamicArray.length * sizeof(Country));
    printf("Enter the continent by which you want to filter: \n");
    getchar();
    fgets(continent_input, sizeof(continent_input), stdin);
    continent_input[strlen(continent_input) - 1] = '\0';
    printf("Enter the population: \n");
    scanf_s("%s", &population_string, sizeof(population_string));
    population = strtol(population_string, NULL, 10);
    int counter = filter_sort_continent(country_list, valid_countries, continent_input, population);
    if (counter == -1)
        printf("The continent you gave is not a valid one. \n");
    else
        for (int index = 0; index < counter; index++)
            printf("%d. Country: %s, continent: %s, population: %ld \n", index + 1, valid_countries[index].name, valid_countries[index].continent, valid_countries[index].population);
    free(valid_countries);
}

void list_all_countries(Repository *country_list) {
    int index;
    for (index=0; index < arrayLength(&country_list->dynamicArray); index++) {
        printf("%d. Country: %s, continent: %s, population: %ld \n", index+1, country_list->dynamicArray.data[index].name, country_list->dynamicArray.data[index].continent, country_list->dynamicArray.data[index].population);
    }
}

void undo(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    int valid = ServiceUndo(country_list, undo_redo_repo);
    if (valid == 1)
        printf("There are no more operations that can be undone!\n");
    else
        printf("Successful undo!\n");
}

void redo(Repository *country_list, UndoRedoRepository *undo_redo_repo) {
    int valid = ServiceRedo(country_list, undo_redo_repo);
    if (valid == 1)
        printf("There are no more operations that can be redone!\n");
    else
        printf("Successful redo!\n");
}

void print_menu() {
    printf("MENU: \n"
           "0. EXIT. \n"
           "1. List all countries. \n"
           "2. Add a country. \n"
           "3. Delete a country. \n"
           "4. Update a country. \n"
           "5. Display all countries whose name contains a given string. \n"
           "6. Display all countries on a given continent, whose populations are greater than a given value. \n"
           "7. UNDO.\n"
           "8. REDO.\n");
}

void start() {
    printf("Welcome to the World Population Monitoring App!\n");
    bool done = false;
    Repository country_list = createRepository();
    UndoRedoRepository undo_redo_repo = createUndoRedoRepo(10);
    while (!done) {
        print_menu();
        printf("Choose an option from the menu: ");
        char option_string[5];
        char option0[] = "0";
        char option1[] = "1";
        char option2[] = "2";
        char option3[] = "3";
        char option4[] = "4";
        char option5[] = "5";
        char option6[] = "6";
        char option7[] = "7";
        char option8[] = "8";
        scanf_s("%s", &option_string, sizeof(option_string));
        if (strcmp(option_string, option0) == 0){
            destroyDynamicArray(&country_list.dynamicArray);
            destroyUndoRedoRepository(&undo_redo_repo);
            printf("Goodbye!");
            done = true;
        } else if (strcmp(option_string, option1) == 0) {
            list_all_countries(&country_list);
        } else if (strcmp(option_string, option2) == 0) {
            option_2(&country_list, &undo_redo_repo);
        } else if (strcmp(option_string, option3) == 0) {
            option_3(&country_list, &undo_redo_repo);
        } else if (strcmp(option_string, option4) == 0) {
            option_4(&country_list, &undo_redo_repo);
        } else if (strcmp(option_string, option5) == 0) {
            option_5(&country_list);
        } else if (strcmp(option_string, option6) == 0) {
            option_6(&country_list);
        } else if (strcmp(option_string, option7) == 0) {
            undo(&country_list, &undo_redo_repo);
        }else if (strcmp(option_string, option8) == 0){
            redo(&country_list, &undo_redo_repo);
        }else
            printf("Bad input!\n");
    }
}