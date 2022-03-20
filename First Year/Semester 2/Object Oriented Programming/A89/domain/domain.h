#ifndef A45_911_BRINZA_ALINA_ELENA_DOMAIN_H
#define A45_911_BRINZA_ALINA_ELENA_DOMAIN_H
#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    int age;
    std::string photograph;
public:

    ///Constructor method for the Dog class
    ///\param breed - the breed of the dog, "empty" by default
    ///\param name - the name of the dog, "empty" by default
    ///\param age - the age of the dog, 0 by default
    ///\param photograph - the link of the photo of the dog, "empty" by default
    explicit Dog(std::string breed = "empty", std::string name = "empty", int age = 0, std::string photograph = "empty");

    ///Getter method for the breed
    ///\return - the breed of the dog
    std::string breedGetter() const;

    ///Getter method for the name
    ///\return - the name of the dog
    std::string nameGetter() const;

    ///Getter method for the age
    ///\return - the age of the dog
    int ageGetter() const;

    ///Getter method for the photograph
    ///\return - the link of the photo of the dog
    std::string photoGetter() const;

    ///Destructor of the class
    ~Dog();

    ///Method to format an entity into a string
    ///\return - the string format of a dog
    std::string toString() const;

    bool operator==(const Dog& dogToCheck) const;

    friend std::istream& operator>>(std::istream& inputStream, Dog& dog);

    friend std::ostream & operator<<(std::ostream& outputStream, const Dog& dogOutput);
};


#endif //A45_911_BRINZA_ALINA_ELENA_DOMAIN_H