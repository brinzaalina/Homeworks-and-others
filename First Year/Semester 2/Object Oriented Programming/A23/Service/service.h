#ifndef A23_911_BRINZA_ALINA_ELENA_SERVICE_H
#define A23_911_BRINZA_ALINA_ELENA_SERVICE_H

#include <stdbool.h>
#include "../Repository/repository.h"
#include "../Repository/undoredorepository.h"

bool check_if_valid_continent(char continent[]);
int add_country(Repository *country_list, UndoRedoRepository *undo_redo_repo, char name[], char continent[], unsigned long int population);
bool delete_country(Repository *country_list, UndoRedoRepository  *undo_redo_repo, char name[]);
int update_country(Repository *country_list, UndoRedoRepository  *undo_redo_repo, char old_name[], char name[], char continent[], unsigned long int new_population);
int filter_country(Repository *country_list, const char filter_string[], Country valid_country[]);
int migration(Repository *country_list, UndoRedoRepository *undo_redo_repo, char old_name[], char new_name[], unsigned long int migrators);
int filter_sort_continent(Repository *country_list, Country valid_countries[], char continent_input[], unsigned long int population);
int ServiceUndo(Repository *country_list, UndoRedoRepository *undo_redo_repo);
int ServiceRedo(Repository *country_list, UndoRedoRepository *undo_redo_repo);

#endif //A23_911_BRINZA_ALINA_ELENA_SERVICE_H
