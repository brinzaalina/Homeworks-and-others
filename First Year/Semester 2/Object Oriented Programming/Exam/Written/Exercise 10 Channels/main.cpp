#include "classes.h"
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