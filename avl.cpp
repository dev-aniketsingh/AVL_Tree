#include<iostream>
#include "avl.h"

using namespace std;

int main() {
	AVLTree<int> tree;
	for(int i = 0; i < 100; i++) {
		tree.insert(i*3); //insert works
		tree.insert(i*7);
	}
	tree.deleteVal(3); //delete works
	tree.deleteVal(9);
	for(int i = 0; i < 100; i++) {
		tree.deleteVal(i*3);
	}
	tree.deleteVal(686);
	tree.print();
	cout << "------------------------------MIN METHOD---------------------------" << "\n";
	cout << tree.Min() << endl;
	cout << "------------------------------MAX METHOD---------------------------" << "\n";
	cout << tree.Max() << endl;
	cout << "------------------------------ValCheck METHOD----------------------" << "\n";
	if(tree.hasGot(10)) {
		cout << "Value is in the AVL tree \n";
	}
	else 
		cout << "Value not found \n";
	if(tree.hasGot(7)) {
		cout << "Value is in the AVL tree \n";
	}
	else 
		cout << "Value not found \n";
	cout << "------------------------------isEmpty() METHOD----------------------" << "\n";
	tree.empty();
	tree.print(); //This works for sure
	if(tree.isEmpty()) {
		cout << "Function works! \n";
	}
	cout <<"----------------------New values into the tree------------------------\n";
	for(int i = 0; i < 100; i++) {
		tree.insert(i*8);
		tree.insert(i*10);
	}
	cout << "------------------------------MIN METHOD---------------------------" << "\n";
	cout << tree.Min() << endl;
	cout << "------------------------------MAX METHOD---------------------------" << "\n";
	cout << tree.Max() << endl;
	cout << "------------------------------ValCheck METHOD----------------------" << "\n";
	if(tree.hasGot(8)) {
		cout << "Value is in the AVL tree \n";
	}
	else 
		cout << "Value not found \n";
	if(tree.hasGot(19)) {
		cout << "Value is in the AVL tree \n";
	}
	else 
		cout << "Value not found \n";

	return 0;
}