template <typename keytype, typename valuetype>

class RBTree{
    private:
        struct Node{
            Node* left;
            Node* right;
            Node* parent;
            char color;
            int weight;
            keytype key;
            valuetype v;

            Node(){
                right = nullptr;
                left = nullptr;
                parent = nullptr;
            }
            
        };

        Node* root;
        Node* TNULL;
        keytype nullkey;

    //Destructor Helper Function
    Node* clearTree(Node* x){
        if(x==TNULL) return nullptr;
        else{
            clearTree(x->left);
            clearTree(x->right);
            delete x;
        }
        return nullptr;
    }

    //Actual Traversal Functions
    void printPreOrder(Node* node){
        if(node!=TNULL){
            cout << node->key << " ";
            printPreOrder(node->left);
            printPreOrder(node->right);
        }
    }

    void printInOrder(Node* node){
        if(node!=TNULL){
            printInOrder(node->left);
            cout << node->key << " ";
            printInOrder(node->right);
        }
    }

    void printPostOrder(Node* node){
        if(node!=TNULL){
            printPostOrder(node->left);
            printPostOrder(node->right);
            cout << node->key << " ";
        }
    }

    //Search funciton to return Node type.
    Node* findNode(Node* node, keytype k){
        if(node == TNULL || node->key == k) return node;
        if(k < node->key) return findNode(node->left, k);
        return findNode(node->right, k);
    }

    //Returns pointer to the left most node from a given node.
    Node* findMin(Node* node){
        while(node->left != TNULL){
            node = node->left;
        }
        return node;
    }

    //Returns pointer to the right most node from a given node.
    Node* findMax(Node* node){
        while(node->right != TNULL){
            node = node->right;
        }
        return node;
    }

    //Helper function to find the predecessor in the delete function
    Node* deletePredHelper(Node* n){
        if(n->left != TNULL){
            Node* node = n->left;

            //Corrects the weights while finding the pred
            while(node->right != TNULL){
                node->weight--;
                node = node->right;
            }
            node->weight = n->weight;

            return node;
        } 

        //This finds the last node that we took a right turn to get to and returns that as pred
        Node* p = n->parent;
        while(p!=TNULL && n==p->left){
            n=p;
            p=p->parent;
        }
        return p;
    }

