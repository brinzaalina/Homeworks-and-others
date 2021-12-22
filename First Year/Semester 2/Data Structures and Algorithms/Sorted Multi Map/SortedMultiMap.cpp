#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <vector>
#include <exception>
using namespace std;

SortedMultiMap::SortedMultiMap(Relation r) {
    this->root = nullptr;
    this->rel = r;
    this->nrElements = 0;
}
//Theta(1)

void SortedMultiMap::add(TKey c, TValue v) {
	if (this->root == nullptr) {
	    //add the root
	    auto * newNode = new BSTNode();
	    newNode->info.first = c;
	    newNode->info.second = v;
        this->root = newNode;
        this->nrElements++;
	} else {
	    BSTNode* currentNode = this->root;
	    BSTNode* previousNode = nullptr;
	    //find the parent of the new node
	    while (currentNode != nullptr) {
	        if (this->rel(c, currentNode->info.first)) {
	            //left case
	            previousNode = currentNode;
	            currentNode = currentNode->left;
	        } else {
	            //right case
	            previousNode = currentNode;
	            currentNode = currentNode->right;
	        }
	    }
	    //add the new node and connect it to its parent
	    auto * newNode = new BSTNode();
	    newNode->info.first = c;
	    newNode->info.second = v;
	    newNode->parent = previousNode;
        this->nrElements++;
        if (this->rel(c, previousNode->info.first)) {
            //node will be the left child
            previousNode->left = newNode;
        } else {
            //node will be the right child
            previousNode->right = newNode;
        }
	}
}
//BC: Theta(1), WC: Theta(height) -> Total complexity: O(height)

vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> matching;
	BSTNode* currentNode = this->root;
	while (currentNode != nullptr) {
	    if (this->rel(c, currentNode->info.first)) {
	        // the elements are on the left tree if they exist
	        if (c == currentNode->info.first) {
	            matching.push_back(currentNode->info.second);
	        }
	        currentNode = currentNode->left;
	    } else {
	        // the elements are on the right tree if they exist
	        currentNode = currentNode->right;
	    }
	}
	return matching;
}
//BC: Theta(1), WC: Theta(nrElements) -> Total complexity: O(nrElements)

BSTNode* SortedMultiMap::searchNode(TKey c, TValue v) {
    BSTNode* returnNode = nullptr;
    BSTNode* currentNode = this->root;
    bool found = false;
    while (currentNode != nullptr && !found) {
        if (this->rel(c, currentNode->info.first)) {
            // the element is on the left tree if it exists
            if (c == currentNode->info.first) {
                if (v == currentNode->info.second) {
                    returnNode = currentNode;
                    found = true;
                }
            }
            currentNode = currentNode->left;
        } else {
            // the element is on the right tree if it exists
            currentNode = currentNode->right;
        }
    }
    return returnNode;
}
//BC: Theta(1), WC: Theta(nrElements) -> Total complexity: O(nrElements)

bool SortedMultiMap::remove(TKey c, TValue v) {
	bool removed = false;
	BSTNode* toRemove = this->searchNode(c, v);
	if (toRemove != nullptr) {
        if (toRemove == this->root) {
            //remove the root
            this->removeRoot(toRemove);
        } else {
            //remove a node
            this->removeNode(toRemove);
        }
	    removed = true;
        this->nrElements--;
	}
    return removed;
}
//BC: Theta(1), WC: Theta(nrElements + height) -> Total complexity: O(nrElements + height)


int SortedMultiMap::size() const {
    return this->nrElements;
}
//Theta(1)

bool SortedMultiMap::isEmpty() const {
	if (this->nrElements == 0)
        return true;
	return false;
}
//Theta(1)

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
//Theta(1)

SortedMultiMap::~SortedMultiMap() {
    this->deleteSortedMultiMap(this->root);
}
//Theta(nrElements)

void SortedMultiMap::deleteSortedMultiMap(BSTNode* currentNode) {
    if (currentNode != nullptr) {
        if (currentNode->left != nullptr) {
            this->deleteSortedMultiMap(currentNode->left);
        }
        if (currentNode->right != nullptr) {
            this->deleteSortedMultiMap(currentNode->right);
        }
    }
}
//Theta(nrElements)

BSTNode* SortedMultiMap::findMaxLeftSide(BSTNode* currentNode) {
    //find the maximum of the left subtree
    BSTNode* node = currentNode->left;
    bool changed = false;
    while (node->right != nullptr) {
        node = node->right;
        changed = true;
    }
    if (changed) {
        node->parent->right = nullptr;
    }
    return node;
}
//BC: Theta(1), WC: Theta(height) -> Total complexity: O(height)

