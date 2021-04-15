#include <cstdlib>
template <typename elmtype>

class CDA{
     private:
        int size;
        int capacity;
        int fIndex;
        int bIndex;

        //element for returning out of bound from [] operator
        elmtype OOB;

        //points to the array
        elmtype* array;

        //create new array and copy old array into new array. then manually delete old array (do not use destructor) and change array pointer
        void resize(int newCapacity){
            elmtype* tempA = new elmtype[newCapacity];
            for(int i=0, j=fIndex; i<size; i++, j=(j+1) % capacity){
                tempA[i] = array[j];
            }
            delete [] array;
            array = tempA;
            tempA = nullptr;
            capacity = newCapacity;
            fIndex=0;
            bIndex = size-1;
        }

    public:

        CDA(){
            capacity = 1;
            size = 0;
            fIndex = 0;
            bIndex = 0;
            array = new elmtype[capacity];
        }

        CDA(int s){
            capacity = s;
            size = s;
            fIndex = 0;
            bIndex = s-1;
            array = new elmtype[capacity];
        }

        CDA(const CDA &src){
            this->size = src.size;
            this->capacity = src.capacity;
            this->fIndex = src.fIndex;
            this->bIndex = src.bIndex;
            this->array = new elmtype[capacity];
            for (int i = 0, j = fIndex; i < size; i++, j = (j + 1) % capacity) {
                this->array[j] = src.array[j];
            }
        }

        CDA& operator=(const CDA& src){
            this->size = src.size;
            this->capacity = src.capacity;
            this->fIndex = src.fIndex;
            this->bIndex = src.bIndex;
            this->array = new elmtype[capacity];
            for (int i = 0, j = fIndex; i < size; i++, j = (j + 1) % capacity) {
                this->array[j] = src.array[j];
            }
            return* this;
        }

        ~CDA(){
            delete [] array;
            array = nullptr;
        }

        elmtype& operator[](int i){
            if(i >= size){
                cout << "Out of bounds" << endl;
                return OOB;
            }
            if(!reversed) return array[(fIndex + i) % capacity];
            return array[(fIndex - i + capacity) % capacity];
        }

        void AddEnd(elmtype v){
            if(size >= capacity) resize(capacity * 2);
            bIndex = (bIndex+1) % capacity;
            array[bIndex] = v;
            size++;
        }

        void AddFront(elmtype v){
            if(size >= capacity) resize(capacity * 2);
            if(fIndex==0) fIndex = capacity - 1;
            else fIndex--;
            array[fIndex] = v;
            size++;
        }

        void DelEnd(){
            if(size == 0) return;
            if(size < (capacity / 4)) resize(capacity/2);
            size--;
            bIndex = (bIndex- 1) % capacity;
        }

        void DelFront(){
            if(size == 0) return;
            if(size < (capacity)/4) resize(capacity/2);
            size--;
            fIndex = (fIndex+1) % capacity;
        }

        int Length(){
            return size;
        }

        int Capacity(){
            return capacity;
        }

        void Clear(){
            delete [] array;
            capacity = 4;
            size = 0;
            fIndex = 0;
            bIndex = 0;
            array = new elmtype[capacity];
        }
};