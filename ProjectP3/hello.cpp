#include <iostream>
#include <math.h>

using namespace std;


/*  BHeap Class
 *
 *  Binomial Heap data structure with insert, merge, extractmin methods
 * 
 *  Heap is stored as a linked list of nodes
 */
template <class keytype, class valuetype>
class BHeap {

private:

    /*   Node Class
     *
     *   Stores key and value pair to be put into heap
     */
    class Node { 
        public:
            keytype key;
            valuetype value;
            int degree;
            Node* parent;
            Node* right;
            Node* sibling;

            Node() {}
            Node(keytype k, valuetype v) {
                key = k;
                value = v;
                degree = 0;
                parent = nullptr;
                right = nullptr;
                sibling = nullptr;
            }
    };

    // Puts all trees from both heaps into one heap
    // Does NOT merge trees of equal degrees together
    void combine(BHeap<keytype, valuetype> &H2) {

        Node* newHeap = nullptr;
        Node* h1 = heap;
        Node* h2 = H2.heap;
        Node* a;
        Node* b;

        // Starts heap with the heap of the smallest degree
        if (h1 != nullptr) {
            if (h2 != nullptr) {
                if (h1->degree <= h2->degree) newHeap = h1;
                else if (h1->degree > h2->degree) newHeap = h2;
            }
            else newHeap = h1;
        }
        else newHeap = h2;

        // Mergesort algorithm for the trees in each heap
        // Inserts tree with smallest degree into new heap
        while(h1 != nullptr && h2 != nullptr) {
            if (h1->degree < h2->degree) {
                if (h1->sibling == nullptr) {
                    while (h2 != nullptr) {
                        h1->sibling = h2;
						h1 = h1->sibling;
						h2 = h2->sibling;
                    }
                }
                h1 = h1->sibling;
            }
            else if (h1->degree == h2->degree) {
                a = h1->sibling;
                h1->sibling = h2;
                h1 = a;
            }
            else {
                while (h2->sibling != nullptr) {
					if (h2->sibling->degree < h1->degree) {
						h2 = h2->sibling;
					}
                    else break;
				}
                b = h2->sibling;
                h2->sibling = h1;
                h2 = b;
            }
        }

        heap = newHeap;
        H2.heap = nullptr;     
    }

    // Recursively prints an individual tree
    void printTree(Node* node) {
        if (node == nullptr) return;
        cout << node->key << " ";
        printTree(node->right);
        if (node->parent != nullptr) {
            printTree(node->sibling);
        }
    }

    // Recursively reverses a heap
    // Used for extractmin to reverse subheap to merge back into heap
    void reverse(Node* node) {
        node->parent = nullptr;
        if (node->sibling != nullptr) {
            reverse(node->sibling);
            node->sibling->sibling = node;
        }
        else reversedHeap = node;
    }

    // Recursively copies a heap given the head node
    Node* copyNode(Node* node, Node* parent) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->key, node->value);
        newNode->degree = node->degree;
        newNode->sibling = copyNode(node->sibling, parent);
        newNode->right = copyNode(node->right, newNode);
        newNode->parent = parent;
        return newNode;
    }


public:

    Node* heap;
    Node* reversedHeap;
    keytype garbageValue;
    int count;

    // Creates empty heap
    BHeap() {
        heap = nullptr;
        reversedHeap = nullptr;
        count = 0;
    }

    // Repeatedly inserts nodes into heap
    BHeap(keytype k[], valuetype v[], int s) {
        heap = nullptr;
        reversedHeap = nullptr;
        count = 0;
        for (int i = 0; i < s; i++) {
            insert(k[i], v[i]);
        }
    }

    // Copies heap from source
    BHeap(const BHeap& src) {
        heap = nullptr;
        reversedHeap = nullptr;
        count = 0;

        heap = copyNode(src.heap, nullptr);
    }

    // Copies heap from source and returns it
    BHeap& operator=(const BHeap& src) {
        heap = nullptr;
        reversedHeap = nullptr;
        count = 0;

        heap = copyNode(src.heap, nullptr);
        return *this;
    }

    // Deletes heap
    ~BHeap() {
        for (int i = 0; i < count; i++) {
            extractMin();
        }
    }

    // Returns key of minimum key node in heap
    keytype peakKey() {
        Node* min = heap;
        Node* node;
        for (node = heap; node != nullptr; node = node->sibling) {
            if (node->key < min->key) min = node;
        }
        return min->key;
    }

    // Returns value of minimum key node in heap
    valuetype peakValue() {
        Node* min = heap;
        Node* node;
        for (node = heap; node != nullptr; node = node->sibling) {
            if (node->key < min->key) min = node;
        }
        return min->value;
    }

    // Removes smallest node from heap and merges its subheap back into heap
    keytype extractMin() {
        reversedHeap = nullptr;

        if (heap == nullptr) {
            return garbageValue;
        }

        // Find min node
        Node* node = heap;
        Node* prev = nullptr;
        Node* min = node;
        while (node->sibling != nullptr) {
            if (node->sibling->key < min->key) {
                min = node->sibling;
                prev = node;
            }
            node = node->sibling;
        }

        // Sets heap based on what is left of heap after removal
        if (prev == nullptr && min->sibling == nullptr)
            heap = nullptr;
        else if (prev == nullptr)
            heap = min->sibling;
        else if (min->sibling == nullptr)
            prev->sibling = nullptr;
        else
            prev->sibling = min->sibling;

        if (min->right != nullptr) {
            reverse(min->right);
            min->right->sibling = nullptr;
        }

        // Creates temporary heap to store the reversed heap;
        BHeap<keytype, valuetype> temp = BHeap<keytype, valuetype>();
        temp.heap = reversedHeap;

        merge(temp);
        return min->key;
    }

    // Inserts new node into heap
    void insert(keytype k, valuetype v) {
        Node* newNode = new Node(k, v);

        // Heap empty, create B0 heap
        if (count == 0) {
            heap = newNode;
            count += pow(2, newNode->degree);
            return;
        }

        // Heap not empty, create temporary B0 heap to be merged into current heap
        BHeap<keytype, valuetype> temp = BHeap<keytype, valuetype>();
        temp.insert(k, v);

        merge(temp);
    }

    // Merges two heaps together
    void merge(BHeap<keytype, valuetype> &H2) {
        
        // Put all trees into one heap, not merged yet
        combine(H2);

        if (heap == nullptr) return;

        Node* prev = nullptr;
        Node* node = heap;
        Node* next = node->sibling;

        // Merges trees of the same degree into one another
        while (next != nullptr) {
            if ((node->degree != next->degree) || ((next->sibling != nullptr) && (next->sibling->degree == node->degree))) {
                prev = node;
                node = next;
            }
            else {
                if (node->key <= next->key) {
                    node->sibling = next->sibling;
                    next->parent = node;
                    next->sibling = node->right;
                    node->right = next;
                    node->degree++;
                }
                else {
                    if (prev == nullptr) heap = next;
                    else prev->sibling = next;
                    node->parent = next;
                    node->sibling = next->right;
                    next->right = node;
                    next->degree++;
                    node = next;
                }
            }

            next = node->sibling;
        }
    }

    // Recursively call printTree for each tree head node in heap
    void printKey() {
        Node* node;
        cout << endl;
        for (node = heap; node != nullptr; node = node->sibling) {
            cout << "B" << node->degree << endl;
            printTree(node);
            cout << endl;
        }
        cout << endl;
    }

};