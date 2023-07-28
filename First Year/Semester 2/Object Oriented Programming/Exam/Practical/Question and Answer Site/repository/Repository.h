#pragma once

#include <vector>
#include <Domain.h>

class Repository {
private:
    std::vector<User> users;
    std::vector<Question> questions;
    std::vector<Answer> answers;
    std::string usersFile;
    std::string questionsFile;
    std::string answersFile;
public:
    explicit Repository(std::string user, std::string question, std::string answer);
    void readUserFromFile();
    void readQuestionFromFile();
    void writeQuestionToFile();
    void readAnswerFromFile();
    void writeAnswerToFile();

    void addQuestion(const Question &question);
    void addAnswer(const Answer& answer);
    void updateAnswer(const Answer &answerOther);

    std::vector<User> getAllUsers();
    std::vector<Question> getAllQuestions();
    std::vector<Answer> getAllAnswers();

    ~Repository() = default;
};
