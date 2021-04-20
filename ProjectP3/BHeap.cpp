//template <typename keytype>

template <typename keytype>

class BHeap{

    private:

    /*
    This Node implementation allows us to just keep track of our list in the Nodes itself. Instead of having to use an external class.
    This is done by using the sibling pointer and setting it when we insert. This is also done by just using the child pointer
    to be the leftmost child so that we can have access to our nodes at that level. 
    */

    struct Node{
        keytype key;
        int degree;
        Node *child; //pointer to left most child
        Node *sibling; //pointer to right sibling in list
        Node *parent; //pointer to parent
    };

    //This initializes node with default values. Cleans up code down the line
    void initNode(Node* node, keytype key, int degree){
        node->key = key;
        node->degree = degree;
        node->child = nullptr;
        node->sibling = nullptr;
        node->parent = nullptr;
    }

    //This function links two BTrees of the same degree
    void linkBTrees(Node* p, Node* y){
        //p will be our parent of y
        y->parent = p;
        y->sibling = p->child;
        p->child = y;

        //increase the degree of p
        p->degree += 1;
    }

    //This finds the node with the min data in the root list and sets our minNode pointer to it. O(lgn) time
    void findMin(){
        if(head == nullptr){
            minNode = nullptr;
            return;
        }

        keytype min = head->key;
        Node* curr = head;

        while(curr != nullptr){
            if(curr->key <= min){
                min = curr->key;
                minNode =  curr;
            }
            curr = curr->sibling;
        }
    }

    //This function recursively copies a heap
    Node* copyHeap(Node* srcNode, Node* p){
        if(srcNode == nullptr) return nullptr;

        //Temp will hold the new node for the new heap
        Node* temp = new Node;
        initNode(temp, srcNode->key, srcNode->degree);

        //First recurse across to get each sibling in each level
        temp->sibling = copyHeap(srcNode->sibling, p);
        //Then go down a level to copy each nodes children
        temp->child = copyHeap(srcNode->child, temp);
        temp->parent = p;
        return temp;
    }

    //This function recursivley prints out each tree in a preorder traversal
    void printTree(Node* node){
        if(node == nullptr) return;
        cout << node->key << " ";
        printTree(node->child);
        printTree(node->sibling);
    }

    //Destructor helper function
    void destroyTree(Node* node){
        if(node == nullptr) return;
        destroyTree(node->child);
        destroyTree(node->sibling);
        delete node;
    }

    public:

    //This points to the leftmost root node in the binomial tree list. Left most to keep consistent with our node implementation
    //These are down here in public because the copy constructor needs to access the src.head
    Node* head;
    Node* minNode;
    keytype emptyKey;

    //Default constructor
    BHeap(){
        head = nullptr;
        minNode = nullptr;
    }

    //For this constructor the heap should be built using the array K containing s items of keytype. The heap should be constructed using repeated insertion.
    BHeap(keytype k[], int s){
        head = nullptr;
        for(int i=0; i < s; i++){
            insert(k[i]);
        }
    }

    //Copy Constructor
    BHeap(const BHeap &src){
        //Copies heap starting at root node and then sets our Min in this tree
        head = copyHeap(src.head, nullptr);
        findMin();
    }
        

    //Copy Assignment Operator
    BHeap& operator=(const BHeap &src){
        //Copies heap starting at root node and then sets our Min in this tree
        head = copyHeap(src.head, nullptr);
        findMin();
        return *this;
    }

    //Destructor
    ~BHeap(){
        //destroyTree(head);
    }

    //Getter and setter functions for our head node
    Node* getHead(){
        return head;
    }

    //We need this because our insert function cannot access the head of the BHeap we create in it
    void setHead(Node* head){
        this->head = head;
        return;
    }

    keytype getHeadKey(){
        return head->key;
    }

    //Returns the minimum key in the heap without modifiying the heap
    keytype peekKey(){
        return minNode->key;
    } 

    //Removes the minimum key in the heap and returns the key
    keytype extractMin(){
        if(head == nullptr){
            return emptyKey;
        }

        Node* curr = head;
        Node* prevMin = nullptr;
        Node* minP = nullptr;
        Node* prev = nullptr;

        keytype min = head->key;

        //We are using this instead of the findMin function because we have to keep track of some extra things for extractMin
        while(curr != nullptr){
            if(curr->key <= min){
                min = curr->key;
                prevMin = prev;
                minP = curr;
            }
            prev = curr;
            curr = curr->sibling;
        }

        //logic for deleting the node pointed to by minP. Is based off what is left of node
        //Case if min is in middle of root list
        if(prevMin != nullptr && minP->sibling != nullptr){
            prevMin->sibling = minP->sibling;
        }
        //Case if minP is far right of root list
        else if(prevMin != nullptr && minP->sibling == nullptr){
            prevMin->sibling = nullptr;
        }
        //Case if minP is head and has a right sibling
        else if(prevMin == nullptr && minP->sibling != nullptr){
            head = minP->sibling;
        }
        //Case if head node is the only tree in heap
        else if(prevMin == nullptr && minP->sibling == nullptr){
            head = nullptr;
        }

        //This checks if the minNode is the head of the list and has no children. Just return
        if(minP->child == nullptr){
            if(head != nullptr) findMin();//This is an edge case where findMin would not get called in merge so we have to call here
            return minP->key;
        }

        //This goes and removes minP from all parent references. Merge will take care of resetting these pointers
        Node* child = minP->child;
        while(child != nullptr){
            child->parent = nullptr;
            child = child->sibling;
        }

        //Here we reverse the children of minP to keep in logical order for when we merge them into the new heap
        Node* current = minP->child;
        Node* pre = nullptr;
        Node* sib = nullptr;
        while(current != nullptr){
            sib = current->sibling;
            current->sibling = pre;
            pre = current;
            current = sib;
        }
        minP->child = nullptr;

        //This is another edge case to where minP was the only node in root list
        if(head == nullptr){
            head = pre;
            findMin();//This is an edge case where findMin would not get called in merge so we have to call here
            return minP->key;
        }

        //Here we create a new heap and set its head to be the new minP's child
        BHeap h;
        h.setHead(pre);
        merge(h);

        return minP->key;
    }

