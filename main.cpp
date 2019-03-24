#include "BST.h"
#include<ctime>

using namespace std;

int main() {
	BST<int>* tree = new BST<int>();
	tree->Add(10);
	tree->Add(12);
	tree->Add(4);
	tree->Add(6);
	tree->Add(5);
	tree->Add(3);
	tree->Add(13);
	tree->Add(11);
	tree->Add(14);
	tree->Add(2);
	tree->Add(7);
	tree->printLRR();
	cout << endl;

	cout << "Min element: " <<(*tree->MinElem())->data << endl;
	cout << "Max element: " << (*tree->MaxElem())->data << endl;

	tree->Remove(12);

	cout << "Iteration print after deleting 12\n";
	for (auto x = tree->begin(); x != tree->end(); ++x)
		cout << (*x)->data << " ";
	cout << endl;

	cout << "Level print\n";
	tree->printQueue();

	cout << endl << "Lower bound 15: " << (*tree->lowerBound(15))->data << endl;
	cout << "Upper bound 1: " << (*tree->upperBound(1))->data << endl;

	cout << "Find element '3': " << (*tree->Find(3))->data << endl;

	cout << "Element before end(): " << (*--tree->end())->data << endl;

	tree->printStack();	
	cout << endl;

	BST<int>* tree1 = new BST<int>();
	tree1->Add(3);
	tree1->Add(5);
	tree1->Add(8);
	tree1->Add(15);
	tree1->Add(43);
	tree1->Add(18);
	tree1->Add(14);
	tree1->Add(69);

	cout << "Print tree1\n";
	tree1->printLRR();
	cout << endl << "Are tree1 & tree equal? " << tree->isEqual(tree1) << endl;
	
	cout << endl;
	cout << "Eratosphen algorithm\n";
	int n = 1000;
	int REPEAT = 100;
	vector<char> prime1;
	auto t1 = clock();
	for (int i = 0; i < sqrt(n); i++) {
		prime1 = vector<char>(n + 1, true);
		prime1[0] = prime1[1] = false;
		for (int i = 2; i <= n; ++i)
			if (prime1[i] && i * i <= n)
				for (int j = i*i; j <= n; j += i) prime1[j] = false;
	}
	auto t2 = clock();
	double sum = 0; for (int i = 2; i <= n; ++i) if (prime1[i]) sum += i;
	cout << "Time for vector: " << double((t2 - t1)) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;

	mySet<int> prime2;
	t1 = clock();
	prime2.erastofen(n);
	t2 = clock(); 
	cout << "Time for my set: " << double((t2 - t1)) * 1000.0 / CLOCKS_PER_SEC << " ms" << endl;

	system("pause");
}

/*
2 3 4 5 6 7 10 11 12 13 14
Min element: 2
Max element: 14
Iteration print after deleting 12
2 3 4 5 6 7 10 11 13 14
Level print
10 4 13 3 6 11 14 2 5 7
Lower bound 15: 14
Upper bound 1: 2
Find element '3': 3
Element before end(): 14
14 13 11 10 7 6 5 4 3 2
Print tree1
3 5 8 14 15 18 43 69
Are tree1 & tree equal? 0

Eratosphen algorithm
Time for vector: 28 ms
Time for my set: 10 ms
*/