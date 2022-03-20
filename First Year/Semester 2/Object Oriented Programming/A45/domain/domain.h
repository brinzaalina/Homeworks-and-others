#ifndef A45_911_BRINZA_ALINA_ELENA_DOMAIN_H
#define A45_911_BRINZA_ALINA_ELENA_DOMAIN_H
#include <string>
using namespace std;

class Dog {
    private:
        string breed;
        string name;
        int age;
        string photograph;
    public:

    ///Constructor method for the Dog class
    ///\param breed - the breed of the dog, "empty" by default
    ///\param name - the name of the dog, "empty" by default
    ///\param age - the age of the dog, 0 by default
    ///\param photograph - the link of the photo of the dog, "empty" by default
    Dog(string breed = "empty", string name = "empty", int age = 0, string photograph = "empty");

    ///Getter method for the breed
    ///\return - the breed of the dog
    string breedGetter();

    ///Getter method for the name
    ///\return - the name of the dog
    string nameGetter();

    ///Getter method for the age
    ///\return - the age of the dog
    int ageGetter();

    ///Getter method for the photograph
    ///\return - the link of the photo of the dog
    string photoGetter();

    ///Destructor of the class
    ~Dog();

    ///Method to format an entity into a string
    ///\return - the string format of a dog
    string toString() const;
};

#endif //A45_911_BRINZA_ALINA_ELENA_DOMAIN_H
