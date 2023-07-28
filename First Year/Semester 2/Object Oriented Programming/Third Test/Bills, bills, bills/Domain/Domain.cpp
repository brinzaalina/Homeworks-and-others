//
// Created by selen on 19/05/2021.
//

#include "Domain.h"

Bill::Bill(): companyName{""}, code{""}, sum{0}, isPaid{false} {
}

Bill::Bill(const std::string& companyName, const std::string& code, float sum, bool isPaid){
    this->companyName = companyName;
    this->code = code;
    this->sum = sum;
    this->isPaid = isPaid;
}

Bill::Bill(const Bill& bill){
    this->companyName = bill.companyName;
    this->code = bill.code;
    this->sum = bill.sum;
    this->isPaid = bill.isPaid;
}

std::string Bill::getCompanyName() const {
    return this->companyName;
}

std::string Bill::getCode() const {
    return this->code;
}

float Bill::getSum() const {
    return this->sum;
}

bool Bill::getIsPaid() const {
    return this->isPaid;
}

void Bill::setCompanyName(std::string& newCompanyName){
    this->companyName = newCompanyName;
}

void Bill::setCode(std::string& newCode) {
    this->code = newCode;
}
void Bill::setSum(float newSum) {
    this->sum = newSum;
}

void Bill::setIsPaid(bool newIsPaid) {
    this->isPaid = newIsPaid;
}

bool Bill::operator==(const Bill& otherBill) const{
    return (this->code == otherBill.code);
}

std::vector<std::string> Bill::tokenize(const std::string& str, char delimiter){
    std::vector <std::string> result;
    std::stringstream ss(str);
    std::string token;
    while(std::getline(ss, token, delimiter))
    {
        result.push_back(token);
    }
    return result;
}

std::istream& operator>>(std::istream& istream, Bill& bill){
    std::string line;
    std::getline(istream, line);
    std::vector<std::string> tokens;
    if (line.empty())
    {
        return istream;
    }

    tokens = Bill::tokenize(line, ';');
    bill.companyName = tokens[0];
    bill.code = tokens[1];
    bill.sum = std::stof(tokens[2]);
    if (tokens[3] == "true")
        bill.isPaid = true;
    else
        bill.isPaid = false;
    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Bill& bill){
    if (bill.isPaid)
        ostream << bill.getCompanyName() << ";" << bill.getCode() << ";" << std::to_string(bill.getSum()) << ";" << "true";
    else
        ostream << bill.getCompanyName() << ";" << bill.getCode() << ";" << std::to_string(bill.getSum()) << ";" << "false";
    return ostream;
}