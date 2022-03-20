//
// Created by selen on 30/05/2021.
//

#ifndef A10_911_BRINZA_ALINA_ELENA_1_UNDOREDO_H
#define A10_911_BRINZA_ALINA_ELENA_1_UNDOREDO_H

#include <repository.h>
#include <userrepository.h>

class UndoRedoAction {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~UndoRedoAction() = default;
};

class UndoRedoAdd: public UndoRedoAction {
private:
    Dog addedDog;
    Repository& repo;
public:
    UndoRedoAdd(const Dog& dog, Repository& newRepo);
    void undo() override;
    void redo() override;
    ~UndoRedoAdd() override = default;
};

class UndoRedoRemove: public UndoRedoAction {
private:
    Dog removedDog;
    Repository& repo;
public:
    UndoRedoRemove(const Dog& dog, Repository& newRepo);
    void undo() override;
    void redo() override;
    ~UndoRedoRemove() override = default;
};

class UndoRedoUpdate: public UndoRedoAction {
private:
    Dog oldDog;
    Dog newDog;
    Repository& repo;
public:
    UndoRedoUpdate(const Dog& oldDog, const Dog& newDog, Repository& newRepo);
    void undo () override;
    void redo() override;
    ~UndoRedoUpdate() override = default;
};

class UndoRedoUser: public UndoRedoAction {
private:
    Dog adoptedDog;
    Repository& repo;
    UserRepository* userRepo;
public:
    UndoRedoUser(const Dog& adoptedDog, Repository& newRepo, UserRepository *newUserRepo);
    void undo() override;
    void redo() override;
    ~UndoRedoUser() override = default;
};

#endif //A10_911_BRINZA_ALINA_ELENA_1_UNDOREDO_H
