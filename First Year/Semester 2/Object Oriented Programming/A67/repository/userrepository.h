#ifndef A45_911_BRINZA_ALINA_ELENA_USERREPOSITORY_H
#define A45_911_BRINZA_ALINA_ELENA_USERREPOSITORY_H


#include <vector>
#include <domain.h>

class UserRepository {
protected:
    std::vector<Dog> adoptionList;
    std::string userFilename;
public:
    ///Constructor for the UserRepository class
    ///\param adoptionList1 - the list of dogs that the user is adopting
    explicit UserRepository(std::vector<Dog>& adoptionList1);

    UserRepository();

    ///Method to get all the elements of the UserRepository
    ///\return - the list of elements from the UserRepository
    virtual std::vector<Dog>& getAllUserRepo()=0;

    ///Method to get the number of elements from the UserRepository
    ///\return - the number of elements
    virtual unsigned int getNrElems()=0;

    ///Method to get the capacity of the dynamic array used in the UserRepository
    ///\return - the capacity
    virtual unsigned int getCap()=0;

    ///Method to add an element to the UserRepository
    ///\param dog - the element to be added
    virtual void addUserRepo(const Dog& dog)=0;

    virtual void writeToFile()=0;

    virtual std::string& getFilename()=0;

    ///Destructor
    ~UserRepository();
};

class UserException: public std::exception {
private:
    std::string message;
public:
    explicit UserException(std::string& _message);

    const char *what() const noexcept override;
};
#endif //A45_911_BRINZA_ALINA_ELENA_USERREPOSITORY_H
