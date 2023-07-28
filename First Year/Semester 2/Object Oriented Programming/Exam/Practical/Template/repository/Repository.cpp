#include "Repository.h"

void Repository::readFromFile() {
//    if (!this->file.empty()) {
//        Object object{};
//        std::ifstream fin(this->file);
//        while (fin >> object) {
//            if (std::find(this->objects.begin(), this->objects.end(), object) == this->objects.end()) {
//                this->objects.push_back(object);
//            }
//        }
//        fin.close();
//    }

}

void Repository::writeToFile() {
//    if (!this->objects.empty()) {
//        std::ofstream fout(this->file);
//        for (Object& object: this->objects) {
//            fout << object << "\n";
//        }
//        fout.close();
//    }
}

void Repository::addObject(const Object &object) {
//    if (std::find(this->objects.begin(), this->objects.end(), object) == this->objects.end()) {
//        this->objects.push_back(object);
//        this->writeToFile();
//    } else {
//        throw RepositoryException("Object already added!");
//    }
}

void Repository::removeObject(const Object &object) {
//    std::vector<Object>::iterator found;
//    found = std::find(this->objects.begin(), this->objects.end(), object);
//    if (found != this->objects.end()) {
//        this->objects.erase(found);
//        this->writeToFile();
//    } else {
//        throw RepositoryException("Object does not exist!");
//    }
}

void Repository::updateObject(const Object &object) {
//    std::vector<Object>::iterator it;
//    it = std::find_if(this->objects.begin(), this->objects.end(), [&object](Object& object1) {return object.getElement() == object1.getElement(); });
//    if (it != this->objects.end()) {
//        this->objects[it - this->objects.begin()] = object;
//        this->writeToFile();
//    } else {
//        throw RepositoryException("Object does not exist!");
//    }
}
