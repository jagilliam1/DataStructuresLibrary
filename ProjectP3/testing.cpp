#include <iostream>
#include <list>
using namespace std;
//#include "Heap.cpp"
#include "BHeap.cpp"

void foo(BHeap<string> H){
	H.printKey();
}

int main(){
	string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};
	
	/*Heap<int> T1, T2(B,10);
	
	T2.printKey();
	//Should output  1 2 4 3 6 5 8 10 7 9
	
	for(int i=0; i<10; i++) T1.insert(B[i]);
	
	T1.printKey();
	// Should output 1 2 5 4 3 9 6 10 7 8
	
	cout << T2.peekKey() << endl;
	//Should output 1
	
	cout << T1.extractMin() << endl;
	//Should output 1
	
	T1.printKey();
	//Should output 2 3 5 4 8 9 6 10 7
	*/

	int X[10000];
	for(int i=0; i < 10000; i++){
		X[i] = i;
	}

	BHeap<int> Y(X,10000);
	//cout << Y.extractMin() << endl;
	//cout << Y.extractMin() << endl;
	//cout << Y.extractMin() << endl;

	for(int i=0; i < 10000; i++){
		//cout << Y.extractMin() << endl;
	}

	//lets also try copy constructor and also change destructor

	BHeap<string> T(A,10), H;

	foo(T);

	//H = T;
	//T.extractMin();
	//H.insert("L");

	//T.printKey();
	//H.printKey();
			
	return 0;
}