#include <fstream>
#include "userrepository.h"

UserException::UserException(std::string &_message): message(_message) {}

const char* UserException::what() const noexcept {
    return message.c_str();
}

UserRepository::UserRepository() = default;

UserRepository::UserRepository(std::vector<Dog>& adoptionList1) {
    this->adoptionList = adoptionList1;
}

UserRepository::~UserRepository() = default;