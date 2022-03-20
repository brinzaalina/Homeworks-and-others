//
// Created by selen on 30/05/2021.
//

#include "undoredo.h"

UndoRedoAdd::UndoRedoAdd(const Dog &dog, Repository &newRepo): addedDog(dog), repo(newRepo){

}

void UndoRedoAdd::undo() {
    int index = this->repo.findByName(this->addedDog.nameGetter());
    this->repo.deleteRepo(index);
}

void UndoRedoAdd::redo() {
    this->repo.addRepo(this->addedDog);
}

UndoRedoRemove::UndoRedoRemove(const Dog &dog, Repository &newRepo): removedDog(dog), repo(newRepo) {

}

void UndoRedoRemove::undo() {
    this->repo.addRepo(this->removedDog);
}

void UndoRedoRemove::redo() {
    int index = this->repo.findByName(this->removedDog.nameGetter());
    this->repo.deleteRepo(index);
}

UndoRedoUpdate::UndoRedoUpdate(const Dog &oldDog, const Dog &newDog, Repository &newRepo): oldDog(oldDog), newDog(newDog), repo(newRepo) {

}

void UndoRedoUpdate::undo() {
    int index = this->repo.findByName(this->newDog.nameGetter());
    this->repo.updateRepo(index, this->oldDog);
}

void UndoRedoUpdate::redo() {
    int index = this->repo.findByName(this->oldDog.nameGetter());
    this->repo.updateRepo(index, this->newDog);
}

UndoRedoUser::UndoRedoUser(const Dog &adoptedDog, Repository &newRepo, UserRepository *newUserRepo): adoptedDog(adoptedDog), repo(newRepo){
    this->userRepo = newUserRepo;
}

void UndoRedoUser::undo() {
    this->userRepo->deleteUserRepo(adoptedDog);
    this->repo.addRepo(adoptedDog);
}

void UndoRedoUser::redo() {
    int index = this->repo.findByName(this->adoptedDog.nameGetter());
    this->userRepo->addUserRepo(adoptedDog);
    this->repo.deleteRepo(index);
}
