//
// Created by selen on 27/03/2021.
//

#include "testservice.h"
#include <cassert>

void testAdminService() {
    auto *dynamicArray = new DynamicArray<Dog>(10);
    auto *repo = new Repository(dynamicArray);
    repo->initialiseRepo();
    Service service = Service(repo);
    assert(service.getAllService()[0].nameGetter() == "Bond");
    assert(service.getCapService() == 10);
    assert(service.getNrElemsService() == 10);
    int added = service.addService("Beagle", "Jim", 10, "https://www.wowwow.ro/beagle-caine/2133");
    assert(added == 0);
    assert(service.getNrElemsService() == 11);
    assert(service.getCapService() == 20);
    added = service.addService("Beagle", "Jim", 10, "https://www.wowwow.ro/beagle-caine/2133");
    assert(added == 1);
    int deleted = service.deleteService("Jim");
    assert(deleted == 0);
    assert(service.getNrElemsService() == 10);
    deleted = service.deleteService("Jim");
    assert(deleted == 1);
    int updated = service.updateService("Jedi", "Beagle", "Jim", 2, "https://www.wowwow.ro/beagle-caine/2133");
    assert(updated == 0);
    updated = service.updateService("Azorel", "Beagle", "Jim", 2, "https://www.wowwow.ro/beagle-caine/2133");
    assert(updated == 1);
}