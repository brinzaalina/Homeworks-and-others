#pragma once

#include <Repository.h>
#include "../observer/Observer.h"

class Service: public Subject {
private:
    Repository& repository;
public:
    explicit Service(Repository& repo): repository{ repo } {};
    std::vector<User> getAllUsers();
    std::vector<Question> getAllQuestions();
    std::vector<std::string> getAllAnswers(std::string filter);
    std::vector<Answer> getAnswers(int questionId);
    void addQuestion(const std::string &text, const std::string &name);
    void addAnswer(int questionId, const std::string& name, const std::string& answer, int votes);
    void updateAnswer(const Answer &newAnswer);
};