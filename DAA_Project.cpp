/* Group Members:-
M Waleed Nasir (15b-029-se)
Sufyan Ahmed (15b-068-se)
Rao Awais (15b-083-se)*/


#include <iostream>
#include <conio.h>

using namespace std;

#define MAX 4 // It will ensure that the maximum childs for the "3" nodes are "4"
#define MIN 2 // It will ensure that the maximum childs for the "1" nodes are "2"

struct btreeNode {
	int val[MAX + 1], count;
	btreeNode *link[MAX + 1];
};

btreeNode *root;

/* creating new node */
btreeNode * createNode(int val, btreeNode *child) {
	btreeNode *newNode = new btreeNode;
	newNode->val[1] = val;
	newNode->count = 1;
	newNode->link[0] = root;
	newNode->link[1] = child;
	return newNode;
}

/* Places the value in appropriate position */
void addValToNode(int val, int pos, btreeNode *node, btreeNode *child) {
	int j = node->count;
	while (j > pos) {
		node->val[j + 1] = node->val[j];
		node->link[j + 1] = node->link[j];
		j--;
	}
	node->val[j + 1] = val;
	node->link[j + 1] = child;
	node->count++;
}

/* split the node */
void splitNode(int val, int *pval, int pos, btreeNode *node, btreeNode *child, btreeNode **newNode) {
	int median, j;

	if (pos > MIN)
		median = MIN + 1;
	else
		median = MIN;

	*newNode = new btreeNode;
	j = median + 1;
	while (j <= MAX) {
		(*newNode)->val[j - median] = node->val[j];
		(*newNode)->link[j - median] = node->link[j];
		j++;
	}
	node->count = median;
	(*newNode)->count = MAX - median;

	if (pos <= MIN) {
		addValToNode(val, pos, node, child);
	}
	else {
		addValToNode(val, pos - median, *newNode, child);
	}
	*pval = node->val[node->count];
	(*newNode)->link[0] = node->link[node->count];
	node->count--;
}

/* sets the value val in the node */
int setValueInNode(int val, int *pval, btreeNode *node, btreeNode **child) {

	int pos;
	if (!node) {
		*pval = val;
		*child = NULL;
		return 1;
	}

	if (val < node->val[1]) {
		pos = 0;
	}
	else {
		for (pos = node->count;
			(val < node->val[pos] && pos > 1); pos--);
		if (val == node->val[pos]) {
			cout << "Duplicates not allowed\n";
			return 0;
		}
	}
	if (setValueInNode(val, pval, node->link[pos], child)) {
		if (node->count < MAX) {
			addValToNode(*pval, pos, node, *child);
		}
		else {
			splitNode(*pval, pval, pos, node, *child, child);
			return 1;
		}
	}
	return 0;
}

/* insert val in B-Tree */
void insertion(int val) {
	int flag, i;
	btreeNode *child;

	flag = setValueInNode(val, &i, root, &child);
	if (flag)
		root = createNode(i, child);
}

/* B-Tree Traversal */
void traversal(btreeNode *myNode) {
	int i;
	if (myNode)
	{
		for (i = 0; i < myNode->count; i++) 
		{
			traversal(myNode->link[i]);
			cout << myNode->val[i + 1] << ' ';
		}
		traversal(myNode->link[i]);
	}
	cout << endl;
}

int main() {
	int val, opt;
	while (true) {
		cout << "*****************************************\n";
		cout << "1. Insertion\t 2. Traversal\t 3. Exit\n";
		cout << "*****************************************\n";
		cout << "\nEnter Your Choice : ";
		cin >> opt; // get you input to process your command to insert in tree or to traverse from the tree or to exit from the program
		cout << endl;
		switch (opt) {
		case 1:
			cout << "Enter Your Input : "; // Enter the input of your choice to insert in the tree but it must be an integer !
			cin >> val;
			insertion(val);
			break;
		case 2:
			traversal(root);
			break;
		case 3:
			exit(0);
		}
		cout << endl;
	}
	return 0;
}
