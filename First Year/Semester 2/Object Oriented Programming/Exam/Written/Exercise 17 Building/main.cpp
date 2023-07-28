#include <string>
#include <iostream>
#include <vector>

class AmbientCondition {
public:
    AmbientCondition() = default;
    virtual std::string adjust() = 0;
    ~AmbientCondition() = default;
};

class Temperature: public AmbientCondition {
private:
    double value;
public:
    explicit Temperature(double value): value{value} {}
    std::string adjust() override {
        return "temperature - " + std::to_string(value) + " degrees" ;
    }
};

class Light: public AmbientCondition{
private:
    bool value;
public:
    explicit Light(bool value): value{value} {}
    std::string adjust() override {
        if (value)
            return "Light turned on";
        else
            return "Light turned off";
    }
};

class BuildingComponent {
public:
    BuildingComponent() = default;
    virtual void setAmbientCondition(AmbientCondition* a) = 0;
    virtual void addBuildingComponent(BuildingComponent* b) = 0;
    virtual ~BuildingComponent() = default;
};

class Room: public BuildingComponent {
private:
    int number;
public:
    explicit Room(int number): number{number} {}
    void setAmbientCondition(AmbientCondition* a) override {
        std::cout<< "Adjusting the condition for room " << std::to_string(number)<< ": " << a->adjust() << "\n";
    }
    void addBuildingComponent(BuildingComponent* b) override {}
    ~Room() = default;
};

class Floor: public BuildingComponent {
private:
    int number;
    std::string name;
    std::vector<BuildingComponent*> components;
public:
    explicit Floor(int number): number{number} {}
    Floor(std::string& name): name{name} {}
    void setAmbientCondition(AmbientCondition* a) override {
        if (name.empty()) {
            std::cout << "Adjusting the condition for the floor " << std::to_string(number) << "\n";
            for (auto comp: components) {
                std::cout << "\t";
                comp->setAmbientCondition(a);
            }
        } else {
            std::cout << "Adjusting the condition for the " << name << "\n";
            for (auto comp: components) {
                std::cout << "\t";
                comp->setAmbientCondition(a);
            }
        }
    }
    void addBuildingComponent(BuildingComponent* b) override {
        components.push_back(b);
    }
    ~Floor() {
        for(auto comp: components) {
            delete comp;
        }
    }
};

class Building: public BuildingComponent {
private:
    std::string name;
    std::vector<BuildingComponent*> components;
public:
    explicit Building(std::string& name): name{name} {}
    void setAmbientCondition(AmbientCondition* a) override {
        std::cout << "Adjusting the condition for the building " << name << "\n";
        for (auto comp: components) {
            std::cout << "\t";
            comp->setAmbientCondition(a);
        }
    }
    void addBuildingComponent(BuildingComponent* b) override {
        components.push_back(b);
    }
    ~Building() {
        for (auto comp: components) {
            delete comp;
        }
    }
};

int main() {
    auto floor0 = new Floor(0);
    auto room0 = new Room(0);
    floor0->addBuildingComponent(room0);

    auto floor1 = new Floor(1);
    auto room1 = new Room(1);
    auto room2 = new Room(2);
    floor1->addBuildingComponent(room1);
    floor1->addBuildingComponent(room2);

    auto temperature0 = new Temperature(23);
    floor0->setAmbientCondition(temperature0);
    floor1->setAmbientCondition(temperature0);

    auto floor2 = new Floor(2);
    auto room3 = new Room(3);
    floor2->addBuildingComponent(room3);

    auto floor3 = new Floor(3);
    auto room4 = new Room(4);
    floor3->addBuildingComponent(room4);

    std::string attic;
    attic.append("attic");
    auto floorAttic = new Floor(attic);
    floorAttic->addBuildingComponent(floor2);
    floorAttic->addBuildingComponent(floor3);

    auto temperature1 = new Temperature(18);
    floorAttic->setAmbientCondition(temperature1);

    std::string name;
    name.append("FSEGA");
    auto building = new Building(name);
    building->addBuildingComponent(floor0);
    building->addBuildingComponent(floor1);
    building->addBuildingComponent(floorAttic);

    auto lights = new Light(true);
    building->setAmbientCondition(lights);

    delete lights;
    delete temperature1;
    delete temperature0;

    return 0;
}