#include <stdio.h>
#include <string.h>
#include "domain.h"

Country createCountry(char name[], char continent[], unsigned long int population) {
    ///Function to create an element of type Country
    /// \param name - the name of the country
    /// \param continent - the name of the continent on which the country is
    /// \param population - the number of people that live in the country
    /// \return - the new element of type Country with the given characteristics
    Country c;
    strcpy(c.name, name);
    strcpy(c.continent, continent);
    c.population = population;
    return c;
}

char* getName(Country* c) {
    /// Getter for the name attribute
    /// \param c - the country
    /// \return - the name of the country
    return c->name;
}

char* getContinent(Country* c) {
    /// Getter for the continent attribute
    /// \param c - the country
    /// \return - the name of the continent
    return c->continent;
}

unsigned long int getPopulation(Country* c) {
    /// Getter for the population attribute
    /// \param c - the country
    /// \return - the pupulation
    return c->population;
}

void toString(Country c, char str[]) {
    ///Method to transform the element into a string
    sprintf(str, "Country %s is a country from %s and its population is %ld.", c.name, c.continent, c.population);
}
