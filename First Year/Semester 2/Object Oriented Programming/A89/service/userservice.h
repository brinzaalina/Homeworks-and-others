#ifndef A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H
#define A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H

#include <repository.h>
#include <userrepository.h>

class UserService {
private:
    Repository& repository;
    UserRepository* userRepository;
    bool repoTypeSelected;
public:

    ///Constructor for the UserService class
    ///\param repository1 - the admin repository
    ///\param userRepository1 - the user repository
    UserService(Repository& repository1, UserRepository* userRepository1);

    explicit UserService(Repository& repository1);

    ///Method to get all the elements from the user repository
    ///\return - the elements from the user repository
    std::vector<Dog> getAllUserService();

    ///Method to get the number of elements from the user repository
    ///\return - the number of elements
    unsigned int getNrElemsUserService();

    ///Method to get the capacity of the user repository
    ///\return - the capacity
    unsigned int getCapUserService();

    ///Method to add a new dog to the user repository
    ///\param dog - the dog to be added
    void addUserService(const Dog& dog);

    void repositoryType(const std::string& fileType);

    std::string& getFileService();

    ///Destructor
    ~UserService();
};

#endif //A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H
