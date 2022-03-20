#ifndef A45_911_BRINZA_ALINA_ELENA_SERVICE_H
#define A45_911_BRINZA_ALINA_ELENA_SERVICE_H

#include <repository.h>

class Service{
private:
    Repository& repository;
public:
    ///Constructor for the Service class
    ///\param repo - the admin repository
    explicit Service(Repository& repo);

    ///Method to get all the elements of the repository
    ///\return - the elements from the repository
    std::vector<Dog> getAllService();

    ///Method to get the number of elements from the repository
    ///\return - the number of elements from the repository
    unsigned int getNrElemsService();

    ///Method to get the capacity of the repository
    ///\return - the capacity
    unsigned int getCapService();

    ///Method to add an element to the repository
    ///\param breed - the breed of the dog
    ///\param name - the name of the dog
    ///\param age - the age of the dog
    ///\param photograph - the link of the photograph of the dog
    ///\return - 1 if not added, 0 otherwise
    void addService(const std::string& breed, const std::string& name, int age, const std::string& photograph);

    ///Method to delete an element from the repository
    ///\param name - the name of the dog to be deleted
    ///\return - 1 if not deleted, 0 otherwise
    void deleteService(const std::string& name);

    ///Method to update an element from the repository
    ///\param old_name - the old name of the dog
    ///\param new_breed - the new breed of the dog
    ///\param new_name - the new name of the dog
    ///\param new_age - the new age of the dog
    ///\param new_photo - the new link to the photograph
    ///\return - 1 if not updated, 0 otherwise
    void updateService(const std::string& old_name, const std::string& new_breed, const std::string& new_name, int new_age,const std::string& new_photo);

    ///Method to get the filtered list of dogs based on their breed and age
    ///\param valid_dogs - the array of valid dogs
    ///\param filter_string - the breed filter
    ///\param age_filter - the age filter
    void getFiltered(std::vector<Dog> &valid_dogs, const std::string &filter_string, int age_filter);

    ///Destructor
    ~Service();
};

#endif //A45_911_BRINZA_ALINA_ELENA_SERVICE_H
