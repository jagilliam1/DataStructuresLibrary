#include "CDA.cpp"
template <typename keytype>
//Might need to move the include down here and change all the elmtype in CDA into keytype 

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

    //Heapifys the heap upwards
    void heapifyUp(int x){
        //Checks if heap order is incorrect and makes swaps
        if(x >= 0 && parent(x) >= 0 && heap[parent(x)] > heap[x]){
            keytype temp = heap[x];
            heap[x] = heap[parent(x)];
            heap[parent(x)] = temp;
            heapifyUp(parent(x));
        }
        return;
    }

    //Heapifys the heap downwards
    void heapifyDown(int x){
        int c1 = left(x);
        int c2 = right(x);
        //Determines which child is the greater of the two.
        if(c1 >= 0 && c2 >= 0 && heap[c1] > heap[c2]) c1 = c2;

        //Checks if heap order is incorrect and makes swaps
        if(c1 > 0 && heap[x] > heap[c1]){
            keytype temp = heap[x];
            heap[x] = heap[c1];
            heap[c1] = temp;
            heapifyDown(c1);
        }
        return;
    }

    public:

    //Default constructor
    Heap(){
        heap = new CDA();//yeah idk about this lol
    }

    //Uses O(n) bottom up method to contrust a heap given the array k of size s
    Heap(keytype k[], int s);

    //Copy Constructor
    Heap(const Heap &src){
        this->heap = src.heap;
    }

    //Copy Assignment Operator
    Heap& operator=(const Heap &src){
        this->heap = src.heap;
        return *this;
    }

    //Destructor
    ~Heap(){
        heap.Clear();
    }

    //Returns the minimum key in the heap without modifiying the heap
    keytype peekKey(){
        if(heap.Length() == 0) return nullptr;
        return heap[0];
    } 

    //Removes the minimum key in the heap and returns the key
    keytype extractMin(){
        if(heap.Length == 0) return nullptr;
        heap[0] = heap[heap.Length() - 1];// I think this is incorrect. Need to replace with the smallest child value
        heap.DelEnd();
        heapifyDown(0);
    }

    //Inserts the key k into the heap
    void insert(keytype k){
        heap[heap.Length()] = k;
        heapifyUp(heap.Length()-1);//Might need to remove the -1 here
    }

    //Writes the keys stored in the array, starting at the root
    void printKey(){
        if(heap.Length() == 0) return;
        for(int i = 0 ; i < heap.Length; i++){
            cout << heap[i] << " ";
        }
        cout << endl;
    }

};