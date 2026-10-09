#include "SortedBagIterator.h"
#include <exception>

// Helper function: pushes all left descendants of node onto stack (for inorder traversal)
// BC: O(1) - when node is nullptr
// WC: O(n) - when we traverse to leftmost node (h = height of subtree)
// AC: O(log n) - average depth in balanced tree
void SortedBagIterator::pushAllLeft(Node* node) {
    while (node != nullptr) {
        stack.push(node);
        node = node->left;
    }
}

// Constructor: initializes iterator and positions it at first element
// BC: O(1) - when tree is empty
// WC: O(n) - when we need to traverse to leftmost node
// AC: O(log n) - average height in balanced tree
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    first();
}

// Resets iterator to first element (leftmost node in BST)
// BC: O(1) - when tree is empty
// WC: O(n) - when we need to traverse to leftmost node
// AC: O(log n) - average height in balanced tree
void SortedBagIterator::first() {
    while (!stack.empty()) {
        stack.pop();
    }
    currentFrequency = 1;
    pushAllLeft(bag.root);
    if (!stack.empty()) {
        currentNode = stack.top();
    } else {
        currentNode = nullptr;
    }
}

// Advances iterator to next element; handles multiple occurrences and inorder traversal
//AC=BC=WC=O(1) amortized - each node visited once during complete traversal
// Theta: Θ(1) amortized
void SortedBagIterator::next() {
    if (!valid()) {
        throw std::exception();
    }

    // if current element has more occurrences, just increment frequency
    if (currentFrequency < currentNode->data.second) {
        currentFrequency++;
        return;
    }

    // move to next node in inorder traversal
    Node* top = stack.top();
    stack.pop();

    // if current node has right subtree, process it
    if (top->right != nullptr) {
        pushAllLeft(top->right);
    }

    // set current to next node or mark as invalid
    if (!stack.empty()) {
        currentNode = stack.top();
        currentFrequency = 1;
    } else {
        currentNode = nullptr;
        currentFrequency = 0;
    }
}

// returns current element (throws exception if iterator invalid)
//AC=BC=WC: O(1) - just returns the current element
// Theta: Θ(1) - always constant time
TElem SortedBagIterator::getCurrent() {
    if (!valid()) {
        throw std::exception();
    }
    return currentNode->data.first;
}

// Checks if iterator points to valid element
// AC=BC=WC: O(1) - simple null check
// Theta: Θ(1) - always constant time
bool SortedBagIterator::valid() {
    return currentNode != nullptr;
}