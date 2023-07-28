//
// Created by selen on 19/06/2021.
//

#include "Exceptions.h"

const char *RepositoryException::what() const noexcept {
    return this->message.c_str();
}

const char *ServiceException::what() const noexcept {
    return this->message.c_str();
}
