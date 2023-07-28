#include "Service.h"

std::vector<User> Service::getAllUsers() {
    return this->repository.getAllUsers();
}

void Service::addQuestion(const std::string &text, const std::string &name) {
    int id = rand() % 1000;
    std::vector<Question> questions = this->repository.getAllQuestions();
    while(std::find(questions.begin(), questions.end(), Question{id, "", ""}) != questions.end())
        id = rand() % 1000;
    Question question{id, text, name};
    this->repository.addQuestion(question);
    this->notify();
}

std::vector<Question> Service::getAllQuestions() {
    std::vector<Question> questions = this->repository.getAllQuestions();
    std::vector<Answer> answers = this->repository.getAllAnswers();
    int howManyAnswers[1000] = {0};
    for (auto answer: answers)
        howManyAnswers[answer.getQuestionId()]++;
    for (int index1 = 0; index1 < questions.size() - 1; index1++) {
        for (int index2 = index1 + 1; index2 < questions.size(); index2++) {
            if (howManyAnswers[questions[index1].getId()] < howManyAnswers[questions[index2].getId()])
                std::swap(questions[index1], questions[index2]);
        }
    }
    return questions;
}


void Service::addAnswer(int questionId, const std::string &name, const std::string &answer, int votes) {
    int id = rand() % 1000;
    std::vector<Answer> answers = this->repository.getAllAnswers();
    while (std::find(answers.begin(), answers.end(), Answer{id, questionId, name, answer, votes}) != answers.end()) {
        id = rand() % 1000;
    }
    Answer answerToAdd{id, questionId, name, answer, votes};
    this->repository.addAnswer(answerToAdd);
    this->notify();
}


void Service::updateAnswer(const Answer &newAnswer) {
    this->repository.updateAnswer(newAnswer);
    this->notify();
}

std::vector<std::string> Service::getAllAnswers(std::string filter) {
    std::vector<Question> questions = this->repository.getAllQuestions();
    std::vector<Answer> answers = this->repository.getAllAnswers();
    int maxMatchingLetters = -1;
    int currentMatchingLetters;
    int questionId{};
    std::string maxMatchingLettersQuestion;
    for (auto question: questions) {
        currentMatchingLetters = 0;
        std::string currentQuestion = question.getDescription();
        for (int index = 0; index < filter.size(); index++) {
            if (currentQuestion[index] == filter[index])
                currentMatchingLetters++;
        }
        if (currentMatchingLetters > maxMatchingLetters) {
            questionId = question.getId();
            maxMatchingLettersQuestion = currentQuestion;
            maxMatchingLetters = currentMatchingLetters;
        }
    }
    int first = -1, second = -1, third = -1;
    std::string firstAnswer, secondAnswer, thirdAnswer;
    for (auto answer: answers) {
        if (answer.getQuestionId() == questionId) {
            if (answer.getNumberVotes() > first) {
                third = second;
                second = first;
                first = answer.getNumberVotes();
                thirdAnswer = secondAnswer;
                secondAnswer = firstAnswer;
                firstAnswer = answer.getAnswer();
            } else if (answer.getNumberVotes() > second) {
                third = second;
                second = answer.getNumberVotes();
                thirdAnswer = secondAnswer;
                secondAnswer = answer.getAnswer();
            } else if (answer.getNumberVotes() > third) {
                third = answer.getNumberVotes();
                thirdAnswer = answer.getAnswer();
            }
        }
    }
    std::vector<std::string> list;
    list.push_back(maxMatchingLettersQuestion);
    if (first != -1)
        list.push_back(firstAnswer);
    if (second != -1)
        list.push_back(secondAnswer);
    if (third != -1)
        list.push_back(thirdAnswer);
    return list;
}

std::vector<Answer> Service::getAnswers(int questionId) {
    std::vector<Answer> answers = this->repository.getAllAnswers();
    std::vector<Answer> allAnswers;
    for (auto answer: answers)
        if (answer.getQuestionId() == questionId)
            allAnswers.push_back(answer);
    return allAnswers;
}



