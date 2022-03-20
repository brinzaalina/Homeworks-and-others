//
// Created by selen on 17/04/2021.
//

#ifndef A45_911_BRINZA_ALINA_ELENA_CSVREPOSITORY_H
#define A45_911_BRINZA_ALINA_ELENA_CSVREPOSITORY_H

#include "userrepository.h"

class CSVRepo: public UserRepository {
public:

    CSVRepo(const std::vector<Dog>& adoptionList, const std::string& userFilename);

    std::vector<Dog>& getAllUserRepo() override;

    int findByName(const std::string& name) override;

    unsigned int getNrElems() override;

    unsigned int getCap() override;

    void addUserRepo(const Dog &dog) override;

    void deleteUserRepo(const Dog &dog) override;

    void writeToFile() override;

    std::string& getFilename() override;

    ~CSVRepo();
};

#endif //A45_911_BRINZA_ALINA_ELENA_CSVREPOSITORY_H
