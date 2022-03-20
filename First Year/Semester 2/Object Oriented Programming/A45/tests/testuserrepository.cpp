//
// Created by selen on 27/03/2021.
//

#include "testuserrepository.h"
#include <cassert>

void testUserRepository() {
    auto * dynamicArray1 = new DynamicArray<Dog>(2);
    UserRepository userRepository = UserRepository(dynamicArray1);
    assert(userRepository.getCap() == 2);
    Dog dog1 = Dog("German Shepherd", "Bond", 1, "https://www.wowwow.ro/ciobanesc-german-caine/2145#");
    Dog dog2 = Dog("Bulldog", "Yoda", 5, "https://www.wowwow.ro/bulldog-caine/2139");
    userRepository.addUserRepo(dog1);
    assert(userRepository.getNrElems() == 1);
    userRepository.addUserRepo(dog2);
    assert(userRepository.getAllUserRepo()[0].ageGetter() == 1);
    assert(userRepository.getAllUserRepo()[1].nameGetter() == "Yoda");
}