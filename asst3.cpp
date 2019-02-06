#include<iostream>
#include<stdio.h>
#include<vector>
#include<algorithm>
#define COUNT 10

using namespace std;

struct Node;

struct bstIt {
	vector<Node*> anc;
	void operator++();
	int operator*();
	bool operator !=(const bstIt b);
};

struct Node {
	Node *left, *right;
	int value;
	Node(int v) {value = v; left = right = NULL;}
	typedef bstIt iterator;
	bstIt begin();
	bstIt end();
};

bstIt Node::begin() {
	Node* ptr = this;
	iterator a;
	a.anc.push_back(ptr);
	while(ptr->left != NULL) {
		ptr = ptr->left;
		a.anc.push_back(ptr);
	}
	return a;
}


bstIt Node::end() {
	iterator a;

	return a;
}

bool bstIt::operator!=(const bstIt b) {
	return this->anc != b.anc;
}


int bstIt::operator*(){
  return anc.back()->value;
}

void bstIt::operator++() {
	Node* ptr = anc.back();
	if (ptr->right == NULL) {
		if (anc.size() > 1)
			if(anc[anc.size() - 2]->left == anc[anc.size() - 1])
				anc.pop_back();
			else {
				while (anc[anc.size() - 2]->left != anc[anc.size() - 1]) {
					anc.pop_back();
					if (anc.size() < 2)
						break;
				}

				anc.pop_back();
			}
		else
			anc.pop_back();
	}
	else if (ptr -> right != NULL) {
		ptr = ptr -> right;
		anc.push_back(ptr);
		while (ptr -> left !=NULL) {
			ptr = ptr -> left;
			anc.push_back(ptr);
		}
	}
}

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
		Node* next = new Node(x);
		myset = next;
	}
	else if(x < myset->value)
		insert(myset->left, x);
	else if(x > myset->value)
		insert(myset->right, x);
	else
		insert(myset->left, x);
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
  Node* s = NULL;
  while(true){
    char input;
    cin >> input;
    if(input == 'x')
      break;
    else if(input == 'i'){
      int value;
      cin >> value;
      insert(s, value);
    }
    else if(input == 'p'){
      if(s == NULL){
        cout << -1 << endl;
      }
      else {
        for(Node::iterator it = s->begin(); it !=s->end(); ++it){
          cout << *it << ' ';
        }
        cout << endl;
      }
    }
  }
}
