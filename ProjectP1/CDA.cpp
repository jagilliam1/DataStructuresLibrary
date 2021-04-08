#include <cstdlib>
using namespace std;
template <typename elmtype>

class CDA{
     private:
        int size;
        int capacity;
        int fIndex;
        int bIndex;
        bool reversed;
        bool sorted;

        //element for returning out of bound from [] operator
        elmtype OOB;

        //points to the array
        elmtype* array;

        //create new array and copy old array into new array. then manually delete old array (do not use destructor) and change array pointer
        void resize(int newCapacity){
            elmtype* tempA = new elmtype[newCapacity];
            
            if(!reversed){
                for(int i=0, j=fIndex; i<size; i++, j=(j+1) % capacity){
                    tempA[i] = array[j];
                }
            }
            else{
                for(int i=0, j=fIndex; i<size; i++, j=(j-1) % capacity){
                    tempA[i] = array[j];
                }
            }
            delete [] array;
            array = tempA;
            tempA = nullptr;
            capacity = newCapacity;
            fIndex=0;
            bIndex = size-1;
        }

        void merge(elmtype *tempArray, int l, int m, int r){

            int mergeSize = r - l + 1;
            int mergePosition = 0;
            int leftPosition = l;
            int rightPosition = m + 1;

            elmtype *mergeArray = new elmtype[mergeSize];

            while (leftPosition <= m && rightPosition <= r) {
                if (tempArray[leftPosition] < tempArray[rightPosition]){
                    mergeArray[mergePosition] = tempArray[leftPosition];
                    leftPosition++;
                }
                else {
                    mergeArray[mergePosition] = tempArray[rightPosition];
                    rightPosition++;
                }
                mergePosition++;
            }

            while (leftPosition <= m) {
                mergeArray[mergePosition] = tempArray[leftPosition];
                mergePosition++;
                leftPosition++;
            }

            while (rightPosition <= r) {
                mergeArray[mergePosition] = tempArray[rightPosition];
                mergePosition++;
                rightPosition++;
            }

            for (mergePosition = 0; mergePosition < mergeSize; mergePosition++) {
                tempArray[mergePosition + l] = mergeArray[mergePosition];
            }
        }

        void mergeSort(elmtype *tempArray, int l, int r){
            if (l < r) {
                int m = (l + (r - 1)) / 2;
                mergeSort(tempArray, l, m);
                mergeSort(tempArray, m + 1, r);
                merge(tempArray, l, m, r);
            }
        }

    public:

        CDA(){
            capacity = 1;
            size = 0;
            fIndex = 0;
            bIndex = 0;
            reversed = false;
            sorted = false;
            array = new elmtype[capacity];
        }

        CDA(int s){
            capacity = s;
            size = s;
            fIndex = 0;
            bIndex = s-1;
            reversed = false;
            sorted = false;
            array = new elmtype[capacity];
        }

        CDA(const CDA &src){
            this->size = src.size;
            this->capacity = src.capacity;
            this->fIndex = src.fIndex;
            this->bIndex = src.bIndex;
            this->reversed = src.reversed;
            this->sorted = src.sorted;
            this->array = new elmtype[capacity];
            if(!reversed){
                for (int i = 0, j = fIndex; i < size; i++, j = (j + 1) % capacity) {
                    this->array[j] = src.array[j];
                }
            }
            if(reversed){
                for (int i = 0, j = fIndex; i < size; i++, j = (j - 1) % capacity) {
                    this->array[j] = src.array[j];
                }
            }
        }

