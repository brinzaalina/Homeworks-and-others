#include "repository.h"

Repository::Repository(DynamicArray<Dog> *repo_array) {
    this->dynamicArray = repo_array;
}

void Repository::initialiseRepo() {
    Dog dog1 = Dog("German Shepherd", "Bond", 1, "https://www.wowwow.ro/ciobanesc-german-caine/2145#");
    Dog dog2 = Dog("Husky", "Yoda", 5, "https://www.wowwow.ro/husky-caine/2152");
    Dog dog3 = Dog("Golden Retriever", "Murray", 3, "https://www.wowwow.ro/golden-retriever-caine/2151");
    Dog dog4 = Dog("Poodle", "Baby", 2, "https://www.wowwow.ro/pudel-standard-%28caniche%29-caine/2163");
    Dog dog5 = Dog("Husky", "Ice", 7, "https://www.wowwow.ro/husky-caine/2152");
    Dog dog6 = Dog("Samoyed", "Bear", 0, "https://www.wowwow.ro/samoyed-caine/2298");
    Dog dog7 = Dog("Husky", "Hudson", 10, "https://www.wowwow.ro/husky-caine/2152");
    Dog dog8 = Dog("Akita Inu", "Dash", 3, "https://www.wowwow.ro/akita-inu-caine/2131");
    Dog dog9 = Dog("Akita Inu", "Geo", 6, "https://www.wowwow.ro/akita-inu-caine/2131");
    Dog dog10 = Dog("Corgi", "Jedi", 1, "https://www.wowwow.ro/welsh-corgi-pembroke-caine/2332");
    this->dynamicArray->addElem(dog1);
    this->dynamicArray->addElem(dog2);
    this->dynamicArray->addElem(dog3);
    this->dynamicArray->addElem(dog4);
    this->dynamicArray->addElem(dog5);
    this->dynamicArray->addElem(dog6);
    this->dynamicArray->addElem(dog7);
    this->dynamicArray->addElem(dog8);
    this->dynamicArray->addElem(dog9);
    this->dynamicArray->addElem(dog10);
}

Dog* Repository::getAllRepo() {
    return (Dog*)this->dynamicArray->elemGetter();
}

int Repository::getNrElems() {
    return this->dynamicArray->nrEntitiesGetter();
}

int Repository::getCap() {
    return this->dynamicArray->capacityGetter();
}

void Repository::addRepo(const Dog& dog) {
    this->dynamicArray->addElem(dog);
}

int Repository::findByName(string name) {
    int searched_index = -1;
    int index = 0;
    int length = this->getNrElems();
    while(index < length && searched_index == -1) {
        Dog someDog = this->dynamicArray->elemGetter()[index];
        string other_name = someDog.nameGetter();
        if (other_name == name)
            searched_index = index;
        index++;
    }
    return searched_index;
}

void Repository::deleteRepo(int delete_index) {
    this->dynamicArray->deleteElem(delete_index);
}

void Repository::updateRepo(int update_index, const Dog& new_dog) {
    this->dynamicArray->updateElem(update_index, new_dog);
}

Repository::~Repository() = default;