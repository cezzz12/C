//
// Created by Cezar on 06.04.2025.
//

#ifndef SORTEDBAG_H
#define SORTEDBAG_H
typedef int TComp;
typedef TComp TElem;
typedef bool(*Relation)(TComp, TComp);
#define NULL_TCOMP -11111
#define CAPACITY 10000
#define NULL_POS -1

class SortedBagIterator;

class SortedBag {
    friend class SortedBagIterator;

private:
    // Node structure for DLLA
    struct Node {
        TComp element;
        int frequency;
        int next;
        int prev;

        Node() : element(NULL_TCOMP), frequency(0), next(NULL_POS), prev(NULL_POS) {}
        Node(TComp elem, int freq) : element(elem), frequency(freq), next(NULL_POS), prev(NULL_POS) {}
    };

    Node nodes[CAPACITY];
    int head;
    int tail;
    int firstEmpty;
    int currentSize;
    int uniqueCount;
    Relation relation;

    int allocatePosition();
    void deallocatePosition(int position);
    void initializeNodes();

    // Finds the position where a new element should be inserted
    int findPosition(TComp e) const;

public:
    SortedBag(Relation r);

    void add(TComp e);

    bool remove(TComp e);

    bool search(TComp e) const;

    int nrOccurrences(TComp e) const;

    int size() const;

    SortedBagIterator iterator() const;

    bool isEmpty() const;

    void empty();

    // Destructor
    ~SortedBag();
};
#endif //SORTEDBAG_H