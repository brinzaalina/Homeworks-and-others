#include "userservice.h"

UserService::UserService(Repository *repository1, UserRepository *userRepository1) {
    this->repository = repository1;
    this->userRepository = userRepository1;
}

Dog* UserService::getAllUserService() {
    return this->userRepository->getAllUserRepo();
}

int UserService::getNrElemsUserService() {
    return this->userRepository->getNrElems();
}

int UserService::getCapUserService() {
    return this->userRepository->getCap();
}

void UserService::addUserService(Dog dog) {
    this->userRepository->addUserRepo(dog);
    string name = dog.nameGetter();
    int delete_index = this->repository->findByName(name);
    this->repository->deleteRepo(delete_index);
}

int UserService::getFiltered(Dog * valid_dogs, string filter_string, int age_filter) {
    int index;
    int counter = 0;
    int length = this->repository->getNrElems();
    if (filter_string[0] == '\0')
        for (index = 0; index < length; index++) {
            Dog dog = this->repository->getAllRepo()[index];
            if (age_filter > dog.ageGetter()) {
                valid_dogs[counter] = dog;
                counter++;
            }
        }
    else {
        for (index = 0; index < length; index++) {
            Dog dog = this->repository->getAllRepo()[index];
            if (filter_string == dog.breedGetter() && age_filter > dog.ageGetter()) {
                valid_dogs[counter] = dog;
                counter++;
            }
        }
    }
    return counter;
}

UserService::~UserService() = default;