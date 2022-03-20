//
// Created by selen on 27/03/2021.
//

#include "testuserservice.h"
#include <cassert>

void testUserService() {
    auto * dynamicArray = new DynamicArray<Dog>(10);
    auto* repo = new Repository(dynamicArray);
    repo->initialiseRepo();
    auto * dynamicArray1 = new DynamicArray<Dog>(10);
    auto *userRepo = new UserRepository(dynamicArray1);
    UserService userService = UserService(repo, userRepo);
    assert(userService.getNrElemsUserService() == 0);
    assert(userService.getCapUserService() == 10);
    Dog dog = repo->getAllRepo()[0];
    userService.addUserService(dog);
    assert(userService.getNrElemsUserService() == 1);
    assert(userService.getAllUserService()[0].nameGetter() == "Bond");
    Dog * validDogs1 = new Dog[10];
    string empty;
    empty[0] = '\0';
    int counter1 = userService.getFiltered(validDogs1, empty, 11);
    assert(counter1 == 9);
    Dog * validDogs2 = new Dog[10];
    int counter2 = userService.getFiltered(validDogs2, "Husky", 11);
    assert(counter2 == 3);
}