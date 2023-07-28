//
// Created by selen on 21/05/2021.
//

#pragma once

#include <string>
#include <vector>
#include <sstream>

class Vegetable {
private:
    std::string family;
    std::string name;
    std::vector<std::string> consumables;
public:
    Vegetable();
    Vegetable(const std::string& family, const std::string& name, std::vector<std::string>& consumables);
    Vegetable(const Vegetable& vegetable);

    std::string getFamily() const;
    std::string getName() const;
    std::vector<std::string> getConsumables();

    void setFamily(const std::string& newFamily);
    void setName(const std::string& newName);
    void setConsumables(std::vector<std::string>& newConsumables);

    static std::vector<std::string> tokenize(char delimiter, const std::string& line);
    friend std::istream& operator>>(std::istream& istream, Vegetable& vegetable);
    friend std::ostream& operator<<(std::ostream& ostream, const Vegetable& vegetable);

    bool operator==(const Vegetable& vegetable) const;
    ~Vegetable();

};
