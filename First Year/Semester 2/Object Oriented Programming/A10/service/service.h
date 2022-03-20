#ifndef A45_911_BRINZA_ALINA_ELENA_SERVICE_H
#define A45_911_BRINZA_ALINA_ELENA_SERVICE_H

#include <repository.h>
#include <memory>
#include "undoredo.h"

class Service{
private:
    Repository& repository;
    std::vector<std::shared_ptr<UndoRedoAction>> undoAdmin;
    std::vector<std::shared_ptr<UndoRedoAction>> redoAdmin;

public:
    explicit Service(Repository& repo);
    std::vector<Dog> getAllService();
    unsigned int getNrElemsService();
    unsigned int getCapService();
    void addService(const std::string& breed, const std::string& name, int age, const std::string& photograph);
    void deleteService(const std::string& name);
    void updateService(const std::string& old_name, const std::string& new_breed, const std::string& new_name, int new_age,const std::string& new_photo);
    void getFiltered(std::vector<Dog> &valid_dogs, const std::string &filter_string, int age_filter);
    int findByNameService(const std::string& name);
    std::vector<std::string> getAllBreeds();
    int numberOfDogsPerBreed(const std::string& breed);

    void undoLastAction();
    void redoLastAction();
    void clearUndoRedo();
    ~Service();
};

#endif //A45_911_BRINZA_ALINA_ELENA_SERVICE_H
