#ifndef A45_911_BRINZA_ALINA_ELENA_CONSOLE_H
#define A45_911_BRINZA_ALINA_ELENA_CONSOLE_H

#include <service.h>
#include <userservice.h>

class Console {
private:
    Service *service;
    UserService * userService;
public:
    Console(Service *service, UserService * userService);

    ///Method to check if a given string does not contain digits
    ///\param input - the string to be verified
    ///\return - true if it is valid, false otherwise
    static bool validateString(string input);

    void addUi();

    void deleteUi();

    void updateUi();

    void listAll();

    void listAllUser();

    void listFilteredUser();

    void listAdoptionList();

    static void printAdministratorSubmenu();

    static void printUserSubmenu();

    void AdministratorMode();

    void UserMode();

    static void printMenu();

    void start();

    ~Console();
};

#endif //A45_911_BRINZA_ALINA_ELENA_CONSOLE_H
