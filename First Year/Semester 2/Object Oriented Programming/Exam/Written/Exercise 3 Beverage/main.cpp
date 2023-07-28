#include "classes.h"

int main() {
    std::unique_ptr<BeverageMachine> machine(new BeverageMachine());
    machine->prepare("Tea", 0);
    machine->prepare("Coffee", 1);
    machine->prepare("Coffee", 2);
    return 0;
}
