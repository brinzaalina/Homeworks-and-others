//
// Created by selen on 27/03/2021.
//

#include "testrepository.h"
#include <cassert>

void testAdminRepository() {
    auto * dynamicArray = new DynamicArray<Dog>(10);
    Repository repo = Repository(dynamicArray);
    repo.initialiseRepo();
    assert(repo.getNrElems() == 10);
    assert(repo.getCap() == 10);
    assert(repo.getAllRepo()[0].nameGetter() == "Bond");
    Dog dog11 = Dog("Beagle", "Bimbo", 10, "https://www.wowwow.ro/beagle-caine/2133");
    repo.addRepo(dog11);
    assert(repo.getNrElems() == 11);
    assert(repo.getCap() == 20);
    assert(repo.findByName("Ice") == 4);
    repo.deleteRepo(4);
    assert(repo.getNrElems() == 10);
    Dog dog12 = Dog("Beagle", "Bimba", 11, "https://www.wowwow.ro/beagle-caine/2133");
    repo.updateRepo(9, dog12);
    assert(repo.getAllRepo()[9].nameGetter() == "Bimba");
    assert(repo.getAllRepo()[9].ageGetter() == 11);
}