void SortedMultiMap::removeRoot(BSTNode *toRemove) {
    if (toRemove->right != nullptr && toRemove->left != nullptr) {
        //remove a root with two children
        BSTNode* replacementNode = this->findMaxLeftSide(toRemove);
        if (replacementNode == toRemove->left) {
            // the replacement is the left child, no new links made
            replacementNode->right = toRemove->right;
            replacementNode->right->parent = replacementNode;
            replacementNode->parent = nullptr;
            BSTNode *rootToDelete = toRemove;
            this->root = replacementNode;
            delete rootToDelete;
        } else {
            // the replacement is not the left child, additional links need to be done
            replacementNode->right = toRemove->right;
            replacementNode->right->parent = replacementNode;
            replacementNode->parent = nullptr;
            replacementNode->left = toRemove->left;
            replacementNode->left->parent = replacementNode;
            BSTNode* rootToDelete = toRemove;
            this->root = replacementNode;
            delete rootToDelete;
        }
    } else if (toRemove->right == nullptr && toRemove->left == nullptr) {
        //remove a leaf root
        BSTNode* rootToDelete = toRemove;
        this->root = nullptr;
        delete rootToDelete;
    } else {
        //remove a root with one  child
        if (toRemove->right != nullptr) {
            //the root has a right child
            BSTNode* newRoot = toRemove->right;
            BSTNode* rootToDelete = toRemove;
            newRoot->parent = nullptr;
            this->root = newRoot;
            delete rootToDelete;
        } else {
            //the root has a left child
            BSTNode* newRoot = toRemove->left;
            BSTNode* rootToDelete = toRemove;
            newRoot->parent = nullptr;
            this->root = newRoot;
            delete rootToDelete;
        }
    }
}
//BC: Theta(1), WC: Theta(height) -> Total complexity: O(height)

void SortedMultiMap::removeNode(BSTNode* toRemove) {
    if (toRemove->right != nullptr && toRemove->left != nullptr) {
        //remove a node with two children
        BSTNode* replacementNode = this->findMaxLeftSide(toRemove);
        if (replacementNode == toRemove->left) {
            //the replacement is the left child, no links need to be done
            replacementNode->right = toRemove->right;
            replacementNode->right->parent = replacementNode;
            replacementNode->parent = toRemove->parent;
            if (replacementNode->parent->left == toRemove) {
                // the replacement will replace the left child of the removed node
                replacementNode->parent->left = replacementNode;
            } else {
                // the replacement will replace the right child of the removed node
                replacementNode->parent->right = replacementNode;
            }
            BSTNode* nodeToDelete = toRemove;
            toRemove = replacementNode;
            delete nodeToDelete;
        } else {
            // the replacement is not the immediate left child, we need additional links
            replacementNode->right = toRemove->right;
            replacementNode->right->parent = replacementNode;
            replacementNode->parent = toRemove->parent;
            if (replacementNode->parent->left == toRemove) {
                // replacement will replace the left child of the removed node
                replacementNode->parent->left = replacementNode;
            } else {
                // replacement will replace the right child of the removed node
                replacementNode->parent->right = replacementNode;
            }
            replacementNode->left = toRemove->left;
            replacementNode->left->parent = replacementNode;
            BSTNode* nodeToDelete = toRemove;
            toRemove = replacementNode;
            delete nodeToDelete;
        }
    } else if (toRemove->right == nullptr && toRemove->left == nullptr) {
        //remove a leaf node
        if (toRemove->parent->left == toRemove) {
            // the node is the left child of its parent
            toRemove->parent->left = nullptr;
            delete toRemove;
        } else if (toRemove->parent->right == toRemove) {
            // the node is the right child of its parent
            toRemove->parent->right = nullptr;
            delete toRemove;
        }
    } else {
        //remove a node with one child
        if (toRemove->parent->left == toRemove) {
            // the node is the left child of its parent
            if (toRemove->left != nullptr) {
                // if the node has a left child, we need to link it to the parent of its parent
                toRemove->parent->left = toRemove->left;
                toRemove->left->parent = toRemove->parent;
            } else {
                // if the node has a right child, we need to link it to the parent of its parent
                toRemove->parent->left = toRemove->right;
                toRemove->right->parent = toRemove->parent;
            }
            delete toRemove;
        } else {
            // the node is the right child of its parent
            if (toRemove->left != nullptr) {
                // if the node has a left child, we need to link it to the parent of its parent
                toRemove->parent->right = toRemove->left;
                toRemove->left->parent = toRemove->parent;
            } else {
                // if the node has a right child, we need to link it to the parent of its parent
                toRemove->parent->right = toRemove->right;
                toRemove->right->parent = toRemove->parent;
            }
            delete toRemove;
        }
    }
}
//BC: Theta(1), WC: Theta(height) -> Total complexity: O(height)

void SortedMultiMap::replaceInOrderRecursive(BSTNode *startNode, Transformer t) {
    if (startNode != nullptr) {
        this->replaceInOrderRecursive(startNode->left, t);
        TValue value = t(startNode->info.first, startNode->info.second);
        startNode->info.second = value;
        this->replaceInOrderRecursive(startNode->right, t);
    }
}
//Theta(n)

void SortedMultiMap::replaceAll(Transformer  t) {
    BSTNode* startNode = this->root;
    this->replaceInOrderRecursive(startNode, t);
}
//Theta(n)
