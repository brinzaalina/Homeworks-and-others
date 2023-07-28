#pragma once

#include <string>
#include <vector>

class Star {
private:
    std::string name;
    std::string constellation;
    int RA;
    int Dec;
    int diameter;
public:
    Star(std::string name = "", std::string constellation = "", int RA = 0, int Dec = 0, int diameter = 0);
    Star(const Star& star);
    bool operator==(const Star& otherStar) const;
    ~Star() = default;

    std::string getName() const;
    std::string getConstellation() const;
    int getRA() const;
    int getDec() const;
    int getDiameter() const;


    static std::vector<std::string> tokenize(const std::string& str, char delimiter);
    friend std::istream& operator>>(std::istream& istream, Star& star);
    friend std::ostream& operator<<(std::ostream& ostream, const Star& star);

};

class Astronomer {
private:
    std::string name;
    std::string constellation;
public:
    Astronomer(std::string name = "", std::string constellation = "");
    Astronomer(const Astronomer& astronomer);
    bool operator==(const Astronomer& astronomer) const;
    ~Astronomer() = default;

    std::string getName() const;
    std::string getConstellation() const;

    static std::vector<std::string> tokenize(const std::string& str, char delimiter);
    friend std::istream& operator>>(std::istream& istream, Astronomer& astronomer);
    friend std::ostream& operator<<(std::ostream& ostream, const Astronomer& astronomer);
};