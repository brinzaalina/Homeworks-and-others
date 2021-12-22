
#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    this->relation = r;
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
}
//Theta(1)

void SortedBag::add(TComp e) {
	if (this->length == 0) {
        Node* newNode = new Node();
        newNode->info.first = e;
        newNode->info.second = 1;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        this->head = newNode;
        this->tail = newNode;
        this->length++;
    }else {
        Node *currentNode = this->head;
        bool found = false;
        while(currentNode != nullptr && !found && this->relation(currentNode->info.first, e)) {
            if (currentNode->info.first == e) {
                currentNode->info.second++;
                this->length++;
                found = true;
            } else
                currentNode = currentNode->next;
        }
        if (!found) {
            if(currentNode == this->head && currentNode != nullptr) {
                Node *newNode = new Node();
                newNode->info.first = e;
                newNode->info.second = 1;
                newNode->prev = nullptr;
                newNode->next = currentNode;
                currentNode->prev = newNode;
                this->head = newNode;
                this->length++;
            } else if (currentNode == nullptr) {
                Node *newNode = new Node();
                newNode->info.first = e;
                newNode->info.second = 1;
                newNode->next = currentNode;
                newNode->prev = this->tail;
                this->tail->next = newNode;
                this->tail = newNode;
                this->length++;
            } else {
                Node *newNode = new Node();
                newNode->info.first = e;
                newNode->info.second = 1;
                newNode->prev = currentNode->prev;
                newNode->next = currentNode;
                currentNode->prev->next = newNode;
                currentNode->prev = newNode;
                this->length++;
            }
        }
    }
}
//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)


bool SortedBag::remove(TComp e) {
    Node *currentNode = this->head;
    bool found = false;
    if (this->length != 0) {
        while (currentNode != nullptr && !found && this->relation(currentNode->info.first, e)) {
            if (currentNode->info.first == e) {
                found = true;
            } else {
                currentNode = currentNode->next;
            }
        }
    }
    if (found) {
        currentNode->info.second--;
        this->length--;
        if (currentNode->info.second == 0) {
            if (currentNode == this->head) {
                if (currentNode->next != nullptr) {
                    currentNode->next->prev = nullptr;
                    this->head = currentNode->next;
                    currentNode->next = nullptr;
                    delete currentNode;
                } else {
                    currentNode = nullptr;
                }
            }else if (currentNode == this->tail) {
                if (currentNode->prev != nullptr) {
                    currentNode->prev->next = nullptr;
                    this->tail = currentNode->prev;
                    currentNode->prev = nullptr;
                    delete currentNode;
                } else {
                    currentNode = nullptr;
                }
            } else {
                currentNode->next->prev = currentNode->prev;
                currentNode->prev->next = currentNode->next;
                currentNode->prev = nullptr;
                currentNode->next = nullptr;
                delete currentNode;
            }
        }
    }
    return found;
}
//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)


bool SortedBag::search(TComp elem) const {
    Node *currentNode = this->head;
    bool found = false;
    while (currentNode != nullptr && !found && this->relation(currentNode->info.first, elem)) {
        if (currentNode->info.first == elem) {
            found = true;
        } else {
            currentNode = currentNode->next;
        }
    }
    return found;
}
//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)


int SortedBag::nrOccurrences(TComp elem) const {
    Node *currentNode = this->head;
    while (currentNode != nullptr && this->relation(currentNode->info.first, elem)) {
        if (currentNode->info.first == elem) {
            return currentNode->info.second;
        } else {
            currentNode = currentNode->next;
        }
    }
    return 0;
}
//BC: Theta(1), WC: Theta(nrNodes), Total: O(nrNodes)


int SortedBag::size() const {
    return this->length;
}
//Theta(1)

bool SortedBag::isEmpty() const {
	if(this->head != nullptr)
	    return false;
    return true;
}
//Theta(1)

Node * SortedBag::getNode(TComp elem) const {
    Node *currentNode = this->head;
    while (currentNode != nullptr && this->relation(currentNode->info.first, elem)) {
        if (currentNode->info.first == elem) {
            return currentNode;
        } else {
            currentNode = currentNode->next;
        }
    }
    return nullptr;
}
//BC:Theta(1), WC:Theta(nrNodes), Total: O(nrNodes)


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}
//Theta(1)

void SortedBag::intersection(const SortedBag& b) {
    Node *currentNode = this->head;
    while (currentNode != nullptr) {
        Node *otherNode = b.getNode(currentNode->info.first);
        if (otherNode != nullptr) {
            if (otherNode->info.second < currentNode->info.second) {
            int occurrencesToDelete = abs(currentNode->info.second - otherNode->info.second);
            currentNode->info.second = currentNode->info.second - occurrencesToDelete;
            this->length = this->length - occurrencesToDelete;
            } else {
                currentNode = currentNode->next;
            }
        } else {
            this->length = this->length - currentNode->info.second;
            currentNode->info.second = 0;
            if (currentNode == this->head) {
                if (currentNode->next != nullptr) {
                    currentNode->next->prev = nullptr;
                    this->head = currentNode->next;
                    currentNode->next = nullptr;
                    currentNode = this->head;
                } else {
                    currentNode = nullptr;
                }
            } else if (currentNode == this->tail) {
                if (currentNode->prev != nullptr) {
                    currentNode->prev->next = nullptr;
                    this->tail = currentNode->prev;
                    currentNode->prev = nullptr;
                    currentNode = nullptr;
                } else {
                    currentNode = nullptr;
                }
            } else {
                Node* nextNode = currentNode->next;
                currentNode->next->prev = currentNode->prev;
                currentNode->prev->next = currentNode->next;
                currentNode->prev = nullptr;
                currentNode->next = nullptr;
                delete currentNode;
                currentNode = nextNode;
            }
        }
    }
}
//BC:Theta(nrNodesOfb*(nrNodesOfb + 1)), WC: Theta(nrNodes * nrNodesOfb)


SortedBag::~SortedBag() {
	Node* prevNode = nullptr;
	Node* currentNode = this->head;
	while (currentNode != nullptr) {
	    prevNode = currentNode;
	    currentNode = currentNode->next;
        delete prevNode;
	}
}
//Theta(nrNodes)