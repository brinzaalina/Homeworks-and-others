//
// Created by selen on 19/06/2021.
//

#pragma once

#include <string>
#include <ctime>
#include <iostream>

class myException: public std::exception {
private:
    std::string message;
public:
    explicit myException(std::string& message): message(message) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class Channel {
public:
    Channel() = default;
    virtual void send(std::string& message) = 0;
    ~Channel() = default;
};

class Telephone: public Channel {
protected:
    std::string number;
public:
    explicit Telephone(std::string& number);
    void send(std::string& message) override;
};

class Fax: public Telephone {
public:
    explicit Fax(std::string& number);
    void send(std::string& message) override;
};

class SMS: public Telephone {
public:
    explicit SMS(std::string& number);
    void send(std::string& message) override;
};

class Failover: public Channel {
private:
    Channel* channel1;
    Channel* channel2;
public:
    Failover(Channel* channel1, Channel* channel2);
    void send(std::string& message) override;
    ~Failover();
};

class Contact {
    Channel* channel1;
    Channel* channel2;
    Channel* channel3;
public:
    explicit Contact(Channel* c1, Channel* c2, Channel* c3);
    void sendAlarm(std::string& message);
    ~Contact();
};