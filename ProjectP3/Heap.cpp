#include "CDA.cpp"
template <typename keytype>
//Might need to move the include down here and change all the elmtype in CDA into keytype 

class Heap{

    private:

    CDA<keytype> heap;//I think this needs to be a pointer

    //Gets the parent of current node
    int parent(int child){
        if(child==0) return -1;
        else return (child - 1) / 2;
    }

    //Gets the left child of current node
    int left(int parent){
        int left = 2*parent + 1;
        if(left <= heap.Length()) return left;
        else return -1;
    }

    //Gets the right child of current node
    int right(int parent){
        int right = 2*parent + 2;
        if(right <= heap.Length()) return right;
        else return -1;
    }

    //Heapifys the heap upwards
    void heapifyUp(int x){
        //Checks if heap order is incorrect and makes swaps
        if(x > 0 && heap[parent(x)] > heap[x]){
            keytype temp = heap[x];
            heap[x] = heap[parent(x)];
            heap[parent(x)] = temp;
            heapifyUp(parent(x));
        }
        return;
    }

    //heapify downward
    void heapifyDown(int x){
        int l = left(x);
        int r = right(x);
        if(l==-1 || r==-1) return;
        int min = x;
        //Checking for the smallest element
        if(l < heap.Length() && heap[l] < heap[x]) min = l;
        if(r < heap.Length() && heap[r] < heap[min]) min = r;

        if(min != x){
            keytype temp = heap[x];
            heap[x] = heap[min];
            heap[min] = temp;
            heapifyDown(min);
        }
        return;
    }

    public:

    //Default constructor
    Heap(){
    }

    //Uses O(n) bottom up method to contrust a heap given the array k of size s
    Heap(keytype k[], int s){
        //Fills our CDA with the given array in O(n) time
        for(int i = 0; i < s; i++){
            heap.AddEnd(k[i]);
            //cout << heap[i] << " ";
        }
        //cout << endl;

        //This then heapifys our given unordered heap. This is also O(n)
        for(int i = (heap.Length()/2) - 1; i >= 0; i--){
            heapifyDown(i);
        }

        //Total run time is still O(n) because O(n+n) is still O(n)
    }

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
        if(heap.Length() == 0) return NULL;
        return heap[0];
    } 

    //Removes the minimum key in the heap and returns the key
    keytype extractMin(){
        if(heap.Length() == 0) return NULL;
        keytype k = heap[0];

        heap[0] = heap[heap.Length() - 1];// I think this is incorrect. Need to replace with the smallest child value
        heap.DelEnd();
        heapifyDown(0);
        return k;
    }

    //Inserts the key k into the heap
    void insert(keytype k){
        heap.AddEnd(k);
        heapifyUp(heap.Length()-1);
    }

    //Writes the keys stored in the array, starting at the root
    void printKey(){
        if(heap.Length() == 0) return;
        for(int i = 0 ; i < heap.Length(); i++){
            cout << heap[i] << " ";
        }
        cout << endl;
    }

};