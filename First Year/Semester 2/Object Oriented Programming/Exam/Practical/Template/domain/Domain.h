#pragma once

#include <iostream>

class Object {
private:
public:
    Object() = default;
    ~Object() = default;

    friend std::istream& operator>>(std::istream& inputStream, Object& object);
    friend std::ostream& operator<<(std::ostream& outputStream, const Object& object);

    bool operator==(const Object& otherObject) const;
};
