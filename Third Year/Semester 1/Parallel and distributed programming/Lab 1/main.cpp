#include <iostream>
#include <list>
#include <unordered_map>
#include <fstream>
#include <ctime>
#include <vector>
#include <random>
#include <mutex>
#include <thread>

#define CREATOR_THREAD_COUNT 5

typedef struct {
    int sourceAccountId;
    int destinationAccountId;
    int amount;
    int serialNumber;
} OPERATION;

typedef struct {
    int id;
    int balance;
    int initialBalance;
    std::list<OPERATION> log;
} ACCOUNT;

std::unordered_map<int, ACCOUNT> _accounts;
std::list<OPERATION> _operations;
int _nextSerialNumber = 0;

std::mutex *accountsMutexes;
std::mutex operationMutex;
std::mutex serialNumberMutex;

std::unordered_map<int, ACCOUNT> readAllAccounts(const std::string &filePath) {
    std::unordered_map<int, ACCOUNT> accounts;
    std::ifstream file(filePath);
    ACCOUNT account;
    while (file >> account.id >> account.balance) {
        account.initialBalance = account.balance;
        accounts[account.id] = account;
    }
    return accounts;
}

void printAllOperations() {
    operationMutex.lock();
    for (auto const &operation: _operations) {
        std::cout << "--> OPERATION serial number: " << operation.serialNumber << "-----" << std::endl;
        std::cout << "source account: " << operation.sourceAccountId << std::endl;
        std::cout << "destination account: " << operation.destinationAccountId << std::endl;
        std::cout << "amount: " << operation.amount << std::endl << std::endl;
    }
    operationMutex.unlock();
}

int generateRandomNumberInRange(int min, int max) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void createTransaction() {
    OPERATION operation;
    operation.amount = generateRandomNumberInRange(1, 100);
    int senderAccount = generateRandomNumberInRange(0, _accounts.size() - 1);
    int receiverAccount = generateRandomNumberInRange(0, _accounts.size() - 1);
    while (senderAccount == receiverAccount) {
        receiverAccount = generateRandomNumberInRange(0, _accounts.size() - 1);
    }
    operation.sourceAccountId = senderAccount;
    operation.destinationAccountId = receiverAccount;
    if (operation.sourceAccountId < operation.destinationAccountId){
        accountsMutexes[operation.sourceAccountId].lock();
        accountsMutexes[operation.destinationAccountId].lock();
        if (_accounts[operation.sourceAccountId].balance < operation.amount) {
            accountsMutexes[operation.destinationAccountId].unlock();
            accountsMutexes[operation.sourceAccountId].unlock();
            return;
        }
        serialNumberMutex.lock();
        operation.serialNumber = _nextSerialNumber++;
        serialNumberMutex.unlock();
        _accounts[operation.sourceAccountId].balance -= operation.amount;
        _accounts[operation.sourceAccountId].log.push_back(operation);
        _accounts[operation.destinationAccountId].balance += operation.amount;
        _accounts[operation.destinationAccountId].log.push_back(operation);
        accountsMutexes[operation.sourceAccountId].unlock();
        accountsMutexes[operation.destinationAccountId].unlock();
    } else {
        accountsMutexes[operation.destinationAccountId].lock();
        accountsMutexes[operation.sourceAccountId].lock();
        if (_accounts[operation.sourceAccountId].balance < operation.amount) {
            accountsMutexes[operation.sourceAccountId].unlock();
            accountsMutexes[operation.destinationAccountId].unlock();
            return;
        }
        serialNumberMutex.lock();
        operation.serialNumber = _nextSerialNumber++;
        serialNumberMutex.unlock();
        _accounts[operation.destinationAccountId].balance += operation.amount;
        _accounts[operation.destinationAccountId].log.push_back(operation);
        _accounts[operation.sourceAccountId].balance -= operation.amount;
        _accounts[operation.sourceAccountId].log.push_back(operation);
        accountsMutexes[operation.destinationAccountId].unlock();
        accountsMutexes[operation.sourceAccountId].unlock();
    }
    operationMutex.lock();
    _operations.push_back(operation);
    operationMutex.unlock();
}

bool checkIfOperationFromSourceAccountIsInDestinationAccountLog(OPERATION operation) {
    for (auto const &operationFromLog: _accounts[operation.destinationAccountId].log) {
        if (operationFromLog.serialNumber == operation.serialNumber) {
            return true;
        }
    }
    return false;
}

bool checkIfOperationFromDestinationAccountIsInSourceAccountLog(OPERATION operation) {
    for (auto const &operationFromLog: _accounts[operation.sourceAccountId].log) {
        if (operationFromLog.serialNumber == operation.serialNumber) {
            return true;
        }
    }
    return false;
}

void checkConsistency() {
    bool isConsistent = true;
    for (auto const &account: _accounts) {
        accountsMutexes[account.first].lock();
        auto initialBalance = account.second.initialBalance;
        for (auto const &operation: account.second.log) {
            if (operation.sourceAccountId == account.first) {
                initialBalance -= operation.amount;
                isConsistent = checkIfOperationFromSourceAccountIsInDestinationAccountLog(operation);
            } else {
                initialBalance += operation.amount;
                isConsistent = checkIfOperationFromDestinationAccountIsInSourceAccountLog(operation);
            }
        }
        if (initialBalance != account.second.balance) {
            isConsistent = false;
            break;
        }
        accountsMutexes[account.first].unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    if (isConsistent) {
        std::cout << "Consistency check passed" << std::endl;
    } else {
        std::cout << "Consistency check failed" << std::endl;
    }
}

int main() {
    std::srand(std::time(nullptr));
    _accounts = readAllAccounts(R"(D:\Desktop Folders\Facultate\Anul 3\Sem 1\Programare paralela si distribuita\A1\accounts.txt)");
    std::thread creatorThreads[CREATOR_THREAD_COUNT];
    accountsMutexes = new std::mutex[_accounts.size()];

    for (int i = 0; i < CREATOR_THREAD_COUNT; i++) {
        creatorThreads[i] = std::thread(createTransaction);
    }
    for (int i = 0; i < CREATOR_THREAD_COUNT; i++) {
        creatorThreads[i].join();
        if (i % 6 == 0) {
            checkConsistency();
        }
    }
    std::thread checkerThread(checkConsistency);
    checkerThread.join();
    std::thread printerThread(printAllOperations);
    printerThread.join();
    delete[] accountsMutexes;
    return 0;

}
