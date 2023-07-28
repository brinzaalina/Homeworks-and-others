//
// Created by selen on 19/05/2021.
//

#include "Exceptions.h"

ValidationException::ValidationException(std::string& errors): message{errors} {
}

const char* ValidationException::what() const noexcept{
    return this->message.c_str();
}

RepositoryException::RepositoryException(std::string& errors): message{errors} {
}

const char* RepositoryException::what() const noexcept{
    return this->message.c_str();
}