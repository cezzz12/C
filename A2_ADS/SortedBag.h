//
// Created by Cezar on 06.04.2025.
//

#ifndef SORTEDBAG_H
#define SORTEDBAG_H
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111;

class SortedBagIterator;

class SortedBag {
    friend class SortedBagIterator;

private:
    // Node structure for doubly linked list
    struct Node {
        TComp element;
        int frequency;
        Node* next;
        Node* prev;

        Node(TComp elem, int freq) : element(elem), frequency(freq), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int currentSize;
    int uniqueCount;
    Relation relation;

    // Time Complexity: O(n) - where n is the number of unique elements
    // Requires traversing the list to find the correct position
    Node* findPosition(TComp e) const;

public:
    // Time Complexity: O(1) - Constant time initialization
    SortedBag(Relation r);

    // Time Complexity: O(n) - where n is the number of unique elements
    // Finding position takes O(n), insertion itself is O(1)
    void add(TComp e);

    // Time Complexity: O(n) - where n is the number of unique elements
    // Finding element takes O(n), removal itself is O(1)
    bool remove(TComp e);

    // Time Complexity: O(n) - where n is the number of unique elements
    // Requires traversing the list to find the element
    bool search(TComp e) const;

    // Time Complexity: O(n) - where n is the number of unique elements
    // Requires traversing the list to find the element
    int nrOccurrences(TComp e) const;

    // Time Complexity: O(1) - Returns a field value
    int size() const;

    // Time Complexity: O(1) - Iterator initialization is constant time
    SortedBagIterator iterator() const;

    // Time Complexity: O(1) - Checks if size is 0
    bool isEmpty() const;

    // Time Complexity: O(n) - where n is the number of unique elements
    // Requires traversing the list to delete all nodes
    ~SortedBag();
};
#endif //SORTEDBAG_H