#include<iostream>
#include<string>
#include<stdlib.h>
#include<fstream>

using namespace std;

struct Node {
	char op;
	string value;
	Node* l;
	Node* r;
	Node(char OP, Node* L, Node* R) {
		op = OP;
		l = L;
		r = R;
	}
	
	Node (string v) {
		value = v;
		op = 'P';
		l = r = NULL;
	}

	Node(istream &infile) {
		char c = infile.get();
		if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
		{
			l = r = NULL;
			op = 'P';
			value = c;
		}
		else if (c == '(') {
			l = new Node(infile);
			op = infile.get();
			r = new Node(infile);
			if(infile.get() != ')')
				cout << "No matching parenthesis. \n";
		}
		else 
			cout << "Error in input. \n";
	}
	
	int compare(Node* l1, Node* r1) {
		
		char left, right;
		if(l1->op == 'P')
			left = l1->value[0];
		else if (l1 == NULL)
			left = '~';
		else
			left = l1->op;

		if(r1->op == 'P')
			right = r1->value[0];
		else if(r1 == NULL)
			right = '~';
		else 
			right = r1->op;
		

		if (left > right)
			return -1;
		else if (right > left)
			return 1;
		else if (left == right)
		{
			if (l1->op == 'P' && r1->op == 'P')
			{
				return 0;
			}

			int t = compare(l1->l, r1->l);
			if (t == 0)
				t = compare(l1->r, r1->r);
			return t;
		}
	}

	void canon() {
		if (l != NULL && l->op != 'P')
			l->canon();
		if (r != NULL && r->op != 'P') 
			r->canon();
		
		if(op == '+')
		{
			int p = compare(l, r);

			if(p == -1)
			{
				Node* temp = l;
				l = r;
				r = temp;
			}
		}
	}
};

bool comp(Node* x, Node* y) {
	bool ret = 1;
	
	if (x -> op != 'P' && y -> op != 'P' && x -> op == y -> op) 
	{
		ret = comp(x->l, y->l) * comp(x->r, y->r);
	}
	
	else if (x -> op != 'P' && y -> op != 'P' && x -> op != y -> op) 
	{
		ret = 0;
	}
	
	else if(x -> op == 'P' && y -> op == 'P')
	{
		if(x->value == y->value)
			ret = 1;
		else
			ret = 0;
	}
	
	else 
		ret = 0;
	
	return ret;
}

int main() 
{
 	Node formula1(cin);
 	Node formula2(cin);
 	formula1.canon();
 	formula2.canon();
 	cout << comp(&formula1, &formula2);
}