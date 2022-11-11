#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

std::vector<int> v1 = {1, 2, 3, 4, 5};
std::vector<int> v2 = {2, 4, 6, 8, 10};
int result = 0;
std::queue<int> partialProducts;
std::condition_variable productFlag;
std::mutex mutex;
bool producerDone = false;

void produce() {
    int product;
    std::unique_lock<std::mutex> lock(mutex);
    for (int index = 0; index < v1.size(); index++) {
        product = v1[index] * v2[index];
        std::cout << "Produced: " << product << std::endl;
        partialProducts.push(product);
        productFlag.notify_one();
    }
    producerDone = true;
    productFlag.notify_one();
}

void consume() {
    while (!producerDone) {
        std::unique_lock<std::mutex> lock(mutex);
        productFlag.wait(lock, [] { return producerDone; });
        result += partialProducts.front();
        partialProducts.pop();
        std::cout << "Partial sum: " << result << std::endl;
    }
    while (!partialProducts.empty()) {
        result += partialProducts.front();
        partialProducts.pop();
        std::cout << "Partial sum: " << result << std::endl;
    }
}

int main() {
    std::thread producer(produce);
    std::thread consumer(consume);

    producer.join();
    consumer.join();

    std::cout << "The result is " << result << std::endl;
    return 0;
}
