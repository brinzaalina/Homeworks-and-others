//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <dynamicarray.h>
#include <repository.h>
#include <service.h>
#include <console.h>
#include <../tests/testdomain.h>
#include <../tests/testdynamicarray.h>
#include <../tests/testrepository.h>
#include <../tests/testuserrepository.h>
#include <../tests/testservice.h>
#include <../tests/testuserservice.h>

void testAll() {
    testDomain();
    testDynamicArray();
    testAdminRepository();
    testUserRepository();
    testAdminService();
    testUserService();
}

int main() {
    auto * dynamicArray = new DynamicArray<Dog>(10);
    auto* repo = new Repository(dynamicArray);
    repo->initialiseRepo();
    auto * dynamicArray1 = new DynamicArray<Dog>(10);
    auto *userRepo = new UserRepository(dynamicArray1);
    auto* service = new Service(repo);
    auto * userService = new UserService(repo, userRepo);
    auto* console = new Console(service, userService);
    console->start();
    return 0;
}

//int main() {
//    testAll();
//    return 0;
//}


