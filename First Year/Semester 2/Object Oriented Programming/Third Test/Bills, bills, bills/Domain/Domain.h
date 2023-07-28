//
// Created by selen on 19/05/2021.
//

#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

class Bill{
private:
    std::string companyName;
    std::string code;
    float sum;
    bool isPaid;

public:
    Bill();
    Bill(const std::string& companyName, const std::string& code, float sum, bool isPaid);
    Bill(const Bill& bill);
    bool operator==(const Bill& otherBill) const;

    std::string getCompanyName() const;
    std::string getCode() const;
    float getSum() const;
    bool getIsPaid() const;

    void setCompanyName(std::string& newCompanyName);
    void setCode(std::string& newCode);
    void setSum(float newSum);
    void setIsPaid(bool newIsPaid);

    static std::vector<std::string> tokenize(const std::string& str, char delimiter);

    friend std::istream& operator>>(std::istream& istream, Bill& entity);
    friend std::ostream& operator<<(std::ostream& ostream, const Bill& entity);

    ~Bill() = default;
};

