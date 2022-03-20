#ifndef A45_911_BRINZA_ALINA_ELENA_REPOSITORY_H
#define A45_911_BRINZA_ALINA_ELENA_REPOSITORY_H


#include <vector>
#include <domain.h>

class Repository {
private:
    std::vector<Dog> adminRepositoryVector;
    std::string dogsFilename;

public:
    void loadDogsFromFile();

    void writeDogsToFile();

    ///Constructor for the Repository class
    ///\param repo_array - the dynamic array in which the dogs will be stored
    explicit Repository(std::vector<Dog>& repo_vector, std::string& dog_filename);

    ///Method to initialise the repository with a number of entities
    void initialiseRepo();

    ///Method to get all the elements of the repository
    ///\return - the array of elements
    std::vector<Dog>& getAllRepo();

    ///Method to get the number of elements in the repository
    ///\return - the number of elements
    unsigned int getNrElems();

    ///Method to get the capacity of the repository
    ///\return - the capacity
    unsigned int getCap();

    ///Method to add an element to the repository
    ///\param dog - the entity to be added
    void addRepo(const Dog& dog);

    ///Method to find an entity by name
    ///\param name - the name of the dog that we are searching for
    int findByName(const std::string& name);

    ///Method to delete an entity based on its index
    ///\param delete_index - the index of the dog to be deleted
    void deleteRepo(int delete_index);

    ///Method to update an entity based on its index with a new entity
    ///\param update_index - the index of the dog to be updated
    ///\param new_dog - the new dog with which the update is done
    void updateRepo(int update_index, const Dog& new_dog);

    ///Destructor
    ~Repository();
};

class RepositoryException: public std::exception {
private:
    std::string message;
public:
    explicit RepositoryException(std::string& _message);

    const char *what() const noexcept override;
};
#endif //A45_911_BRINZA_ALINA_ELENA_REPOSITORY_H

