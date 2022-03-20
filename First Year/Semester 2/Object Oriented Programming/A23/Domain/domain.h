#ifndef A23_911_BRINZA_ALINA_ELENA_DOMAIN_H
#define A23_911_BRINZA_ALINA_ELENA_DOMAIN_H
typedef struct {
    char name[50];
    char continent[50];
    unsigned long int population;
} Country;

Country createCountry(char name[], char continent[], unsigned long int population);
char* getName(Country* c);
char* getContinent(Country* c);
unsigned long int getPopulation(Country* c);
void toString(Country c, char str[]);

#endif //A23_911_BRINZA_ALINA_ELENA_DOMAIN_H
