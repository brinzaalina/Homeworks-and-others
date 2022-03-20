#include "console.h"
#include <iostream>

using namespace std;

Console::Console(Service *service, UserService * userService)
{
    this->service = service;
    this->userService = userService;
}

bool Console::validateString(string input) {
    for (int i = 0; i <input.length(); i++)
        if (isdigit(input[i]) != false)
            return false;
    return true;
}

void Console::addUi() {
    cout<<"Add a new dog"<<endl;
    string breed;
    string name;
    string age_s;
    string photograph;
    cout<<"Enter the breed: "<<endl;
    getline(cin, breed);
    if ((!validateString(breed)) || (breed.length() == 0))
        throw "Breed input not valid!";
    cout<<"Enter the name: "<<endl;
    getline(cin, name);
    if (!validateString(name) || name.length() == 0)
        throw "Name input not valid";
    cout<<"Enter the age: "<<endl;
    getline(cin, age_s);
    int age;
    if (!validateString(age_s) && age_s.length() != 0)
        age = stoi(age_s);
    else
        throw "Age input not valid!";
    if (age < 0)
        throw "Age cannot be smaller than 0!";
    cout<<"Enter the link to the photograph: "<<endl;
    getline(cin, photograph);
    if (photograph.length() == 0 || photograph.find("www") == string::npos)
        throw "Photograph link is not valid!";
    int added = this->service->addService(breed, name, age, photograph);
    if (added == 1)
        throw "This dog already exists!";
    else if (added == 0)
        cout<<"Dog added successfully!"<<endl;
}

void Console::deleteUi() {
    cout<<"Delete a dog"<<endl;
    string name;
    cout<<"Enter the name: "<<endl;
    getline(cin, name);
    if (!validateString(name) || name.length() == 0)
        throw "Name input is not valid!";
    int deleted = this->service->deleteService(name);
    if (deleted == 0)
        cout<<"Dog successfully deleted!"<<endl;
    else if (deleted == 1)
        throw "The dog does not exist!";
}

void Console::updateUi() {
    cout<<"Update a dog"<<endl;
    string old_name;
    string new_breed;
    string new_name;
    string new_age_s;
    string new_photograph;
    cout<<"Enter the old name: "<<endl;
    getline(cin, old_name);
    if (!validateString(old_name) || old_name.length() == 0)
        throw "Name input not valid!";
    cout<<"Enter the new breed: "<<endl;
    getline(cin, new_breed);
    if (!validateString(new_breed) || new_breed.length() == 0)
        throw "Breed input not valid!";
    cout<<"Enter the name: "<<endl;
    getline(cin, new_name);
    if (!validateString(new_name) || new_name.length() == 0)
        throw "Name input not valid!";
    cout<<"Enter the age: "<<endl;
    getline(cin, new_age_s);
    int new_age;
    if (!validateString(new_age_s) && new_age_s.length() != 0)
        new_age = stoi(new_age_s);
    else
        throw "Age input not valid!";
    if (new_age < 0)
        throw "Age cannot be smaller than 0!";
    cout<<"Enter the link to the photograph: "<<endl;
    getline(cin, new_photograph);
    if (new_photograph.length() == 0 || new_photograph.find("www") == string::npos)
        throw "Photograph link is not valid!";
    int updated = this->service->updateService(old_name, new_breed, new_name, new_age, new_photograph);
    if (updated == 1)
        throw "The dog does not exist!";
    else if (updated == 0)
        cout<<"Dog updated successfully!"<<endl;
}

void Console::listAll() {
    Dog *dogs = this->service->getAllService();
    int index;
    int elemNo = this->service->getNrElemsService();
    if (elemNo == 0)
        throw "No dogs in the database!";
    for (index = 0; index <elemNo; index++)
        cout << index + 1 << ". " << dogs[index].toString() << endl;
}

void Console::listAllUser() {
    string option;
    bool done = false;
    int index = 0;
    int length = this->service->getNrElemsService();
    if (length == 0)
        throw "No dogs in the database!";
    while (!done) {
        if (length == 0)
            throw "No dogs remained!";
        if (index == length)
            index = 0;
        cout<< this->service->getAllService()[index].toString() << endl;
        cout<<"Adopt? [Yes / No / exit]"<<endl;
        string link = string("start ").append(this->service->getAllService()[index].photoGetter());
        system(link.c_str());
        getline(cin, option);
        if (option == "Yes") {
            Dog dog = this->service->getAllService()[index];
            this->userService->addUserService(dog);
            length = this->service->getNrElemsService();
        }
        else if (option == "No") {
            index++;
        }
        else if (option == "exit")
            done = true;
        if (length == 0)
            done = true;
    }
}

