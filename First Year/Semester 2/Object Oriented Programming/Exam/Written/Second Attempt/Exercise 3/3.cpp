#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

class Encoder {
public:
    Encoder() = default;
    virtual std::string encode(std::string& msg) = 0;
    virtual ~Encoder() = default;
};

class AlienEncoder: public Encoder {
private:
    std::string header;
public:
    explicit AlienEncoder(std::string& header);
    std::string encode(std::string& msg) override;
};

AlienEncoder::AlienEncoder(std::string &header): header{header} {
}

std::string AlienEncoder::encode(std::string &msg) {
    return msg + this->header;
}

class MorseEncoder: public Encoder {
public:
    MorseEncoder() = default;
    std::string encode(std::string& msg) override;
};

std::string MorseEncoder::encode(std::string &msg) {
    for (char & i : msg) {
        i = '.';
    }
    return msg;
}

class Mixer: public Encoder {
private:
    Encoder* encoder1;
    Encoder* encoder2;
public:
    Mixer(Encoder* first, Encoder* second);
    std::string encode(std::string& msg) override;
    ~Mixer() override;
};

Mixer::Mixer(Encoder *first, Encoder *second) {
    this->encoder1 = first;
    this->encoder2 = second;
}

std::string Mixer::encode(std::string &msg) {
    std::string result;
    for (int i = 0; i < msg.size(); i++) {
        std::string letter = std::string(1, msg[i]);
        if(i%2 == 0) {
            result+=this->encoder1->encode(letter);
        } else {
            result+=this->encoder2->encode(letter);
        }
    }
    return result;
}

Mixer::~Mixer() {
    delete this->encoder1;
    delete this->encoder2;
}

class Communication {
private:
    Encoder* encoder;
    std::vector<std::string> messages;
public:
    explicit Communication(Encoder* encoder1);
    void addMessage(std::string& msg);
    std::string communicate();
    ~Communication();
};

Communication::Communication(Encoder *encoder1) {
    this->encoder = encoder1;
}

void Communication::addMessage(std::string& msg) {
    this->messages.push_back(msg);
}

std::string Communication::communicate() {
    std::string resultMessage;
    std::sort(this->messages.begin(), this->messages.end());
    for (auto msg: this->messages) {
        resultMessage.append(this->encoder->encode(msg));
        resultMessage.append(" ");
    }
    return resultMessage;
}

Communication::~Communication() {
    delete this->encoder;
}

int main() {
    auto morse1 = new MorseEncoder();
    auto morse2 = new MorseEncoder();
    std::string header = "ET";
    auto alien = new AlienEncoder(header);
    auto mixer = new Mixer(alien, morse2);
    auto communication1 = new Communication{morse1};
    auto communication2 = new Communication{mixer};

    std::string message1 = "I love oop!";
    std::string message2 = "I love C++";
    communication1->addMessage(message1);
    communication1->addMessage(message2);
    communication2->addMessage(message1);
    communication2->addMessage(message2);

    std::cout << communication1->communicate() << "\n";
    std::cout << communication2->communicate() << "\n";

    delete communication1;
    delete communication2;
    return 0;
}