        CDA& operator=(const CDA& src){
            this->size = src.size;
            this->capacity = src.capacity;
            this->fIndex = src.fIndex;
            this->bIndex = src.bIndex;
            this->reversed = src.reversed;
            this->sorted = src.sorted;
            this->array = new elmtype[capacity];
            if(!reversed){
                for (int i = 0, j = fIndex; i < size; i++, j = (j + 1) % capacity) {
                    this->array[j] = src.array[j];
                }
            }
            if(reversed){
                for (int i = 0, j = fIndex; i < size; i++, j = (j - 1) % capacity) {
                    this->array[j] = src.array[j];
                }
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
            if(!reversed) bIndex = (bIndex+1) % capacity;
            else bIndex = (bIndex-1) % capacity;//reverse
            array[bIndex] = v;
            size++;
        }

        void AddFront(elmtype v){
            if(size >= capacity) resize(capacity * 2);

            if(!reversed){
                if(fIndex==0) fIndex = capacity - 1;
                else fIndex--;
            }
            else{
                if(fIndex==capacity-1) fIndex = 0;
                else fIndex++;
            }
            array[fIndex] = v;
            size++;
        }

        void DelEnd(){
            if(size == 0) return;
            if(size < (capacity / 4)) resize(capacity/2);
            size--;
            if(!reversed) bIndex = (bIndex- 1) % capacity;
            else bIndex = (bIndex + 1) % capacity;//reverse
        }

        void DelFront(){
            if(size == 0) return;
            if(size < (capacity)/4) resize(capacity/2);
            size--;
            if(!reversed) fIndex = (fIndex+1) % capacity;
            else fIndex = (fIndex-1) % capacity;//reverse
        }

        int Length(){
            return size;
        }

        int Capacity(){
            return capacity;
        }

        //These are temp debug helper functions
        int front(){
            return fIndex;
        }
        int back(){
            return bIndex;
        }

        void Clear(){
            delete [] array;
            capacity = 4;
            size = 0;
            fIndex = 0;
            bIndex = 0;
            sorted = false;
            reversed = false;
            array = new elmtype[capacity];
        }

        void Reverse(){
            if(!reversed){
                reversed = true;
                int temp;
                temp = fIndex;
                fIndex = bIndex;
                bIndex = temp;
            }
            else{
                reversed = false;
                int temp;
                temp = fIndex;
                fIndex = bIndex;
                bIndex = temp;
            }
        }

        elmtype quickSelect(elmtype arr[], int arrSize, int k){
            int pivot = arr[rand() % arrSize];
            int l=0;
            int e=0;
            int g=0;
            elmtype L[arrSize], E[arrSize], G[arrSize];

            for(int i=0; i < arrSize; i++){
                if(arr[i] < pivot){
                    L[l] = arr[i];
                    l++;
                }
                else if(arr[i]==pivot){
                    E[e] = arr[i];
                    e++;
                }
                else{
                    G[g] = arr[i];
                    g++;
                }
            }

            if(k <= l) return quickSelect(L, l, k);
            else if(k <= l + e) return pivot;
            else return quickSelect(G, g, k-l-e);
        }

        elmtype Select(int k){
            //Change to normal direction and adjust to index 0
            if(reversed){
                resize(capacity);
                Reverse();
                elmtype c = quickSelect(array, size, k);
                Reverse();
                return c;
            }

            resize(capacity);
            return quickSelect(array, size, k);
        }

        void Sort(){
            //Shifts everything to start at true index 0 and sets to normal direction. Helps to simplify algo. Still nlgn time.
            if(reversed){
                reversed = false;
                int temp;
                temp = fIndex;
                fIndex = bIndex;
                bIndex = temp;
            }
            resize(capacity);
            elmtype *tempArray = new elmtype[size];
            tempArray = array;
            mergeSort(tempArray, 0, bIndex);
            array = tempArray;
            sorted = true;
        }

        int Search(elmtype e){
            if(!reversed){
                for(int i=0, j=fIndex; i<size; i++, j=(j+1) % capacity){
                    if(array[j]==e) return i;
                }
            }
            else{
                for(int i=0, j=fIndex; i<size; i++, j=(j-1) % capacity){
                    if(array[j]==e) return i;
                }
            }
            return -1;
        }

        int binarySearch(int left, int right, elmtype& e){
            int mid = left + ((right - left) / 2);
            if(left==mid && array[mid]!=e) return ~(mid+1);
            if(array[mid]==e) return mid;
            else if(array[mid] > e) return binarySearch(left, mid-1, e);
            return binarySearch(mid+1, right, e);
        }

        int BinSearch(elmtype e){
                return binarySearch(fIndex, bIndex, e);
        }
};