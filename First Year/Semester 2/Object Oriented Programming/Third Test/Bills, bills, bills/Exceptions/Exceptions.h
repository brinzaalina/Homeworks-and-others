#pragma once
#include <exception>
#include <string>

class ValidationException: public std::exception{
private:
    std::string message;

public:
    explicit ValidationException(std::string& errors);
    const char* what() const noexcept override;
};

class RepositoryException : public std::exception{
private:
    std::string message;

public:
    explicit RepositoryException(std::string& errors);
    const char* what() const noexcept override;
};