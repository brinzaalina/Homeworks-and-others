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

void test() {
    std::string number = "0745165688";
    auto telephone = new Telephone(number);
    auto fax = new Fax(number);
    auto sms = new SMS(number);
    auto failover1 = new Failover(fax, sms);
    auto failover2 = new Failover(telephone, failover1);

    auto contact = new Contact(telephone, failover1, failover2);
    std::string message = "hello!";
    contact->sendAlarm(message);
}

int main() {
    test();
    return 0;
}
