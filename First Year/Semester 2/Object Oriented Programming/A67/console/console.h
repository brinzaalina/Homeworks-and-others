#ifndef A45_911_BRINZA_ALINA_ELENA_CONSOLE_H
#define A45_911_BRINZA_ALINA_ELENA_CONSOLE_H
#include <service.h>
#include <userservice.h>
#include <validator.h>

class Console {
private:
    Service& service;
    UserService& userService;
    DogValidator& validator;
public:
    Console(Service& service, UserService& userService, DogValidator& validator1);

    void addUi();

    void deleteUi();

    void updateUi();

    void listAll();

    void listAllUser();

    void listFilteredUser();

    void listAdoptionList();

    void openFile();

    static void printAdministratorSubmenu();

    static void printUserSubmenu();

    void AdministratorMode();

    void UserMode();

    static void printMenu();

    void start();

    ~Console();
};
#endif //A45_911_BRINZA_ALINA_ELENA_CONSOLE_H
