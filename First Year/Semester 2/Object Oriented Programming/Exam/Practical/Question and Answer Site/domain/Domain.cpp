#include <sstream>
#include <vector>
#include "Domain.h"

std::vector<std::string> tokenize(const std::string &str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while (getline(ss, token, delimiter))
        result.push_back(token);

    return result;
}

User::User(std::string name) {
    this->name = std::move(name);
}

std::string User::getName() const {
    return this->name;
}

std::istream &operator>>(std::istream &istream, User &user) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> lineParts;
    if (line.empty())
    {
        return istream;
    }
    lineParts = tokenize(line, ',');
    user.name = lineParts[0];
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const User &user) {
    std::string result;
    result.append(user.getName());
    ostream << result;
    return ostream;
}

bool User::operator==(const User &user) const {
    return this->name == user.name;
}

Question::Question(int id, std::string description, std::string name) {
    this->id = id;
    this->description = std::move(description);
    this->name = std::move(name);
}

int Question::getId() const {
    return this->id;
}

std::string Question::getDescription() const {
    return this->description;
}

std::string Question::getName() const {
    return this->name;
}

bool Question::operator==(const Question &question) const {
    return this->id == question.id;
}

std::istream &operator>>(std::istream &istream, Question &question) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> lineParts;
    if (line.empty())
    {
        return istream;
    }
    lineParts = tokenize(line, ',');
    question.id = std::stoi(lineParts[0]);
    question.description = lineParts[1];
    question.name = lineParts[2];
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Question &question) {
    std::string result;
    result.append(std::to_string(question.getId()));
    result.append(",");
    result.append(question.getDescription());
    result.append(",");
    result.append(question.getName());
    ostream << result;
    return ostream;
}

Answer::Answer(int id, int questionId, std::string name, std::string answer, int numberVotes) {
    this->id = id;
    this->questionId = questionId;
    this->name = std::move(name);
    this->answer = std::move(answer);
    this->numberVotes = numberVotes;
}

int Answer::getId() const {
    return this->id;
}

int Answer::getQuestionId() const {
    return this->questionId;
}

std::string Answer::getName() const {
    return this->name;
}

std::string Answer::getAnswer() const {
    return this->answer;
}

int Answer::getNumberVotes() const {
    return this->numberVotes;
}

bool Answer::operator==(const Answer &answer) const {
    return this->id == answer.id;
}

std::istream &operator>>(std::istream &istream, Answer &answer) {
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> lineParts;
    if (line.empty())
    {
        return istream;
    }
    lineParts = tokenize(line, ',');
    answer.id = std::stoi(lineParts[0]);
    answer.questionId = std::stoi(lineParts[1]);
    answer.name = lineParts[2];
    answer.answer = lineParts[3];
    answer.numberVotes = std::stoi(lineParts[4]);
    return istream;
}

std::ostream &operator<<(std::ostream &ostream, const Answer &answer) {
    std::string result;
    result.append(std::to_string(answer.getId()));
    result.append(",");
    result.append(std::to_string(answer.getQuestionId()));
    result.append(",");
    result.append(answer.getName());
    result.append(",");
    result.append(answer.getAnswer());
    result.append(",");
    result.append(std::to_string(answer.getNumberVotes()));
    ostream << result;
    return ostream;
}

void Answer::setNumberVotes(int number) {
    this->numberVotes = number;
}
