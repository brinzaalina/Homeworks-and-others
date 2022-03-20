#include <crtdbg.h>
#include <repository.h>
#include <service.h>
#include <console.h>

int main() {
    std::vector<Dog> adminRepoVector;
    adminRepoVector.reserve(10);
    std::string filename = R"(D:\GitHub\a67-911-Brinza-Alina-Elena\dogs.txt)";
    Repository repo{adminRepoVector, filename};
    repo.initialiseRepo();
    Service service{repo};
    UserService userService{repo};
    DogValidator validator{};
    Console console{service, userService, validator};
    console.start();
    _CrtDumpMemoryLeaks();
    return 0;
}

