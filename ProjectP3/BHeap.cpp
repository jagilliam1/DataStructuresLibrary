template <typename keytype>

struct Node{
    keytype data;
    int degree;
    Node *child, *sibling, *parent;
};

class BHeap{

    private:

    public:

    //Default constructor
    BHeap();

    //For this constructor the heap should be built using the array K containing s items of keytype. The heap should be constructed using repeated insertion.
    BHeap(keytype k[], int s);

    //Copy Constructor
    BHeap(const Heap &src);

    //Copy Assignment Operator
    BHeap& operator=(const Heap &src);

    //Destructor
    ~BHeap();

    //Returns the minimum key in the heap without modifiying the heap
    keytype peekKey(); 

    //Removes the minimum key in the heap and returns the key
    keytype extractMin();

    //Inserts the key k into the heap
    void insert(keytype k);

    //Merges the heap H2 into the current heap. Consumes H2
    void merge(BHeap<keytype> &H2);

    //Writes the keys stored in the heap, printing the smallest binomial tree first. When printing a
    //binomial tree, print the size of tree first and then use a modified preorder traversal of the tree.
    void printKey();

};