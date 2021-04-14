#include "CDA.cpp"
template <typename keytype>

class Heap{

    private:

    CDA<keytype> heap;

    //Gets the parent of current node
    int parent(int child){
        if(child==0) return -1;
        else return (child-1) / 2;
    }

    //Gets the left child of current node
    int left(int parent){
        int left = 2*parent + 1;
        if(left < heap.Length()) return left;
        else return -1;
    }

    //Gets the right child of current node
    int right(int parent){
        int right = 2*parent + 2;
        if(right < heap.Length()) return right;
        else return -1;
    }

    public:

    //Default constructor
    Heap();

    //Uses O(n) bottom up method to contrust a heap given the array k of size s
    Heap(keytype k[], int s);

    //Copy Constructor
    Heap(const Heap &src);

    //Copy Assignment Operator
    Heap& operator=(const Heap &src);

    //Destructor
    ~Heap();

    //Returns the minimum key in the heap without modifiying the heap
    keytype peekKey(){
        return heap[0];
    } 

    //Removes the minimum key in the heap and returns the key
    keytype extractMin();

    //Inserts the key k into the heap
    void insert(keytype k);

    //Writes the keys stored in the array, starting at the root
    void printKey(){
        for(int i = 0 ; i < heap.Length; i++){
            cout << heap[i] << " ";
        }
        cout << endl;
    }

};