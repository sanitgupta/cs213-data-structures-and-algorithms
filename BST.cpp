#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#define COUNT 10

using namespace std;

struct Node {
	Node *left, *right;
	int value;
};

bool find(Node* myset, int x) {
	if(myset == NULL) return false;
	if (x == myset->value)
		return true;
	else if (x < myset->value)
		find(myset->left, x);
	else 
		return find(myset->right, x);
}

void insert(Node* &myset, int x) {
	if(myset == NULL) {
		Node* next = new Node;
		next->value = x;
		myset = next;
	}
	else if(x < myset->value)
		insert(myset->left, x);
	else if(x > myset->value)
		insert(myset->right, x);
}

void del(Node* &myset, int x) {
	if(myset == NULL) {
		;
	}
	else if (x == myset->value) {
		if (myset->left == NULL && myset->right == NULL) {
			delete myset;
			myset = NULL;
		}
		else if (myset->right == NULL) {
			Node* temp;
			temp = myset;
			myset = myset->left;
			delete temp;
		}
		else if (myset->left == NULL) {
			Node* temp;
			temp = myset;
			myset = myset->right;
			delete temp;
		}
		else {
			Node* temp;
			temp = myset->right;
			while(temp->left != NULL) {
				temp = temp->left;
			}
			myset->value = temp->value;
			del(myset->right, temp->value);
		}
	}
	else if (x < myset->value)
		del(myset->left, x);
	else if (x > myset->value)
		del(myset->right, x);
}

void print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
 
    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(Node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);

   cout << endl << endl << endl << endl;
}


int main() {
	Node* myset = NULL;
	cout << myset;
	insert(myset, 5);
	cout << myset;
	insert(myset, 0);
	cout << myset;
	insert(myset, 10);
	insert(myset, 3);
	insert(myset, 9);
	insert(myset, 7);
	insert(myset, 8);
	insert(myset, 11);
	print2D(myset);
	del(myset, 5);
	print2D(myset);
	del(myset, 11);
	del(myset, 7);
	del(myset, 9);
	cout << find(myset, 11);
	cout << find(myset, 12);
	cout << find(myset, 8);

	cout << endl;

	return 0;
}
