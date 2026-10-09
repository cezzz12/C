#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>

SortedBag::SortedBag(Relation r) {
    head = NULL_POS;
    tail = NULL_POS;
    currentSize = 0;
    uniqueCount = 0;
    relation = r;
    initializeNodes();
}

// Time complexity: O(CAPACITY)
void SortedBag::initializeNodes() {
    for (int i = 0; i < CAPACITY - 1; i++) {
        nodes[i].next = i + 1;
    }
    nodes[CAPACITY - 1].next = NULL_POS;
    firstEmpty = 0;
}

// AC=BC=WC= O(1)
int SortedBag::allocatePosition() {
    if (firstEmpty == NULL_POS) {
        throw std::exception();
    }
    int newPosition = firstEmpty;
    firstEmpty = nodes[firstEmpty].next;
    nodes[newPosition].next = NULL_POS;
    nodes[newPosition].prev = NULL_POS;
    return newPosition;
}

// AC=BC=WC O(1)
void SortedBag::deallocatePosition(int position) {
    nodes[position].element = NULL_TCOMP;
    nodes[position].frequency = 0;
    nodes[position].next = firstEmpty;
    nodes[position].prev = NULL_POS;
    firstEmpty = position;
}

// BC=WC=AC= O(n)
int SortedBag::findPosition(TComp e) const {
    if (head == NULL_POS) {
        return NULL_POS;
    }

    int current = head;
    while (current != NULL_POS) {
        if (nodes[current].element == e) {
            return current;
        }
        if (!relation(nodes[current].element, e)) {
            return nodes[current].prev;
        }

        current = nodes[current].next;
    }
    return tail;
}



// Time complexity:
// BC - O(1) adding duplicate to head
// AC - O(n)
// WC - O(n) insert new unique element at tail
void SortedBag::add(TComp e) {
    if (head == NULL_POS) {
        head = allocatePosition();
        nodes[head].element = e;
        nodes[head].frequency = 1;
        tail = head;
        currentSize = 1;
        uniqueCount = 1;
        return;
    }

    int pos = findPosition(e);

    if (pos != NULL_POS && nodes[pos].element == e) {
        nodes[pos].frequency++;
        currentSize++;
        return;
    }
    int newPos = allocatePosition();
    nodes[newPos].element = e;
    nodes[newPos].frequency = 1;

    if (pos == NULL_POS) {
        if (head != NULL_POS && !relation(nodes[head].element, e)) {

            nodes[newPos].next = head;
            nodes[head].prev = newPos;
            head = newPos;
        } else {

            if (tail != NULL_POS) {
                nodes[tail].next = newPos;
                nodes[newPos].prev = tail;
                tail = newPos;
            } else {
                head = newPos;
                tail = newPos;
            }
        }
    }

    else if (pos == tail) {
        if (nodes[pos].element == e) {
            nodes[pos].frequency++;
            currentSize++;
            deallocatePosition(newPos);
            return;
        } else {
            // Add after tail
            nodes[tail].next = newPos;
            nodes[newPos].prev = tail;
            tail = newPos;
        }
    }
    // Insert in the middle
    else {
        int nextNode = nodes[pos].next;
        nodes[newPos].next = nextNode;
        nodes[newPos].prev = pos;
        nodes[pos].next = newPos;
        if (nextNode != NULL_POS) {
            nodes[nextNode].prev = newPos;
        }
    }

    currentSize++;
    uniqueCount++;
}

// Time complexity:
// BC - O(1) remove head
// AC - O(n)
// WC - O(n) not found or tail
bool SortedBag::remove(TComp e) {
    if (head == NULL_POS) {
        return false;
    }

    int current = head;

    // Find the node with element e
    while (current != NULL_POS && nodes[current].element != e) {
        current = nodes[current].next;
    }

    if (current == NULL_POS) {
        return false;
    }

    nodes[current].frequency--;
    currentSize--;

    if (nodes[current].frequency == 0) {
        if (current == head && current == tail) {
            head = NULL_POS;
            tail = NULL_POS;
        } else if (current == head) {
            head = nodes[head].next;
            nodes[head].prev = NULL_POS;
        } else if (current == tail) {
            tail = nodes[tail].prev;
            nodes[tail].next = NULL_POS;
        } else {
            int prevNode = nodes[current].prev;
            int nextNode = nodes[current].next;
            nodes[prevNode].next = nextNode;
            nodes[nextNode].prev = prevNode;
        }

        deallocatePosition(current);
        uniqueCount--;
    }

    return true;
}

// Time complexity:
// BC - O(1) at head
// AC - O(n),
// WC - O(n) element not found
bool SortedBag::search(TComp e) const {
    int current = head;
    while (current != NULL_POS) {
        if (nodes[current].element == e) {
            return true;
        }
        current = nodes[current].next;
    }
    return false;
}


// BC - O(1),
// AC - O(n),
// WC - O(n)
int SortedBag::nrOccurrences(TComp e) const {
    int current = head;
    while (current != NULL_POS) {
        if (nodes[current].element == e) {
            return nodes[current].frequency;
        }
        current = nodes[current].next;
    }
    return 0;
}

// AC=BC=WC=O(1)
int SortedBag::size() const {
    return currentSize;
}

// AC=BC=WC= O(1)
bool SortedBag::isEmpty() const {
    return currentSize == 0;
}

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
    // No dynamic memory to deallocate in this implementation
}