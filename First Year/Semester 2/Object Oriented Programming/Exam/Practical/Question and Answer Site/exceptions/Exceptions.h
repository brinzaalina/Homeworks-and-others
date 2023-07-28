#pragma once

#include <exception>
#include <string>

class RepositoryException: public std::exception {
private:
    std::string message;
public:
    explicit RepositoryException(std::string error): message{ std::move(error) } {}
    const char* what() const noexcept override;
};

class ServiceException: public std::exception {
private:
    std::string message;
public:
    explicit ServiceException(std::string error): message{ std::move(error) } {}
    const char* what() const noexcept override;
};