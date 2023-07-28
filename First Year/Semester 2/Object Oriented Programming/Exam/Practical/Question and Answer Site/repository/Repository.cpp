#include <fstream>
#include <algorithm>
#include <Exceptions.h>
#include "Repository.h"

Repository::Repository(std::string user, std::string question, std::string answer) {
    this->usersFile = std::move(user);
    this->questionsFile = std::move(question);
    this->answersFile = std::move(answer);
    this->readUserFromFile();
    this->readQuestionFromFile();
    this->readAnswerFromFile();
}

void Repository::readUserFromFile(){
    if (!this->usersFile.empty()) {
        User user;
        std::ifstream fin(this->usersFile);
        while (fin >> user) {
            if (std::find(this->users.begin(), this->users.end(), user) == this->users.end()) {
                this->users.push_back(user);
            }
        }
        fin.close();
    }
}

void Repository::readQuestionFromFile() {
    if (!this->questionsFile.empty()) {
        Question question;
        std::ifstream fin(this->questionsFile);
        while (fin >> question) {
            if (std::find(this->questions.begin(), this->questions.end(), question) == this->questions.end()) {
                this->questions.push_back(question);
            }
        }
        fin.close();
    }
}

void Repository::readAnswerFromFile() {
    if (!this->answersFile.empty()) {
        Answer answer;
        std::ifstream fin(this->answersFile);
        while (fin >> answer) {
            if (std::find(this->answers.begin(), this->answers.end(), answer) == this->answers.end()) {
                this->answers.push_back(answer);
            }
        }
        fin.close();
    }
}

void Repository::writeQuestionToFile() {
    if (!this->questions.empty()) {
        std::ofstream fout(this->questionsFile);
        for (Question& question: this->questions) {
            fout << question << "\n";
        }
        fout.close();
    }
}

void Repository::writeAnswerToFile() {
    if (!this->answers.empty()) {
        std::ofstream fout(this->answersFile);
        for (Answer& answer: this->answers) {
            fout << answer << "\n";
        }
        fout.close();
    }
}

void Repository::addQuestion(const Question &question) {
    if (std::find(this->questions.begin(), this->questions.end(), question) == this->questions.end()) {
        this->questions.push_back(question);
        this->writeQuestionToFile();
    } else {
        throw RepositoryException("Question already added!");
    }
}

void Repository::addAnswer(const Answer &answer) {
    if (std::find(this->answers.begin(), this->answers.end(), answer) == this->answers.end()) {
        this->answers.push_back(answer);
        this->writeAnswerToFile();
    } else {
        throw RepositoryException("Answer already added!");
    }
}

void Repository::updateAnswer(const Answer &answer) {
    std::vector<Answer>::iterator it;
    it = std::find_if(this->answers.begin(), this->answers.end(), [&answer](Answer& answerOther) {return answer.getId()==
                                                                                                         answerOther.getId(); });
    if (it != this->answers.end()) {
        this->answers[it - this->answers.begin()] = answer;
        this->writeAnswerToFile();
    } else {
        throw RepositoryException("Answer does not exist!");
    }
}

std::vector<User> Repository::getAllUsers() {
    return this->users;
}

std::vector<Question> Repository::getAllQuestions() {
    return this->questions;
}

std::vector<Answer> Repository::getAllAnswers() {
    return this->answers;
}
