#include <string>
#include <iostream>

class Handrail {
public:
    Handrail() = default;
    virtual double computePrice() = 0;
    virtual ~Handrail() = default;
};

class WoodHandrail: public Handrail {
public:
    WoodHandrail() = default;
    double computePrice() override {
        return 2;
    }
};

class MetalHandrail: public Handrail {
public:
    MetalHandrail() = default;
    double computePrice() override {
        return 2.5;
    }
};

class HandrailWithVerticalElements: public Handrail {
private:
    int noElements;
    Handrail* handrail;
public:
    HandrailWithVerticalElements(int number, Handrail* handrail1) {
        noElements = number;
        handrail = handrail1;
    }
    double computePrice() override {
        return handrail->computePrice() + 5 * noElements;
    }

    ~HandrailWithVerticalElements() override {
        delete handrail;
    }
};

class Stair {
private:
    int noSteps;
public:
    explicit Stair(int number): noSteps{number} {}
    virtual std::string getDescription() const = 0;
    virtual double getCoefficient() const = 0;
    double getPrice() const {
        return this->getCoefficient() * noSteps;
    }
    virtual ~Stair() = default;
};

class WoodStair: public Stair {
public:
    explicit WoodStair(int number): Stair(number) {}
    std::string getDescription() const override {
        return "wood stair";
    }
    double getCoefficient() const override {
        return 1.5;
    }
};

class MetalStair: public Stair {
public:
    explicit MetalStair(int number): Stair(number) {}
    std::string getDescription() const override {
        return "metal stair";
    }
    double getCoefficient() const override {
        return 2;
    }
};

class StairWithHandrail: public Stair {
private:
    double handrailLinearMeters;
    Stair* stair;
    Handrail* handrail;
public:
    explicit StairWithHandrail(int nrSteps, double meters, Stair* stair1, Handrail* handrail1): Stair(nrSteps) {
        handrailLinearMeters = meters;
        stair = stair1;
        handrail = handrail1;
    }
    double getPrice() {
        return stair->getPrice() + handrail->computePrice() * handrailLinearMeters;
    }

    double getCoefficient() const override {
        return 1;
    }
    std::string getDescription() const override {
        return stair->getDescription() + " with " + std::to_string(handrailLinearMeters) + " meters of handrail";
    }
    ~StairWithHandrail() override {
        delete stair;
        delete handrail;
    }
};

int main() {
    auto woodStair = new WoodStair(20);

    auto metalStair = new MetalStair(10);
    auto metalHandrail = new MetalHandrail{};
    auto metalStairHandrail = new StairWithHandrail(10, 5, metalStair, metalHandrail);

    auto woodStair1 = new WoodStair(10);
    auto woodHandrail = new WoodHandrail{};
    auto vertical = new HandrailWithVerticalElements(10, woodHandrail);
    auto woodStairHandrail = new StairWithHandrail(10, 5, woodStair1, vertical);

    //1
    std::cout << woodStair->getDescription() << " - price -> " << woodStair->getPrice() << "\n";

    //2
    std::cout << metalStairHandrail->getDescription() << " - price -> " << metalStairHandrail->getPrice() << "\n";

    //3
    std::cout << woodStairHandrail->getDescription() << " - price -> " << woodStairHandrail->getPrice() << "\n";

    delete woodStair;
    delete metalStairHandrail;
    delete woodHandrail;
    return 0;
}