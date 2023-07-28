#include <iostream>
#include <vector>
#include <cassert>

class Object{
public:
    virtual void print() = 0;
    virtual ~Object() = default;
};


class Character : public Object{
private:
    char character;
public:
    explicit Character(char character): character(character) {}
    void print() override{
        std::cout << character << " ";
    }
    bool operator==(Character& c) const{
        return c.character == character;
    }
    bool operator==(char chr) const{
        return chr == character;
    }
    ~Character() override = default;
};

class Double: public Object{
private:
    double number;
public:
    explicit Double(double number): number(number) {}
    void print() override{
        std::cout << number << " ";
    }
    ~Double() override = default;
};

class MyVector{
private:
    std::vector<Object*> objects;
public:
    MyVector operator+=(Object* object){
        objects.push_back(object);
        return *this;
    }
    int size(){
        return objects.size();
    }
    Object* operator[](int position){
        return objects[position];
    }
    ~MyVector() {
//        for (auto a: objects)
//            delete a;
        objects.clear();
    }
};


class BackwardsIterator{
private:
    int position;
    MyVector& vect;
public:
    explicit BackwardsIterator(MyVector& vect): vect(vect) {
        position = vect.size()-1;
    }
    Object* element(){
        return vect[position];
    }
    void previous(){
        position--;
    }
    bool isValid() const{
        return position >= 0;
    }
};

int main() {
    MyVector vector{};
    Character* c = new Character{'c'};
    assert(*c == 'c');
    vector += c;
    vector += new Double{2.5};
    vector += new Double{1.2};
    vector += new Character{'o'};
    assert(vector.size() == 4);
    BackwardsIterator i{vector};
    while(i.isValid()){
        Object* o = i.element();
        o->print();
        i.previous();
    }
    return 0;
}
