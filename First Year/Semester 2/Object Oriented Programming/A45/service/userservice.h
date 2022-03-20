#ifndef A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H
#define A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H

#include <repository.h>
#include <userrepository.h>

class UserService {
private:
    Repository * repository;
    UserRepository * userRepository;
public:
    ///Constructor for the UserService class
    ///\param repository1 - the admin repository
    ///\param userRepository1 - the user repository
    UserService(Repository * repository1, UserRepository * userRepository1);

    ///Method to get all the elements from the user repository
    ///\return - the elements from the user repository
    Dog * getAllUserService();

    ///Method to get the number of elements from the user repository
    ///\return - the number of elements
    int getNrElemsUserService();

    ///Method to get the capacity of the user repository
    ///\return - the capacity
    int getCapUserService();

    ///Method to add a new dog to the user repository
    ///\param dog - the dog to be added
    void addUserService(Dog dog);

    ///Method to get the filtered list of dogs based on their breed and age
    ///\param valid_dogs - the array of valid dogs
    ///\param filter_string - the breed filter
    ///\param age_filter - the age filter
    ///\return - the number of elements from the valid_dogs array
    int getFiltered(Dog * valid_dogs, string filter_string, int age_filter);

    ///Destructor
    ~UserService();
};
#endif //A45_911_BRINZA_ALINA_ELENA_USERSERVICE_H