void Console::listFilteredUser() {
    string breed_filter;
    string age_filter_s;
    int age_filter;
    cout<<"Enter the breed: "<<endl;
    getline(cin,breed_filter);
    if (!validateString(breed_filter))
        throw "Input not valid!";
    cout<<"Enter the age: "<<endl;
    getline(cin, age_filter_s);
    if (!validateString(age_filter_s) && age_filter_s.length() != 0)
        age_filter = stoi(age_filter_s);
    if (age_filter < 0)
        throw "Age cannot be smaller than 0!";
    auto * validDogs = new Dog [this->service->getCapService()];
    int length = this->userService->getFiltered(validDogs, breed_filter, age_filter);
    if (length == 0)
        throw "No dogs corresponding!";
    string option;
    bool done = false;
    int index = 0;
    while (!done){
        if (length == 0)
            throw "No dogs remained!";
        if (index == length)
            index = 0;
        cout<< validDogs[index].toString() << endl;
        cout<<"Adopt? [Yes / No / exit]"<<endl;
        string link = string("start ").append(validDogs[index].photoGetter());
        system(link.c_str());
        getline(cin, option);
        if (option == "Yes") {
            Dog dog = validDogs[index];
            this->userService->addUserService(dog);
            for (int i = index; i < length - 1; i++)
                validDogs[i] = validDogs[i + 1];
            length--;
        }
        else if (option == "No") {
            index++;
        }
        else if (option == "exit")
            done = true;
    }
}

void Console::listAdoptionList() {
    Dog * adoptions = this->userService->getAllUserService();
    int index;
    int elemNo = this->userService->getNrElemsUserService();
    if (elemNo == 0)
        throw "The list is empty!";
    for (index = 0; index < elemNo; index++)
        cout<< index + 1 << ". " << adoptions[index].toString() << endl;
}

void Console::printAdministratorSubmenu() {
    cout<<"ADMINISTRATOR MENU: "<<endl;
    cout<<"0. Exit"<<endl;
    cout<<"1. List all the dogs from the shelter."<<endl;
    cout<<"2. Add a new dog."<<endl;
    cout<<"3. Delete a dog."<<endl;
    cout<<"4. Update a dog."<<endl;
    cout<<"Choose an option: "<<endl;
}

void Console::printUserSubmenu() {
    cout<<"USER MENU: "<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. See all the dogs in the database, one by one."<<endl;
    cout<<"2. See all the dogs of a given breed, having an age less than a given number."<<endl;
    cout<<"3. See the adoption list."<<endl;
    cout<<"Choose an option: "<<endl;
}

void Console::AdministratorMode() {
    cout<<"~You entered the administrator mode~"<<endl;
    bool done = false;
    while (!done) {
        try {
            printAdministratorSubmenu();
            string option;
            getline(cin, option);
            if (option == "0") {
                done = true;
                cout << "Exiting admin mode..." << endl;
            } else if (option == "1")
                this->listAll();
            else if (option == "2")
                this->addUi();
            else if (option == "3")
                this->deleteUi();
            else if (option == "4")
                this->updateUi();
            else
                cout << "Bad input!"<<endl;
        }catch (const char *msg) {
            cout<<msg<<endl;
        }catch (const exception &exc){
            cerr<<exc.what();
            cout<<endl;
        }
    }
}

void Console::UserMode() {
    cout<<"~You entered the user mode~"<<endl;
    bool done = false;
    while(!done) {
        try {
            printUserSubmenu();
            string option;
            getline(cin, option);
            if (option == "0") {
                done = true;
                cout<<"Exiting user mode..."<<endl;
            }
            else if (option == "1")
                this->listAllUser();
            else if (option == "2")
                this->listFilteredUser();
            else if (option == "3")
                this->listAdoptionList();
            else
                cout<<"Bad input!"<<endl;
        }catch (const char *msg) {
            cout<<msg<<endl;
        }catch (const exception &exc) {
            cerr<<exc.what();
            cout<<endl;
        }
    }
}

void Console::printMenu() {
    cout<<"MENU:"<<endl;
    cout<<"0. Exit."<<endl;
    cout<<"1. Administrator mode."<<endl;
    cout<<"2. User mode."<<endl;
    cout<<"Choose an option: "<<endl;
}

void Console::start() {
    cout<<"~Keep calm and adopt a pet shelter app~"<<endl;
    bool done = false;
    while (!done) {
        printMenu();
        string option;
        getline(cin,option);
        if (option == "1")
            AdministratorMode();
        else if (option == "2")
            UserMode();
        else if (option == "0") {
            done = true;
            cout << "Goodbye!" << endl;
        }else
            cout<<"Bad input!"<<endl;
    }


}

Console::~Console() = default;