    //Right rotation function
    void rotateRight(Node* x){
        Node* y = x->left;
        x->left = y->right;

        if(y->right != TNULL){
            y->right->parent = x;
        }

        y->parent = x->parent;
        if(x->parent == nullptr){
            this->root = y;
        }
        else if(x == x->parent->right){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
        y->weight = x->weight;
        x->weight = x->left->weight + x->right->weight + 1;
    }

    //Left rotation function
    void rotateLeft(Node* x){
        Node* y = x->right;
        x->right = y->left;

        if(y->left != TNULL){
            y->left->parent = x;
        }

        y->parent = x->parent;
        if(x->parent == nullptr){
            this->root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        y->weight = x->weight;
        x->weight = x->left->weight + x->right->weight + 1;
    }

    //fix violation function for insert
    void insertFixUp(Node* z){

        //Uncle
        Node* y;
        
        while(z->parent->color == 'r'){

            //If z->parent is left child of z->parent->parent
            if(z->parent == z->parent->parent->left){
                //z's uncle
                y = z->parent->parent->right;

                //Case 1:
                if(y->color == 'r'){
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }

                else{
                    //Case 2:
                    if(z==z->parent->right){
                        z = z->parent;
                        rotateLeft(z);
                    }

                    //Case 3:
                    z->parent->color = 'b';
                    z->parent->parent->color = 'r';
                    rotateRight(z->parent->parent);
                }
            }

            else{
                //z's uncle
                y = z->parent->parent->left;

                //Case 1:
                if(y->color == 'r'){
                    z->parent->color = 'b';
                    y->color = 'b';
                    z->parent->parent->color = 'r';
                    z = z->parent->parent;
                }

                else{
                    //Case 2:
                    if(z==z->parent->left){
                        z = z->parent;
                        rotateRight(z);
                    }

                    //Case 3:
                    z->parent->color = 'b';
                    z->parent->parent->color = 'r';
                    rotateLeft(z->parent->parent);
                }
            }
            if(z==root) break;
        }
        root->color = 'b';
    }

    //Fix violation function for delete
    void deleteFixUp(Node* x){
        //Sibling of x
        Node* w;

        while(x != root && x->color == 'b'){
            if(x == x->parent->left){

                w = x->parent->right;

                //Case 1:
                if(w->color == 'r'){
                    w->color = 'b';
                    x->parent->color = 'r';
                    rotateLeft(x->parent);
                    w = x->parent->right;
                }

                //Case 2:
                if(w->left->color == 'b' && w->right->color == 'b'){
                    w->color = 'r';
                    x = x->parent;
                }

                //Case 3:
                else{
                    if(w->right->color == 'b'){
                        w->left->color = 'b';
                        w->color = 'r';
                        rotateRight(w);
                        w = x->parent->right;
                    }
                    
                    //Case 4:
                    w->color = x->parent->color;
                    x->parent->color = 'b';
                    w->right->color = 'b';
                    rotateLeft(x->parent);
                    x = root;
                }
            }

            else{

                w = x->parent->left;

                //Case 1:
                if(w->color == 'r'){
                    w->color = 'b';
                    x->parent->color = 'r';
                    rotateRight(x->parent);
                    w = x->parent->left;
                }

                //Case 2:
                if(w->right->color == 'b' && w->left->color == 'b'){
                    w->color = 'r';
                    x = x->parent;
                }

                //Case 3:
                else{
                    if(w->left->color == 'b'){
                        w->right->color = 'b';
                        w->color = 'r';
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    
                    //Case 4:
                    w->color = x->parent->color;
                    x->parent->color = 'b';
                    w->left->color = 'b';
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = 'b';
    }

    void transplant(Node* u, Node* v){
        if(u->parent == nullptr){
            this->root = v;
        }
        else if(u == u->parent->left){
            u->parent->left = v;
        }
        else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    //Function to check if a node exist
    bool checkNode(keytype k){
        Node* current = root;

        while(current != TNULL){
            if(current->key == k) return true;
            if(k > current->key) current = current->right;
            else if(k < current->key) current = current->left;
        }

        return false;
    }

    //copyInsert helper function
    Node* createNode(keytype k, valuetype v, char c){
        Node* node = new Node;
        node->color = c;
        node->weight = 1;
        node->key = k;
        node->v = v;
        node->left = this->TNULL;
        node->right = this->TNULL;

        return node;
    }

    //Copy Constructor helper function
    //Using newTNULL and oldTNULL to seperate the two trees TNULL pointers.
    Node* copyInsert(Node* node, Node* srcNode, Node* newTNULL, Node* oldTNULL){

        if(srcNode == oldTNULL) return newTNULL;

        node = createNode(srcNode->key, srcNode->v, srcNode->color);
        node->weight = srcNode->weight;

        node->left = copyInsert(node->left, srcNode->left, newTNULL, oldTNULL);
        if(node->left != newTNULL) node->left->parent = node;

        node->right = copyInsert(node->right, srcNode->right, newTNULL, oldTNULL);
        if(node->right != newTNULL) node->right->parent = node;

        return node;
    }

    //Helper function for printk
    void printkHelper(Node* node, int k, int& i){
        if(node!=TNULL && i < k){
            printkHelper(node->left, k, i);
            //Checks i before and after to make sure we dont print or call any extra nodes
            if(i >= k) return;
            cout << node->key << " ";
            i++;
            if(i >= k) return;
            printkHelper(node->right, k, i);
        }
    }

    int rankHelper(keytype k, Node* node){
        int r = 1;
        while(node != TNULL && node != nullptr){
            //We dont count our rank if we are less than curent nodes key
            if(k < node->key) node = node->left;
            //Here we count our rank because our node is larger than all the nodes to the left of it
            else if(k > node->key){
                r += 1 + node->left->weight;
                node = node->right;
            }
            //Case if this is the node
            else{
                return r + node->left->weight;
            }
        }
        return 0; //tree is empty
    }

    keytype selectHelper(int i, Node* x){
        //Checks to make sure we arnt trying to look outside the tree
        if(i <= root->weight){
            int r = x->left->weight + 1;
            if(i == r) return x->key; //The rank given is the x
            else if(i < r) return selectHelper(i, x->left); //rank is to the left of x
            else return selectHelper(i-r, x->right); //rank is to the right of x
        }
        else return nullkey;
    }

    public:
    
    //Default Constructor
    RBTree(){
        TNULL = new Node;
        TNULL->color = 'b';
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        TNULL->parent = nullptr;
        TNULL->weight = 0;
        root = TNULL;
    }

    //Overloaded Constructor
    RBTree(keytype k[], valuetype V[], int s){
        TNULL = new Node;
        TNULL->color = 'b';
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        TNULL->parent = nullptr;
        TNULL->weight = 0;
        root = TNULL;
        for(int i = 0; i < s; i++){
            insert(k[i], V[i]);
        }
    }

    //Copy Constructor
    RBTree(const RBTree &src){
        this->TNULL = new Node;
        this->TNULL->color = 'b';
        this->TNULL->left = nullptr;
        this->TNULL->right = nullptr;
        this->TNULL->parent = nullptr;
        this->TNULL->weight = 0;
        this->root = copyInsert(root, src.root, this->TNULL, src.TNULL);
    }

    //Copy Assignment Operator
    RBTree& operator=(const RBTree &src){
        this->TNULL = new Node;
        this->TNULL->color = 'b';
        this->TNULL->left = nullptr;
        this->TNULL->right = nullptr;
        this->TNULL->parent = nullptr;
        this->TNULL->weight = 0;
        this->root = copyInsert(root, src.root, this->TNULL, src.TNULL);
        return *this;
    }

    ~RBTree(){
        root = clearTree(root);
    }

    valuetype* search(keytype k){
        Node* n = findNode(root, k);
        return &n->v;
    }

    keytype* successor(keytype k){
        Node* p = nullptr;
        Node* n = root;
        bool leftTaken = false;//Used for edge case if node we found is the absolute maximum value in the tree

        if(root == TNULL || root == nullptr) return nullptr;

        while(n && n->key != k){
            //Keep going down right until we find the node
            if(k > n->key) n = n->right;
            else{
                p = n;
                n = n->left;
                leftTaken = true;
            }
        }

        //This checks if the node we found is the maximum value in the tree
        if(n->left == TNULL && n->right == TNULL && leftTaken == false) return nullptr;

        //Once we find node check if it has right subtree. If not we already have last left edge stored in p from while loop above
        if(n && n->right != TNULL) p = findMin(n->right);
        return &p->key;
    }

    keytype* predecessor(keytype k){
        Node* p = nullptr;
        Node* n = root;
        bool rightTaken = false;//Used for edge case if node we found is the absolute minimum value in the tree

        if(root == TNULL || root == nullptr) return nullptr;

        while(n && n->key != k){
            //Keep going down left until we find the node
            if(k < n->key) n = n->left;
            else{
                p = n;
                n = n->right;
                rightTaken = true;
            }
        }

        //This checks if the node we found is the minimum value in the tree
        if(n->left == TNULL && n->right == TNULL && rightTaken == false) return nullptr;

        //Once we find node check if it has left subtree. If not we already have last right edge stored in p from while loop above
        if(n && n->left != TNULL) p = findMax(n->left);
        return &p->key;
    }

    void insert(keytype k, valuetype v){
        Node* z = new Node;
        z->parent = nullptr;
        z->key = k;
        z->v = v;
        z->left = TNULL;
        z->right = TNULL;
        z->color = 'r';
        z->weight = 1;

        //Normal Binary Search Tree Insert here
        Node* x = this->root;
        Node* y = nullptr;

        while(x!=TNULL){
            y = x;
            x->weight++;
            if(z->key < x->key){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }

        //Below handles updating our pointers once we have found where to insert our node

        z->parent = y;
        //Checks if node we insert is the root node
        if(y==nullptr){
            this->root = z;
        }
        
        //Assigns new node to either be left or right child of parent depending on if its less than or greater than
        else if(z->key < y->key) {
            y->left = z;
        }

        else{
            y->right = z;
        }

        //Colors root black
        if(z->parent == nullptr){
            z->color = 'b';
            return;
        }

        //Edge case. If this is case we don't need to call fixup
        if(z->parent->parent == nullptr) return;

        //Fixup Tree
        insertFixUp(z);
    }

    int remove(keytype k){
        //Check if node to remove exist. O(lgn)
        bool check = checkNode(k);
        if(check == false) return 0;
        
        Node* z = findNode(root, k);//Node to be removed from the tree. O(lgn)
        Node* y = z;//This is either the node to remove from the tree or node to move around the tree. It depends on which case
        Node* x;//Node to be moved into y's position in the tree
        char yOriginal = y->color;//We store this because y can be removed around thus the color could change

        //Handle all the node weights here
        Node* t = z;
        while(t!=nullptr && t != TNULL){
            t->weight--;
            t = t->parent;
        }

        //Case if node only has one child on its right
        if(z->left == TNULL){
            x = z->right;
            transplant(z, z->right);
        }

        //Case if node only has one child on its left
        else if(z->right == TNULL){
            x = z->left;
            transplant(z, z->left);
        }

        //Case if the node has two children
        else{
            //State is swapped
            y = deletePredHelper(z);//If this case happens y will now be set as the pred and will move into z's positon in the tree
            yOriginal = y->color;
            x = y->left;

            if(y->parent == z) x->parent = y;

            else{
                transplant(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }

            transplant(z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }

        delete z;
        //We call this because if y is black by moving it we could have caused some Red-Black violations in the tree
        if(yOriginal == 'b'){
            deleteFixUp(x);
        }

        return 1;
    }

    int rank(keytype k){
        return rankHelper(k, root);
    }

    keytype select(int pos){
        return selectHelper(pos, root);
    } 

    int size(){
        return this->root->weight;
    }

    void preorder(){
        if(root == nullptr || root == TNULL) return;
        printPreOrder(root);
        cout << endl;
    }

    void inorder(){
        if(root == nullptr || root == TNULL) return;
        printInOrder(root);
        cout << endl;
    }

    void postorder(){
        if(root == nullptr || root == TNULL) return;
        printPostOrder(root);
        cout << endl;
    }

    void printk(int k){
        if(root == nullptr || root == TNULL) return;
        int i = 0;
        printkHelper(root, k, i);
        cout << endl;
    }
};