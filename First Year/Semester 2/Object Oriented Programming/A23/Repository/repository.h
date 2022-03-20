 #ifndef A23_911_BRINZA_ALINA_ELENA_REPOSITORY_H
#define A23_911_BRINZA_ALINA_ELENA_REPOSITORY_H

#include <stdbool.h>
#include "../Domain/domain.h"
#include "../DynamicArray/dynamic_array.h"

typedef struct {
    DynamicArray dynamicArray;
}Repository;

Repository createRepository();
void addCountry(Repository *country_list, Country country);
int findByName(Repository *country_list, char name[]);
void deleteCountry(Repository *country_list, int delete_index);
void updateCountry(Repository *country_list, int update_index, Country updated_country);
void migrationUpdate(Repository *country_list, int old_index, int new_index, unsigned long int migrators);

#endif //A23_911_BRINZA_ALINA_ELENA_REPOSITORY_H
