//
// Created by selen on 21/05/2021.
//

#pragma once

#include <string>
#include <vector>
#include <sstream>

class Product {
private:
    std::string category;
    std::string name;
    int quantity;
public:
    Product();
    Product(const std::string& categoryOfProduct, const std::string& nameOfProduct, int quantityOfProduct);
    Product(const Product& product);

    std::string getCategory() const;
    std::string getName() const;
    int getQuantity() const;

    void setCategory(const std::string& newCategory);
    void setName(const std::string &newName);
    void setQuantity(int newQuantity);

    static std::vector<std::string> tokenize(char delimiter, const std::string& line);
    friend std::istream& operator>>(std::istream& istream, Product& product);
    friend std::ostream& operator<<(std::ostream& ostream, const Product& product);

    bool operator==(const Product& product) const;
    ~Product();

};
