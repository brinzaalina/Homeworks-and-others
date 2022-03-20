#ifndef A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H
#define A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H

#include <repository.h>
#include <userrepository.h>
#include <memory>
#include "undoredo.h"

class UserService {
private:
    Repository& repository;
    UserRepository* userRepository;
    bool repoTypeSelected;
    std::vector<std::shared_ptr<UndoRedoAction>> undoUser;
    std::vector<std::shared_ptr<UndoRedoAction>> redoUser;
public:
    UserService(Repository& repository1, UserRepository* userRepository1);
    explicit UserService(Repository& repository1);
    std::vector<Dog> getAllUserService();
    unsigned int getNrElemsUserService();
    unsigned int getCapUserService();
    UserRepository* getUserRepo();
    void addUserService(const Dog& dog);
    void repositoryType(const std::string& fileType);
    std::string& getFileService();
    void undoLastAction();
    void redoLastAction();
    void clearUndoRedo();
    ~UserService();
};

#endif //A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H
