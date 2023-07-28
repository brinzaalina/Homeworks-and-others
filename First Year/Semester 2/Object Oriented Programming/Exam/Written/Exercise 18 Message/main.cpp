#include <string>
#include <iostream>
#include <vector>

class Message {
private:
    std::string text;
public:
    Message() = default;
    explicit Message(std::string& text): text{text} {}
    virtual std::string getMessage() {
        return this->text;
    }
    ~Message() = default;
};

class ShortMessage: public Message {
public:
    explicit ShortMessage(std::string& text): Message(text){
        if (text.size() > 70)
            throw std::exception();
    }
};

class NormalMessage: public Message {
public:
    explicit NormalMessage(std::string& text): Message(text) {}
};

class MessageWithAttachment: public Message {
private:
    std::string attachmentLocation;
    Message* message;
public:
    MessageWithAttachment(Message* message1, std::string& attachment): attachmentLocation{attachment} {
        this->message = message1;
    }
    std::string getMessage() override {
        return this->message->getMessage() + " " + this->attachmentLocation;
    }
};

class Contact {
protected:
    std::string name;
public:
    explicit Contact(std::string& name): name{name} {}
    virtual void addContact(Contact* c) = 0;
    virtual void sendMessage(Message* message) = 0;
    virtual ~Contact() = default;
};

class Person: public Contact {
public:
    explicit Person(std::string& name): Contact(name) {}
    void addContact(Contact* c) override {}
    void sendMessage(Message* message) override {
        std::string result;
        result.append("Sending message: ");
        result.append(message->getMessage());
        result.append(" to ");
        result.append(this->name);
        std::cout << result << "\n";
    }
    ~Person() = default;
};

class Group: public Contact {
private:
    std::vector<Contact*> contacts;
public:
    explicit Group(std::string& name): Contact(name) {}
    void addContact(Contact* c) override {
        this->contacts.push_back(c);
    }
    void sendMessage(Message* message) override {
        std::cout << "Sending message to the group " << this->name << "\n";
        for (auto contact: this->contacts) {
            contact->sendMessage(message);
        }
    }
    ~Group() override {
        for (auto contact: contacts)
            delete contact;
    }
};

int main() {
    std::string name1;
    name1.append("roommates");
    auto group1 = new Group(name1);
    std::string name2;
    name2.append("John");
    auto person1 = new Person(name2);
    std::string name3;
    name3.append("Alice");
    auto person2 = new Person(name3);
    group1->addContact(person1);
    group1->addContact(person2);

    std::string name4;
    name4.append("university friends");
    auto group2 = new Group(name4);
    std::string name5;
    name5.append("Lilian");
    auto person3 = new Person(name5);
    std::string name6;
    name6.append("Michael");
    auto person4 = new Person(name6);
    group2->addContact(group1);
    group2->addContact(person3);
    group2->addContact(person4);

    std::string name7;
    name7.append("parents");
    auto group3 = new Group(name7);
    std::string name8;
    name8.append("mother");
    auto person5 = new Person(name8);
    std::string name9;
    name9.append("father");
    auto person6 = new Person(name9);
    group3->addContact(person5);
    group3->addContact(person6);

    std::string name10;
    name10.append("Charles");
    auto person7 = new Person(name10);

    std::string shortMess;
    shortMess.append("I arrived safely");
    auto shortMessage = new ShortMessage(shortMess);
    group3->sendMessage(shortMessage);

    std::string normalMess;
    normalMess.append("Hello! I invite you to my birthday party, which is on 10/05 next year. I know that this is quite early, but I wanna prepare a surprise for you and I need a lot of time for it, so please mark that date and come with me for the best day of your lives.");
    auto normalMessage = new NormalMessage(normalMess);
    std::string location;
    location.append("somewhere over the rainbow");
    auto attachment = new MessageWithAttachment(normalMessage, location);

    person7->sendMessage(attachment);
    group2->sendMessage(attachment);

    delete shortMessage;
    delete normalMessage;
    delete attachment;
    return 0;
}