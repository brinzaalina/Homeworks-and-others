//
// Created by selen on 11/04/2021.
//

#ifndef A45_911_BRINZA_ALINA_ELENA_VALIDATOR_H
#define A45_911_BRINZA_ALINA_ELENA_VALIDATOR_H
#include "domain.h"

class ValidationException: public std::exception {
private:
    std::string message;
public:
    explicit ValidationException(std::string& _message);

    const char *what() const noexcept override;
};

class DogValidator {
public:
    DogValidator();

    bool validateString(const std::string& input);

    void validateBreed(const std::string& breed);

    void validateName(const std::string& name);

    void validateAgeString(const std::string& age);

    void validateAge(int age);

    void validatePhotoLink(const std::string& photograph);

    ~DogValidator();
};

#endif //A45_911_BRINZA_ALINA_ELENA_VALIDATOR_H
