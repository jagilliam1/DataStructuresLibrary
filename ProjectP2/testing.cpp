#include <iostream>
using namespace std;
#include "RBTree.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " PASSED " << endl;
	}else if(numOfErrors < 100){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else if (numOfErrors < 1000){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else if (numOfErrors < 10000){
		cout << errors << " caused " << numOfErrors << " of errors Add+1" << endl;
	}else{
		cout << errors << " caused " << numOfErrors << " of errors" << endl;
	}
}

int main(){


    int rankError = 0;
	int selectError = 0;
	int searchError = 0;
	int treeSize = 100200;
    //int treeSize = 100;
    int c = 0;
    RBTree<int,int> X;
	for (int i=treeSize;i>=0;i--){
        X.insert(i,treeSize-i);
        //cout << X.size() << endl;
        //cout << i << endl;
        //c++;
    }
    //cout << c << endl;
    //cout << X.size() << endl;
	for (int i=1;i<treeSize;i++) {
		if(X.rank(i) != i+1) rankError++; 
		if(X.select(i) != i-1) selectError++;
		if(*(X.search(i)) != treeSize-i) searchError++; 
	}
	printErrors("Rank",rankError);
	printErrors("Select",selectError);
	printErrors("Search",searchError);
	cout << "Finished without failing" << endl << endl;



	/*string K[10] = {"A","B","C","D","E","F","G","H","I","K"};
	int V[10] = {10,9,8,7,6,5,4,3,2,1};
	
	RBTree<string,int> T1;

    T1.insert("A", 10);
    T1.insert("B", 9);
    T1.insert("C", 8);
    T1.insert("D", 7);
    T1.insert("E", 6);
    T1.insert("F", 5);
    T1.insert("G", 4);
    T1.insert("H", 3);
    T1.insert("I", 2);
    T1.insert("K", 1);*/

    //T1.remove("D");
    //T1.remove("E");
    //T1.remove("H");

    //cout << T1.remove("J") << endl;
    //T1.remove("A");
    //T1.remove("B");
    //T1.remove("C");
    //T1.remove("D");
    //T1.remove("E");
    //T1.remove("F");
    //T1.remove("G");
    //T1.remove("F");
    //T1.remove("B");
    //T1.remove("H");
    //T1.remove("I");
    //T1.remove("K");

    //cout << T1.select(3) << endl;
	//Should output C 

    //RBTree<string,int> T2;

    //T2 = T1;

    //T1.remove("A");
    //T2.remove("B");
    //T2.insert("B", 9);

    //cout << T1.rank("I") << endl;
    //T1.inorder();
    //Should output	A B C D E F G H I K\n

    //T2.inorder();
    //Should output	A B C D E F G H I K\n

    //T1.preorder();
    //Should output "D B A C F E H G I K\n"
    //T1.postorder();
	//cout << "end" << endl;
	
	
	return 0;
}