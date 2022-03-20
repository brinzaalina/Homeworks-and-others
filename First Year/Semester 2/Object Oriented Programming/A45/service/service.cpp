#include "service.h"

Service::Service(Repository *repo) {
    this->repository = repo;
}

Dog* Service::getAllService() {
    return this->repository->getAllRepo();
}

int Service::getNrElemsService() {
    return this->repository->getNrElems();
}

int Service::getCapService() {
    return this->repository->getCap();
}

int Service::addService(string breed, string name, int age, string photograph) {
    int index;
    int length = this->repository->getNrElems();
    for (index = 0; index < length; index++) {
        string other_name = this->getAllService()[index].nameGetter();
        if (other_name == name)
            return 1;
    }
    this->repository->addRepo(Dog(breed, name, age, photograph));
    return 0;
}

int Service::deleteService(string name) {
    int delete_index = this->repository->findByName(name);
    if (delete_index == -1)
        return 1;
    else {
        this->repository->deleteRepo(delete_index);
        return 0;
    }
}

int Service::updateService(string old_name, string new_breed, string new_name, int new_age, string new_photo) {
    int update_index = this->repository->findByName(old_name);
    if (update_index == -1)
        return 1;
    Dog new_dog = Dog(new_breed, new_name, new_age, new_photo);
    this->repository->updateRepo(update_index, new_dog);
    return 0;
}

Service::~Service() = default;