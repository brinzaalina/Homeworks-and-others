#include <vector>
#include <sstream>
#include "Domain.h"

std::vector<std::string> tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

std::istream &operator>>(std::istream &inputStream, Object &object) {
    return inputStream;
}

std::ostream &operator<<(std::ostream &outputStream, const Object &object) {
    return outputStream;
}

bool Object::operator==(const Object &otherObject) const {
}
