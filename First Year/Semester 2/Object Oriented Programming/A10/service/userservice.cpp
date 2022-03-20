#include "userservice.h"
#include <algorithm>
#include <CSVrepository.h>
#include <HTMLrepository.h>


UserService::UserService(Repository& repository1, UserRepository* userRepository1): repository(repository1) {
    this->userRepository = userRepository1;
    repoTypeSelected = false;
}

UserService::UserService(Repository &repository1): repository(repository1) {
    repoTypeSelected = false;
}

std::vector<Dog> UserService::getAllUserService() {
    return this->userRepository->getAllUserRepo();
}

unsigned int UserService::getNrElemsUserService() {
    if (this->userRepository->getNrElems() == 0) {
        std::string error;
        error += std::string("The list of adoptions is empty!");
        if(!error.empty())
            throw UserException(error);
    }
    return this->userRepository->getNrElems();
}

unsigned int UserService::getCapUserService() {
    return this->userRepository->getCap();
}

std::string& UserService::getFileService() {
    return this->userRepository->getFilename();
}

void UserService::addUserService(const Dog& dog) {
    this->userRepository->addUserRepo(dog);
    std::string name = dog.nameGetter();
    int delete_index = this->repository.findByName(name);
    this->repository.deleteRepo(delete_index);
    std::shared_ptr<UndoRedoAction> action = std::make_shared<UndoRedoUser>(dog, this->repository, this->userRepository);
    this->undoUser.push_back(action);
}

void UserService::repositoryType(const std::string& fileType) {
    std::vector<Dog> userVector;
    std::string userFile;
    if (fileType == "csv") {
        userFile = R"(D:\GitHub\a10-911-Brinza-Alina-Elena-1\AdoptionList.csv)";
        if (!repoTypeSelected) {
            repoTypeSelected = true;
        } else {
            userVector = this->getAllUserService();
        }
        auto* repo = new CSVRepo{userVector, userFile};
        this->userRepository = repo;
        this->userRepository->writeToFile();
    }else if (fileType == "html") {
        userFile = R"(D:\GitHub\a10-911-Brinza-Alina-Elena-1\AdoptionList.html)";
        if (!repoTypeSelected) {
            repoTypeSelected = true;
        } else {
            userVector = this->getAllUserService();
        }
        auto * repo = new HTMLRepo{userVector, userFile};
        this->userRepository = repo;
        this->userRepository->writeToFile();
    } else {
        std::string error;
        error += std::string("The filename is invalid!");
        if(!error.empty())
            throw UserException(error);
    }
}

UserRepository* UserService::getUserRepo() {
    return this->userRepository;
}

void UserService::undoLastAction() {
    if (this->undoUser.empty()) {
        std::string error;
        error += std::string("No more undoes left!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->undoUser.back()->undo();
    this->redoUser.push_back(this->undoUser.back());
    this->undoUser.pop_back();
}

void UserService::redoLastAction() {
    if (this->redoUser.empty()) {
        std::string error;
        error += std::string("No more redoes left!");
        if(!error.empty())
            throw RepositoryException(error);
    }
    this->redoUser.back()->redo();
    this->undoUser.push_back(this->redoUser.back());
    this->redoUser.pop_back();
}

void UserService::clearUndoRedo() {
    this->undoUser.clear();
    this->redoUser.clear();
}

UserService::~UserService() = default;