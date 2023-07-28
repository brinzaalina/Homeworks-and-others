#include <string>
#include <algorithm>
#include <vector>
#include <stdexcept>

template <typename TInfo, typename TElem>
class SortedDictionary {
private:
    std::vector<std::pair<TInfo, TElem>> elements;
public:
    SortedDictionary() = default;
    SortedDictionary<TInfo, TElem>& put(TInfo info, TElem elem);
    void print(std::ostream& ostream);
    int size();
    TElem eraseFirst();
};

template<typename TInfo, typename TElem>
SortedDictionary<TInfo, TElem>& SortedDictionary<TInfo, TElem>::put(TInfo info, TElem elem) {
    if (std::find_if(this->elements.begin(), this->elements.end(), [info] (const std::pair<TInfo, TElem>& element) {return element.first == info; }) !=
            this->elements.end()) {
        throw std::runtime_error("Element already exists!");
    }
    this->elements.push_back(std::make_pair(info, elem));
    std::sort(this->elements.begin(), this->elements.end(), [](const std::pair<TInfo, TElem>& a, const std::pair<TInfo, TElem>& b) { return a.first < b.first; });
    return *this;
}

template<typename TInfo, typename TElem>
void SortedDictionary<TInfo, TElem>::print(std::ostream &ostream) {
    for (auto elem: this->elements) {
        ostream << elem.first << " " << elem.second << "; ";
    }
}

template<typename TInfo, typename TElem>
int SortedDictionary<TInfo, TElem>::size() {
    return this->elements.size();
}

template<typename TInfo, typename TElem>
TElem SortedDictionary<TInfo, TElem>::eraseFirst() {
    std::pair<TInfo, TElem> firstElement = this->elements[0];
    this->elements.erase(this->elements.begin());
    return firstElement.second;
}

class Person {
private:
    std::string name;
    int age;
public:
    Person(const std::string& name, int age): name{name}, age{age} {}
    bool operator==(const Person& otherPerson) {
        return this->name == otherPerson.name && this->age == otherPerson.age;
    }
    friend std::ostream& operator<<(std::ostream& ostream, const Person& person) {
        std::string output;
        output.append(person.name);
        output.append(" is ");
        output.append(std::to_string(person.age));
        output.append(" years old.");
        ostream << output;
        return ostream;
    }
};