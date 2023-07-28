//
// Created by selen on 19/06/2021.
//

#include "classes.h"

Telephone::Telephone(std::string& number) {
    this->number = number;
}

void Telephone::send(std::string &message) {
    srand(time(nullptr));
    int r = rand() % 10;
    if (r % 2 == 0){
        std::string er;
        er.append("The line is busy!");
        throw myException(er);
    } else {
        std::string string;
        string.append("dialing ");
        string.append(this->number);
        std::cout << string << " ...\n";
    }
}

Fax::Fax(std::string& number): Telephone(number) {
}

void Fax::send(std::string &message) {
    srand(time(NULL));
    int r = rand() % 10;
    if (r % 2 == 1){
        std::string er;
        er.append("The line is busy!");
        throw myException(er);
    } else {
        std::string fax;
        fax.append("sending fax to ");
        fax.append(this->number);
        fax.append(": ");
        fax.append(message);
        std::cout << fax << " ...\n";
    }
}

SMS::SMS(std::string& number) : Telephone(number) {
}

void SMS::send(std::string &message) {
    srand(time(NULL));
    int r = rand() % 10;
    if (r % 2 == 0){
        std::string er;
        er.append("The line is busy!");
        throw myException(er);
    } else {
        std::string sms;
        sms.append("sending sms to ");
        sms.append(this->number);
        sms.append(": ");
        sms.append(message);
        std::cout << sms << " ...\n";
    }
}

Failover::Failover(Channel *channel1, Channel *channel2) {
    this->channel1 = channel1;
    this->channel2 = channel2;
}

void Failover::send(std::string &message) {
    try {
        channel1->send(message);
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
        try {
            channel2->send(message);
        } catch (std::exception& ex) {
            std::cout << ex.what() << "\n";
        }
    }

}

Failover::~Failover() {
    delete this->channel1;
    delete this->channel2;
}

Contact::Contact(Channel *c1, Channel *c2, Channel *c3) {
    this->channel1 = c1;
    this->channel2 = c2;
    this->channel3 = c3;
}

void Contact::sendAlarm(std::string &message) {
    bool repeat = true;
    while (repeat) {
        try {
            channel1->send(message);
            repeat = false;
        } catch (std::exception &e1) {
            std::cout << e1.what() << "\n";
            try {
                channel2->send(message);
                repeat = false;
            } catch (std::exception &e2) {
                std::cout << e2.what() << "\n";
                try {
                    channel3->send(message);
                    repeat = false;
                } catch (std::exception &e3) {
                    std::cout << e3.what() << "\n";
                }
            }
        }
    }
}

Contact::~Contact() {
    delete this->channel1;
    delete this->channel2;
    delete this->channel3;
}
