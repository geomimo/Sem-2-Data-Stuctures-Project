// Domes2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "BinTree.h"
#include "BinTreeNode.h"
#include "Chain.h"
#include "chainnode.h"
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;
int menu();

int main()
{	
	int key, d = 0,answer;//ΕΙΣΑΓΩΓΗ ΜΕΤΑΒΛΗΤΩΝ.
	BinTree<int> Tree;
	float c, b;
	cout << "Give parameter c>1.\n";
	cin >> c;
	cout << "Give parameter b>0.\n";
	cin >> b;
	answer = menu();//ΜΕΝΟΥ ΕΠΙΛΟΓΩΝ.
	int i = 0;
	while (answer != 6) {//ΜΕΧΡΙ ΤΗΝ ΕΠΙΛΟΓΗ EXIT
		key = 0;
		int deleted;
		switch (answer)
		{
			case(1):
			{	
				BinTreeNode<int> checked;
				do {
					cout << "Give key to insert.\n";
					cin >> key;
					if (Tree.Search(key, &checked)) {
						cout << "The key " << key << " is already in Tree. Please give another key." << endl;
					}
				} while (Tree.Search(key, &checked));
				Chain<int> *path = new Chain<int>();
				Tree.Insert(key, *path);//ΕΙΣΑΓΩΓΗ ΝΕΟΥ ΚΟΜΒΟΥ ΚΑΙ ΕΠΙΣΤΡΟΦΗ ΜΟΝΟΠΑΤΙΟΥ ΑΠΟ ΤΗ ΡΙΖΑ ΜΕΧΡΙ ΤΟΝ ΚΟΜΒΟ ΑΥΤΟΝ.
				cout << "Key has been inserted successfully.\n";
				if (Tree.Depth(key) > ceil(c*log2(Tree.Count(Tree.Root()->data) + 1 + d))) {//ΕΛΕΓΧΟΣ ΑΝΙΣΟΡΡΟΠΟΙΑΣ
					BinTreeNode<int> *node = new BinTreeNode<int>();
					ChainIterator<int> *iterator = new ChainIterator<int>;
					int *checkKey = iterator->Initialize(*path);
					while (checkKey && Tree.Search(*checkKey, node)) {//ΕΥΡΕΣΗ ΚΟΜΒΟΥ ΟΠΟΥ ΘΑ ΓΙΝΕΙ Η ΑΝΑΚΑΤΑΣΕΥΗ
						if (Tree.Height(node) <= ceil(c*log2(Tree.Count(node->data) + 1))) {
							checkKey = iterator->Next();
						}
						else {
							break;
						}
					}
					if (!checkKey) {
						node = Tree.Root();
					}
					cout << "REBUILD AT NODE: " << node->data << endl;
					Tree.Rebuild(node); //ΑΝΑΚΑΤΑΣΚΕΥΗ ΥΠΟΔΕΝΤΡΟΥ
				}
				break;
			}
			case(2):
			{
				cout << "Give key to delete.\n";
				cin >> key;
				if (Tree.Root() && Tree.Count(Tree.Root()->data) > 0) {//ΔΙΑΓΡΑΦΗ ΚΟΜΒΟΥ ΜΕ ΚΛΕΙΔΙ key ΑΝ ΥΠΑΡΧΕΙ. 
					Tree.Delete(key, deleted);
					cout << "Key " << deleted << " has been deleted successfully.\n";
					d++;
				}
				else {
					cout << "There is no key to delete.\n";
				}
				if (Tree.Root() && d >= (Tree.Count(Tree.Root()->data) + 1)*(pow(2.0, b / c) - 1)) {// ΕΛΕΓΧΟΣ ΓΙΑ ΠΛΗΡΗ
					Tree.Rebuild(Tree.Root());														// ΑΝΑΚΑΤΑΣΚΕΥΗ
					cout << "FULL REBUILD." << endl;
					d = 0;
				}
				break;
			}
			case(3):
			{
				if (Tree.Count(Tree.Root()->data) != 0) {
					cout << "InOrder: ";
					Tree.InOrder(Tree.Root());
					cout << endl;
				}
				else {
					cout << "Empty Tree.\n";
				}
				break;
			}
			case(4):
			{	
				if (Tree.Count(Tree.Root()->data) != 0) {
					cout << "PostOrder: ";
					Tree.PostOrder(Tree.Root());
					cout << endl;
				}
				else {
					cout << "Empty Tree.\n";
				}
				break;
			}
			case(5):
			{
				if (Tree.Count(Tree.Root()->data) != 0) {
					cout << "PreOrder: ";
					Tree.PreOrder(Tree.Root());
					cout << endl;
				}
				else {
					cout << "Empty Tree.\n";
				}
				break;
			}
			default:
				cout << "Wrong input. Please type a number from 1 to 6." << endl;
				break;
		}
		answer = menu();
	}
	cout << "Give us a 10. :) Thank you!" << endl;
	system("PAUSE");
    return 0;
}

int menu() {//ΜΕΝΟΥ ΕΠΙΛΟΓΩΝ
	int answer;
	cout << "1: Insert.\n" <<
		"2: Delete.\n" <<
		"3: Print InOrder.\n"<<
		"4: Print PostOrded.\n"<<
		"5: Print PreOrder.\n"<<
		"6: Exit.\n";
	cin >> answer;
	return answer;
}
