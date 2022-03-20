#include "userrepository.h"

UserRepository::UserRepository(DynamicArray<Dog> *adoptionList1) {
    this->adoptionList = adoptionList1;
}

Dog* UserRepository::getAllUserRepo() {
    return (Dog*)this->adoptionList->elemGetter();
}

int UserRepository::getNrElems() {
    return this->adoptionList->nrEntitiesGetter();
}

int UserRepository::getCap() {
    return this->adoptionList->capacityGetter();
}

void UserRepository::addUserRepo(const Dog &dog) {
    this->adoptionList->addElem(dog);
}

UserRepository::~UserRepository() = default;