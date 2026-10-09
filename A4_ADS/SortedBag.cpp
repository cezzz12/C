#include "SortedBag.h"
#include "SortedBagIterator.h"

// Initializes an empty SortedBag with given relation function
// AC=BC=WC: O(1) - constructor just initializes variables
// Theta: Θ(1) - always constant time
SortedBag::SortedBag(Relation r) {
    relation = r;
    root = nullptr;
    totalSize = 0;
}

// BC: O(1) - when tree is empty or element is at root
// WC: O(n) - when tree is completely unbalanced (linear chain)
// AC: O(log n) - when tree is reasonably balanced

void SortedBag::add(TComp e) {
    if (root == nullptr) {  // tree is empty, create root node
        root = new Node(e);
    } else { // tree is not empty, find the correct position
        Node* current = root;
        Node* parent = nullptr;
        // traverse the tree to find the correct position for the new element
        while (current != nullptr) {
            if (e == current->data.first) { // element already exists, increment frequency
                current->data.second++;
                totalSize++;
                return;
            }
            parent = current;
            if (relation(e, current->data.first)) { // use relation to decide direction
                //(go left if e is before and right if e after)
                current = current->left;
            } else {
                current = current->right;
            }
        }
        //element not found, create a new node
        Node* newNode = new Node(e);
        if (relation(e, parent->data.first)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }
    totalSize++;
}

// Removes one occurrence of element; decrements frequency or deletes node if last occurrence
// BC: O(1) - element is at root and has frequency > 1
// WC: O(n) - element is leaf in unbalanced tree or doesn't exist
// AC: O(log n) - when tree is reasonably balanced

bool SortedBag::remove(TComp e) {
    Node* current = root;
    Node* parent = nullptr;
    bool isLeft = false;

    // find the node to remove
    while (current != nullptr && current->data.first != e) {
        parent = current;
        if (relation(e, current->data.first)) {
            current = current->left; //element is less, go left
            isLeft = true;
        } else {
            current = current->right;   //element is greater, go right
            isLeft = false;
        }
    }

    if (current == nullptr) return false; // element not found

    // if frequency > 1, just decrement
    if (current->data.second > 1) {
        current->data.second--;
        totalSize--;
        return true;
    }

    // handle node deletion based on number of children
    if (current->left == nullptr && current->right == nullptr) {
        // Leaf node so delete directly
        if (current == root) root = nullptr;
        else if (isLeft) parent->left = nullptr;
        else parent->right = nullptr;
        delete current;
    }
    else if (current->left == nullptr) {
        // only right child
        if (current == root) root = current->right; //root becomes right child and connect to parent
        else if (isLeft) parent->left = current->right;
        else parent->right = current->right;
        delete current;
    }
    else if (current->right == nullptr) {
        // only left child
        if (current == root) root = current->left; //root becomes left child and connect to parent
        else if (isLeft) parent->left = current->left;
        else parent->right = current->left;
        delete current;
    }
    else {
        // two children - replace with inorder successor
        Node* successor = current->right;
        Node* successorParent = current;
        // find inorder successor (leftmost node in right subtree)
        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }
        // copy successor's data to current node
        current->data = successor->data;
        //remove the successor node
        if (successorParent == current) {
            successorParent->right = successor->right;
        } else {
            successorParent->left = successor->right;
        }
        delete successor;
    }
    totalSize--;
    return true;
}

// Searches for element in BST, returns true if found
// BC: O(1) - element is at root
// WC: O(n) - element is leaf in unbalanced tree or doesn't exist
// AC: O(log n) - when tree is reasonably balanced

bool SortedBag::search(TComp e) const {
    Node* current = root;
    while (current != nullptr) {
        if (e == current->data.first) return true;
        if (relation(e, current->data.first)) current = current->left;
        else current = current->right;
    }
    return false;
}

// Returns frequency count of element in BST, 0 if not found
//BC: O(1) - element is at root
//WC: O(n) - element is leaf in unbalanced tree or doesn't exist
//AC: O(log n) - when tree is reasonably balanced

int SortedBag::nrOccurrences(TComp e) const {
    Node* current = root;
    while (current != nullptr) {
        if (e == current->data.first) return current->data.second;
        if (relation(e, current->data.first)) current = current->left;
        else current = current->right;
    }
    return 0;
}

// Returns total number of elements (sum of all frequencies)
//AC=BC=WC: O(1) - just returns the size
// Theta: Θ(1) - always constant time
int SortedBag::size() const {
    return totalSize;
}

// Checks if bag is empty by comparing size to 0
//AC=BC=WC: O(1)
// Theta: Θ(1) - always constant time
bool SortedBag::isEmpty() const {
    return totalSize == 0;
}

// Recursively deletes all nodes in the BST (post-order traversal)
//AC=BC=WC: O(n)  we traverse all nodes
// Theta: Θ(n) - we visit all nodes in the tree
void SortedBag::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Destructor - deallocates all memory by calling destroyTree
// AC=BC=WC: O(n) - must delete all nodes
// Theta: Θ(n) - visits all nodes
SortedBag::~SortedBag() {
    destroyTree(root);
}

// Creates and returns iterator for traversing bag in sorted order
// AC=BC=WC: O(1) - just creates iterator object
// Theta: Θ(1) - always constant time
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

// helper function to add element to result tree with frequency for intersection
//BC= O(1) - when tree is empty
//WC=O(n) - when we need to traverse to find position
//AC=O(log n) - when tree is balanced, each search costs log n
void addToResult(Node*& root, TComp elem, int freq, Relation rel) {
    if (root == nullptr) { //if tree is empty, create new root
        root = new Node(elem);
        root->data.second = freq;
        return;
    }
    // start from root and find position
    Node* current = root;
    Node* parent = nullptr;
    while (current != nullptr) {
        if (elem == current->data.first) { // if element already exists, update frequency
            current->data.second = freq;
            return;
        }
        parent = current;
        if (rel(elem, current->data.first)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    Node* newNode = new Node(elem);
    newNode->data.second = freq;
    if (rel(elem, parent->data.first)) { //insert as left or right child based on relation
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
}

//BC=O(h1) - when current tree is empty
// WC: O(n* log n) - when all elements are common and we need to search bag b
// AC: O(n * log n) - when tree b is balanced, each search costs log n2
// Theta: Θ(n*log n)
void SortedBag::intersection(const SortedBag& b) {
    if (root == nullptr) return;
    // create a new root for result
    Node* newRoot = nullptr;
    // stack for non-recursive traversal
    std::stack<Node*> stack;
    Node* current = root;

    // traverse current tree and check each element against bag b
    while (current != nullptr || !stack.empty()) {
        // reach the leftmost node of the current node
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }

        current = stack.top(); //get  to  the leftmost node and remove it from stack
        stack.pop();

        // check if element exists in bag b
        int freqB = b.nrOccurrences(current->data.first);
        if (freqB > 0) { // If element exists in both bags
            // add to result with minimum frequency
            int minFreq = std::min(current->data.second, freqB);
            addToResult(newRoot, current->data.first, minFreq, relation);
        }

        current = current->right;
    }

    // update size
    totalSize = 0;
    std::stack<Node*> countStack;
    current = newRoot;
    while (current != nullptr || !countStack.empty()) { //traverse new tree to count total size
        while (current != nullptr) {
            countStack.push(current);
            current = current->left;
        }
        if (!countStack.empty()) {
            current = countStack.top();
            countStack.pop();
            totalSize += current->data.second;
            current = current->right;
        }
    }
    // delete old tree and set new root
    destroyTree(root);
    root = newRoot;
}