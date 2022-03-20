#include "console.h"
#include <iostream>

Console::Console(Service& service, UserService& userService, DogValidator& validator1): service(service), userService(userService), validator(validator1){
}

void Console::addUi() {
    std::cout << "Add a new dog" << std::endl;
    std::string breed;
    std::string name;
    std::string age_s;
    int age;
    std::string photograph;
    while(true){
        try {
            std::cout << "Enter the breed: " << std::endl;
            getline(std::cin, breed);
            this->validator.validateBreed(breed);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while(true) {
        try {
            std::cout << "Enter the name: " << std::endl;
            getline(std::cin, name);
            this->validator.validateName(name);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the age: " << std::endl;
            getline(std::cin, age_s);
            this->validator.validateAgeString(age_s);
            age = stoi(age_s);
            this->validator.validateAge(age);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the link to the photograph: " << std::endl;
            getline(std::cin, photograph);
            this->validator.validatePhotoLink(photograph);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    this->service.addService(breed, name, age, photograph);
    std::cout << "Dog added successfully!" << std::endl;
}

void Console::deleteUi() {
    std::cout<<"Delete a dog"<<std::endl;
    std::string name;
    while(true) {
        try {
            std::cout << "Enter the name: " << std::endl;
            getline(std::cin, name);
            this->validator.validateName(name);
            break;
        } catch (ValidationException &ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    this->service.deleteService(name);
    std::cout<<"Dog successfully deleted!"<<std::endl;
}

void Console::updateUi() {
    std::cout<<"Update a dog"<<std::endl;
    std::string old_name;
    std::string new_breed;
    std::string new_name;
    std::string new_age_s;
    std::string new_photograph;
    while(true) {
        try {
            std::cout << "Enter the old name: " << std::endl;
            getline(std::cin, old_name);
            this->validator.validateName(old_name);
            break;
        } catch (ValidationException &ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while(true){
        try {
            std::cout << "Enter the new breed: " << std::endl;
            getline(std::cin, new_breed);
            this->validator.validateBreed(new_breed);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while(true) {
        try {
            std::cout << "Enter the new name: " << std::endl;
            getline(std::cin, new_name);
            this->validator.validateName(new_name);
            break;
        } catch (ValidationException &ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    int new_age;
    while (true) {
        try {
            std::cout << "Enter the new age: " << std::endl;
            getline(std::cin, new_age_s);
            this->validator.validateAgeString(new_age_s);
            new_age = stoi(new_age_s);
            this->validator.validateAge(new_age);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    while (true) {
        try {
            std::cout << "Enter the new link to the photograph: " << std::endl;
            getline(std::cin, new_photograph);
            this->validator.validatePhotoLink(new_photograph);
            break;
        }catch (ValidationException& ex) {
            std::cout << ex.what() << std::endl;
        }
    }
    this->service.updateService(old_name, new_breed, new_name, new_age, new_photograph);
    std::cout<<"Dog updated successfully!"<<std::endl;
}

void Console::listAll() {
    std::vector<Dog> dogs;
    dogs = this->service.getAllService();
    int index = 0;
    for (const Dog& dog: dogs) {
        std::cout << index + 1 << ". " << dog.toString() << std::endl;
        index++;
    }
}

void Console::listAllUser() {
    std::string option;
    bool done = false;
    int index = 0;
    unsigned int length = this->service.getNrElemsService();
    while (!done) {
        if (length == 0) {
            std::string error;
            error += std::string("The database is empty!");
            if(!error.empty())
                throw RepositoryException(error);
        }
        if (index == length)
            index = 0;
        std::cout<< this->service.getAllService()[index].toString() << std::endl;
        std::cout<<"Adopt? [Yes / No / exit]"<<std::endl;
        std::string link = std::string("start ").append(this->service.getAllService()[index].photoGetter());
        system(link.c_str());
        getline(std::cin, option);
        if (option == "Yes") {
            Dog dog = this->service.getAllService()[index];
            this->userService.addUserService(dog);
            length = this->service.getNrElemsService();
        }
        else if (option == "No") {
            index++;
        }
        else if (option == "exit")
            done = true;
        else
            std::cout<<"Invalid input!"<<std::endl;
        if (length == 0)
            done = true;
    }
}

void Console::listFilteredUser() {
    std::string breed_filter;
    std::string age_filter_s;
    int age_filter;
    std::cout<<"Enter the breed: "<<std::endl;
    getline(std::cin,breed_filter);
    if (!this->validator.validateString(breed_filter)) {
        std::string error;
        error += std::string("Filter not valid!");
        if(!error.empty())
            throw ValidationException(error);
    }
    std::cout<<"Enter the age: "<<std::endl;
    getline(std::cin, age_filter_s);
    this->validator.validateAgeString(age_filter_s);
    age_filter = stoi(age_filter_s);
    this->validator.validateAge(age_filter);
    std::vector<Dog> validDogs;
    validDogs.reserve(this->service.getNrElemsService());
    this->service.getFiltered(validDogs, breed_filter, age_filter);
    if (validDogs.empty()) {
        std::string error;
        error += std::string("The list of valid dogs is empty!");
        if(!error.empty())
            throw UserException(error);
    }
    std::string option;
    bool done = false;
    int index = 0;
    while (!done){
        if (validDogs.empty()) {
            std::string error;
            error += std::string("The list of valid dogs is empty!");
            if(!error.empty())
                throw UserException(error);
        }
        if (index == validDogs.size())
            index = 0;
        std::cout<< validDogs[index].toString() << std::endl;
        std::cout<<"Adopt? [Yes / No / exit]"<<std::endl;
        std::string link = std::string("start ").append(validDogs[index].photoGetter());
        system(link.c_str());
        getline(std::cin, option);
        if (option == "Yes") {
            Dog dog = validDogs[index];
            this->userService.addUserService(dog);
            validDogs.erase(validDogs.begin() + index);
        }
        else if (option == "No") {
            index++;
        }
        else if (option == "exit")
            done = true;
        else
            std::cout<<"Invalid input!"<<std::endl;
    }
}

void Console::listAdoptionList() {
    std::vector<Dog> adoptions;
    adoptions = this->userService.getAllUserService();
    int index = 0;
    for (const Dog &dog: adoptions) {
        std::cout << index + 1 << ". " << dog.toString() << std::endl;
        index++;
    }
}

void Console::openFile() {
    std::string link = std::string("start ").append(this->userService.getFileService());
    system(link.c_str());
}

void Console::printAdministratorSubmenu() {
    std::cout<<"ADMINISTRATOR MENU: "<<std::endl;
    std::cout<<"0. Exit"<<std::endl;
    std::cout<<"1. List all the dogs from the shelter."<<std::endl;
    std::cout<<"2. Add a new dog."<<std::endl;
    std::cout<<"3. Delete a dog."<<std::endl;
    std::cout<<"4. Update a dog."<<std::endl;
    std::cout<<"Choose an option: "<<std::endl;
}

void Console::printUserSubmenu() {
    std::cout<<"USER MENU: "<<std::endl;
    std::cout<<"0. Exit."<<std::endl;
    std::cout<<"1. See all the dogs in the database, one by one."<<std::endl;
    std::cout<<"2. See all the dogs of a given breed, having an age less than a given number."<<std::endl;
    std::cout<<"3. See the adoption list."<<std::endl;
    std::cout<<"4. See the adoption list file."<<std::endl;
    std::cout<<"Choose an option: "<<std::endl;
}

void Console::AdministratorMode() {
    std::cout<<"~You entered the administrator mode~"<<std::endl;
    bool done = false;
    while (!done) {
        try {
            printAdministratorSubmenu();
            std::string option;
            getline(std::cin, option);
            if (option == "0") {
                done = true;
                std::cout << "Exiting admin mode..." << std::endl;
            } else if (option == "1")
                this->listAll();
            else if (option == "2")
                this->addUi();
            else if (option == "3")
                this->deleteUi();
            else if (option == "4")
                this->updateUi();
            else
                std::cout << "Bad input!"<<std::endl;
        }catch (ValidationException& ex) {
            std::cout<<ex.what()<<std::endl;
        }catch (RepositoryException& ex) {
            std::cout<<ex.what()<<std::endl;
        }
    }
}

void Console::UserMode() {
    std::cout<<"~You entered the user mode~"<<std::endl;
    bool done = false;
    while(!done) {
        try {
            printUserSubmenu();
            std::string option;
            getline(std::cin, option);
            if (option == "0") {
                done = true;
                std::cout<<"Exiting user mode..."<<std::endl;
            }
            else if (option == "1")
                this->listAllUser();
            else if (option == "2")
                this->listFilteredUser();
            else if (option == "3")
                this->listAdoptionList();
            else if (option == "4")
                this->openFile();
            else
                std::cout<<"Bad input!"<<std::endl;
        }catch (ValidationException& ex) {
            std::cout<<ex.what()<<std::endl;
        }catch (UserException& ex) {
            std::cout<<ex.what()<<std::endl;
        }catch (RepositoryException& ex) {
            std::cout<<ex.what()<<std::endl;
        }
    }
}

void Console::printMenu() {
    std::cout<<"MENU:"<<std::endl;
    std::cout<<"0. Exit."<<std::endl;
    std::cout<<"1. Administrator mode."<<std::endl;
    std::cout<<"2. User mode."<<std::endl;
    std::cout<<"Choose an option: "<<std::endl;
}

void Console::start() {
    std::cout<<"~Keep calm and adopt a pet shelter app~"<<std::endl;
    int usermode = 0;
    bool done = false;
    while (!done) {
        printMenu();
        std::string option;
        getline(std::cin,option);
        if (option == "1")
            AdministratorMode();
        else if (option == "2") {
            if (usermode == 0) {
                std::cout<<"Enter the type of the file in which you want to save the adoption list(csv or html):"<<std::endl;
                std::string fileType;
                while (true) {
                    try {
                        getline(std::cin, fileType);
                        this->userService.repositoryType(fileType);
                        break;
                    }catch (UserException& ex) {
                        std::cout<<ex.what()<<std::endl;
                    }
                }
                usermode = 1;
            }
            UserMode();
        }else if (option == "0") {
            done = true;
            std::cout << "Goodbye!" << std::endl;
        }else
            std::cout<<"Bad input!"<<std::endl;
    }


}

Console::~Console() = default;
