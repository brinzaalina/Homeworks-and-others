//
// Created by selen on 17/04/2021.
//

#ifndef A45_911_BRINZA_ALINA_ELENA_HTMLREPOSITORY_H
#define A45_911_BRINZA_ALINA_ELENA_HTMLREPOSITORY_H

#include "userrepository.h"

class HTMLRepo: public UserRepository {
public:
    HTMLRepo(const std::vector<Dog>& adoptionList, const std::string& userFilename);

    std::vector<Dog>& getAllUserRepo() override;

    unsigned int getNrElems() override;

    unsigned int getCap() override;

    void addUserRepo(const Dog &dog) override;

    void writeToFile() override;

    std::string& getFilename() override;

    ~HTMLRepo();
};

#endif //A45_911_BRINZA_ALINA_ELENA_HTMLREPOSITORY_H