    //Inserts the key k into the heap
    void insert(keytype k){
        //Checks if the heap is empty
        if(head == nullptr){
            Node* temp = new Node;
            initNode(temp, k, 0);
            head = temp;
            minNode = temp;
            return;
        }

        //Create new BHeap for our insert node
        BHeap h;
        //Create new node with default values and degree 0. Then set our new BHeap head to this node and merge with current BHeap
        Node* node = new Node;
        initNode(node, k, 0);
        h.setHead(node);
        merge(h);
    }

    //Merges the heap H2 into the current heap. Consumes H2
    //The goal is to first merge the trees in order by degree without combining trees with the same degree
    void merge(BHeap<keytype> &H2){
        //We use 3 currents because it allows us to keep track of previous and new nodes in list without losing them
        Node* curr1 = head;
        Node* curr2 = H2.getHead();
        Node* curr3 = nullptr;
        Node* tempNode = nullptr;

        /*
        *  This goes and compares the heads of the two nodes and decides which one is larger so we know where to start our in order merge
        *   It stores which is the smallest degree node into curr3 which is then stored in temp
        */
        if(curr1->degree <= curr2->degree){
            curr3 = curr1;
            curr1 = curr1->sibling;
        }
        else{
            curr3 = curr2;
            curr2 = curr2->sibling;
        }

        //This will be used down the line to comeback to our curr3 node in this position. Marks our starting node
        tempNode = curr3;

        //This then merges the two heaps without touching their degrees
        //curr3 is in the node opposite curr2. So this will join two trees in the node based off which degree is higher of curr1 or curr2. This goes down the entire list
        while(curr1 != nullptr && curr2 != nullptr){
            if(curr1->degree <= curr2->degree){
                curr3->sibling = curr1;
                curr1 = curr1->sibling;
            }
            else{
                curr3->sibling = curr2;
                curr2 = curr2->sibling;
            }

            //Move down the list
            curr3 = curr3->sibling;
        }

        //These two if statements cover the cases for if one heap has more trees than the other.
        //We just add the rest of the trees that our left without having to worry to compare.
        if(curr1 != nullptr){
            while(curr1 != nullptr){
                curr3->sibling = curr1;
                curr1 = curr1->sibling;
                curr3 = curr3->sibling;
            }
        }

        if(curr2 != nullptr){
            while(curr2 != nullptr){
                curr3->sibling = curr2;
                curr2 = curr2->sibling;
                curr3 = curr3->sibling;
            }
        }

        //The rest of the algorithm handles our trees with the same degree
        curr3 = tempNode;
        head = tempNode;
        Node* p = nullptr;
        Node* n = curr3->sibling;

        while(n != nullptr){
            //If two siblings dont have the same degree or there are 3 consecutive same degree roots we move on to the next sibling because that first one
            //will just be the root with that degree. It is impossible for there to be more than 3 of the same kind
            if((curr3->degree != n->degree) || (n->sibling != nullptr && curr3->degree == n->sibling->degree)){
                p = curr3;
                curr3 = n;
            }

            //Otherwise we repeatdly merge the binomial trees with matching degrees. Uses our linkBTree method
            else{
                //This keeps heap order correct by choosing smallest key to be the one in root list
                if(curr3->key <= n->key){
                    curr3->sibling = n->sibling;
                    //This sets our curr3 to be the parent of n because curr3 key is smaller
                    linkBTrees(curr3, n);
                }
                else{
                    //If this is other way around we will lose our temp pointer so we have to update it to be the new head of our heap
                    if(p == nullptr) tempNode = n;
                    //Otherwise we just make sure our sibling pointers dont get lost
                    else p->sibling = n;

                    //This sets our n to be the parent of curr3 and curr3 gets "eaten" by n so we update it
                    linkBTrees(n, curr3);
                    curr3 = n;
                }
            }
            n = curr3->sibling;
        }
        head = tempNode;

        //We can afford to do this this because this puts the function at most O(lgn + lgn) which is still O(lgn)
        findMin();
    }

    //Writes the keys stored in the heap, printing the smallest binomial tree first. When printing a
    //binomial tree, print the size of tree first and then use a modified preorder traversal of the tree.
    void printKey(){
        Node* curr = head;
        while(curr != nullptr){
            cout << "B" << curr->degree << endl;
            cout << curr->key << " ";
            printTree(curr->child);
            if(curr->sibling != nullptr) cout << endl << endl;
            else cout << endl;
            curr = curr->sibling;
        }
        return;
    }

};