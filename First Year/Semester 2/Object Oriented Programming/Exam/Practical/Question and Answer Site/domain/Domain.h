#pragma once

#include <string>

class User {
private:
    std::string name;
public:
    User() = default;
    explicit User(std::string name);
    std::string getName() const;
    ~User() = default;

    friend std::istream& operator>>(std::istream& inputStream, User& user);
    friend std::ostream& operator<<(std::ostream& outputStream, const User& user);

    bool operator==(const User& user) const;
};


class Question {
private:
    int id;
    std::string description;
    std::string name;
public:
    explicit Question(int id = 0, std::string description = "", std::string name = "");
    int getId() const;
    std::string getDescription() const;
    std::string getName() const;
    ~Question() = default;

    friend std::istream& operator>>(std::istream& inputStream, Question& question);
    friend std::ostream& operator<<(std::ostream& outputStream, const Question& question);

    bool operator==(const Question& question) const;
};

class Answer{
private:
    int id;
    int questionId;
    std::string name;
    std::string answer;
    int numberVotes;
public:
    explicit Answer(int id = 0, int questionId = 0, std::string name = "", std::string answer = "", int numberVotes = 0);
    int getId() const;
    int getQuestionId() const;
    std::string getName() const;
    std::string getAnswer() const;
    int getNumberVotes() const;
    void setNumberVotes(int number);
    ~Answer() = default;

    friend std::istream& operator>>(std::istream& inputStream, Answer& answer);
    friend std::ostream& operator<<(std::ostream& outputStream, const Answer& answer);

    bool operator==(const Answer& answer) const;
};
