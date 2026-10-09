#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

// Time Complexity: O(1) - Constant time initialization
SortedBag::SortedBag(Relation r) {
    head = nullptr;
    tail = nullptr;
    currentSize = 0;
    uniqueCount = 0;
    relation = r;
}

// Time Complexity: O(n) - where n is the number of unique elements
// Best- O(1) Average,Worst -O(n)
// Requires traversing the list to find the correct position
SortedBag::Node* SortedBag::findPosition(TComp e) const {
    if (head == nullptr) {
        return nullptr;
    }
    Node* current = head;
    while (current != nullptr) {
        if (current->element == e) {
            return current;
        }
        if (!relation(current->element, e)) {
            return current->prev;
        }

        current = current->next;
    }
    return tail;
}

// Time Complexity: O(n) - where n is the number of unique elements
// Time Complexity:
// Best - O(1) (element at head/tail or already exists),
// Average - O(n),
// Worst - O(n) (insert new unique element in middle)
void SortedBag::add(TComp e) {
    if (head == nullptr) {
        head = new Node(e, 1);
        tail = head;
        currentSize = 1;
        uniqueCount = 1;
        return;
    }

    Node* pos = findPosition(e);
    if (pos != nullptr && pos->element == e) {
        pos->frequency++;
        currentSize++;
        return;
    }
    Node* newNode = new Node(e, 1);

    if (pos == nullptr) {
        if (!relation(head->element, e)) {
            // New head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        } else {
            // New tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    // Insert at end
    else if (pos == tail) {
        if (pos->element == e) {
            // Element already exists at tail
            pos->frequency++;
            currentSize++;
            delete newNode;
            return;
        } else {
            // Add after tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    // Insert in the middle
    else {
        Node* nextNode = pos->next;
        newNode->next = nextNode;
        newNode->prev = pos;
        pos->next = newNode;
        if (nextNode != nullptr) {
            nextNode->prev = newNode;
        }
    }

    currentSize++;
    uniqueCount++;
}

// Time Complexity:
// Best - O(1) (element at head),
// Average - O(n),
// Worst - O(n) (element not present)
bool SortedBag::remove(TComp e) {
    if (head == nullptr) {
        return false;
    }

    Node* current = head;

    // Find the node with element e
    while (current != nullptr && current->element != e) {
        current = current->next;
    }

    if (current == nullptr) {
        return false;
    }
    current->frequency--;
    currentSize--;

    if (current->frequency == 0) {
        if (current == head && current == tail) {
            head = nullptr;
            tail = nullptr;
        } else if (current == head) {
            head = head->next;
            head->prev = nullptr;
        } else if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete current;
        uniqueCount--;
    }

    return true;
}

// Time Complexity: O(n) - where n is the number of unique elements
// Requires traversing the list to find the element
// Time Complexity:
// Best - O(1) (element at head),
// Average - O(n),
// Worst - O(n) (element not present)
bool SortedBag::search(TComp e) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->element == e) {
            return true;
        }
        current = current->next;
    }
    return false;
}
// Time Complexity:
// Best - O(1),
// Average - O(n),
// Worst - O(n)
int SortedBag::nrOccurrences(TComp e) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->element == e) {
            return current->frequency;
        }
        current = current->next;
    }
    return 0;
}

// Time Complexity: O(1) - Returns a field value
int SortedBag::size() const {
    return currentSize;
}

// Time Complexity: O(1) - Checks if size is 0
bool SortedBag::isEmpty() const {
    return currentSize == 0;
}

// Time Complexity: O(1) - Iterator initialization is constant time
SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

// Time Complexity: O(n) - where n is the number of unique elements
// Requires traversing the list to delete all nodes
SortedBag::~SortedBag() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}