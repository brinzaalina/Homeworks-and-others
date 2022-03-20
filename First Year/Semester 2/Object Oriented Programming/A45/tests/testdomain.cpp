//
// Created by selen on 27/03/2021.
//

#include "testdomain.h"
#include <cassert>
#include <cstring>

void testDomain() {
    Dog newDog("Amstaff", "Buds", 5, "https://www.wowwow.ro/amstaff-caine/2132");
    assert(newDog.breedGetter() == "Amstaff");
    assert(newDog.nameGetter() == "Buds");
    assert(newDog.ageGetter() == 5);
    assert(newDog.photoGetter() == "https://www.wowwow.ro/amstaff-caine/2132");
    auto str_age = to_string(newDog.ageGetter());
    string str = newDog.toString();
    assert(str == "Breed: Amstaff | Name: Buds | Age: 5 | Photograph link: https://www.wowwow.ro/amstaff-caine/2132");
    try {
        Dog newInvalid("Beagle", "Bimbo", -1, "https://www.wowwow.ro/beagle-caine/2133");
    }catch (const char* msg) {
        assert(strcmp(msg, "Age can't be smaller than 0!") == 0);
    }
}
