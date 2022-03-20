//
// Created by selen on 27/03/2021.
//

#include "testdynamicarray.h"
#include <cassert>
#include <cstring>

void testDynamicArray() {
    auto * dynamicArray = new DynamicArray<TElem>(1);
    assert(dynamicArray->capacityGetter() == 1);
    assert(dynamicArray->nrEntitiesGetter() == 0);
    try {
        auto * dynamicArrayInvalid = new DynamicArray<TElem>(0);
    } catch (const char *msg) {
        assert(strcmp(msg, "Can't have an array with less than an element!") == 0);
    }
    TElem element1 = nullptr;
    dynamicArray->addElem(element1);
    assert(dynamicArray->nrEntitiesGetter() == 1);
    TElem element2 = nullptr;
    dynamicArray->addElem(element2);
    assert(dynamicArray->nrEntitiesGetter() == 2);
    assert(dynamicArray->capacityGetter() == 2);
    TElem element3 = nullptr;
    dynamicArray->updateElem(1, element3);
    assert(dynamicArray->elemGetter()[1] == element3);
    TElem element4 = nullptr;
    dynamicArray->addElem(element4);
    dynamicArray->deleteElem(1);
    assert(dynamicArray->nrEntitiesGetter() == 2);
    assert(dynamicArray->elemGetter()[1] == element4);
}
