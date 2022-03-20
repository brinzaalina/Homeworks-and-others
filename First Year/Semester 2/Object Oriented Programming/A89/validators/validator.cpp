//
// Created by selen on 11/04/2021.
//

#include "validator.h"

ValidationException::ValidationException(std::string &_message): message(_message) {}

const char* ValidationException::what() const noexcept {
    return message.c_str();
}
DogValidator::DogValidator() = default;

bool DogValidator::validateString(const std::string& input) {
    for (char i : input)
        if (isdigit(i) != false)
            return false;
    return true;
}

void DogValidator::validateBreed(const std::string& breed) {
    std::string errors;
    if (!validateString(breed))
        errors += std::string("The breed input contains digits!");
    if (breed.length() == 0)
        errors += std::string("The breed input is empty!");
    if (!errors.empty())
        throw ValidationException(errors);
}

void DogValidator::validateName(const std::string& name) {
    std::string errors;
    if (!validateString(name))
        errors += std::string("The name input contains digits!");
    if (name.length() == 0)
        errors += std::string("The name input is empty!");
    if (!isupper(name[0]))
        errors += std::string("The name should start with a capital letter!");
    if (!errors.empty())
        throw ValidationException(errors);
}

void DogValidator::validateAgeString(const std::string& age) {
    std::string errors;
    if (age.empty())
        errors += std::string("The age input is empty!");
    if (age.find_first_not_of("0123456789") != std::string::npos)
        errors += std::string("The age input has non-digit characters!");
    if(!errors.empty())
        throw ValidationException(errors);
}

void DogValidator::validateAge(int age) {
    std::string errors;
    if (age<0)
        errors += std::string("Age cannot be smaller than 0!");
    if(!errors.empty())
        throw ValidationException(errors);
}


void DogValidator::validatePhotoLink(const std::string& photograph) {
    std::string errors;
    if (photograph.length() == 0)
        errors += std::string("The link input is empty!");
    if (photograph.find("www") == std::string::npos)
        errors += std::string("The link is not a valid one!");
    if(!errors.empty())
        throw ValidationException(errors);
}

DogValidator::~DogValidator()=default;