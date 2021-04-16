class DllNode {
public:
    int value;
    DllNode *prev;
    DllNode *next;
};

class Dll {
private:
    DllNode *head;
    int length=0;
public:

    // create an empty list
    Dll(){
        head = new DllNode;
        head->prev = head;
        head->next = head;
        length = 0;
    }

    // create a deep copy of the src list
    Dll(const Dll &src){
        length = src.length;
        DllNode *current;
        DllNode *temp;
        head = new DllNode;
        head->prev = head;
        head->next = head;
        DllNode *otherCurrent = src.head->next;
        head->next = current;

        for(int i=0; i < length; i++){
            temp = new DllNode;
            temp->value = otherCurrent->value;
            temp->next = nullptr;
            temp->prev = current;
            if(i == length-1){
                temp->next = head;
                head->prev = current;
            }
            otherCurrent = otherCurrent->next;
            current = temp;
        }
    }

    // create a linked list containing the elements of the array
    Dll(const int arr[], int size){
        length = size;
        DllNode *current;
        DllNode *temp;
        head = new DllNode;
        head->prev = head;
        head->next = head;
        current = head;

        for(int i=0; i < size; i++){
            temp = new DllNode;
            temp->value = arr[i];
            temp->next = nullptr;
            temp->prev = current;
            if(i == size-1){
                temp->next = head;
                head->prev = current;
            }
            current = temp;
        }
    }

    // create a deep copy of the src list
    Dll &operator=(const Dll &src){
        length = src.length;
        DllNode *current;
        DllNode *temp;
        head = new DllNode;
        head->prev = head;
        head->next = head;
        DllNode *otherCurrent = src.head->next;
        head->next = current;

        for(int i=0; i < length; i++){
            temp = new DllNode;
            temp->value = otherCurrent->value;
            temp->next = nullptr;
            temp->prev = current;
            if(i == length-1){
                temp->next = head;
                head->prev = current;
            }
            otherCurrent = otherCurrent->next;
            current = temp;
        }
        return *this;
    }

    // free all memory
    ~Dll(){
        DllNode *current = head->prev;
        DllNode *temp;
        for(int i=0; i<length; i++){
            temp = current->prev;
            delete current;
            current = temp;
        }
    }

    // return if the list is empty in O(1)
    bool empty() const{
        return head->next == head;
    }

    // return how many items are in the list in O(1)
    int size() const{
        return length;
    }

    // return a reference to the value of the list at a rank/index
    int &at(int rank){
        if(rank < 0 || rank > length-1) return nullptr;

        DllNode* current = head->next;
        for(int i=0; i<rank; i++){
            current = current->next;
        }
        return current->value;
    }

    // insert a value at the rank/index
    void insert(int rank, int value){
        if( rank > length || rank < 0) return;

        //These next two are for checking if inserting at front or back to use constant time
        if(rank == 0 ){
            DllNode* current = head->next;
            DllNode *insert = new DllNode;
            insert->value = value;
            insert->prev = current->prev;
            insert->next = current;
            current->prev->next = insert;
            current->prev = insert;
            length++;
        }

        else if(rank == length){
            DllNode* current = head->prev;
            DllNode* insert = new DllNode;
            insert->value = value;
            insert->prev = current;
            insert->next = current->next;
            current->next->prev = insert;
            current->next = insert;
            length++;
        }

        else{
            DllNode* current = head->next;
            for(int i=0; i < rank; i++){
                current = current->next;
            }
            DllNode *insert = new DllNode;
            insert->value = value;
            insert->prev = current->prev;
            insert->next = current;
            current->prev->next = insert;
            current->prev = insert;
            length++;
        }
    }

    // remove the node at the rank/index and return its value
    int remove(int rank){
        int temp;

        if(rank < 0 || rank > length-1) return -1;;

        if(rank==0){
            DllNode* current = head->next;
            temp = current->value;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
            return temp;
        }

        else if(rank == length){
            DllNode* current = head->prev;
            temp = current->value;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
            return temp;
        }

        else{
            DllNode* current = head->next;
            for(int i=0; i<rank; i++){
                current = current->next;
            }
            temp = current->value;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            length--;
            return temp;
        }
    }

    // reset the list to an empty list
    void clear(){
        DllNode *current = head->prev;
        DllNode *temp;
        int tempint = length;
        for(int i=tempint; i > 0; i--){
            temp = current->prev;
            delete current;
            current = temp;
            length--;
        }
        head->prev = head;
        head->next = head;
    }

    // write the contents of the list to the ostream
    void display(ostream &os) const{
        DllNode* current = head->next;
        os << "[ ";
        for(int i=0; i<length; i++){
            os << current->value << " ";
            current = current->next;
        }
        os << "]";
    }
};

// write the contents of the list to the ostream
ostream &operator<<(ostream &os, const Dll &list){
    list.display(os);
    return os; 
}
