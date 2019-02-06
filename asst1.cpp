#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<string>

using namespace std;
int count = 0;

void check(string z, int G[], string a, string b, string c)
{
	int i1 = 0, i2 = 0, i3 = 0;
	
	for (int i = 0; i < a.length(); i++) {
		i1 += G[z.find(a[i])] * pow(10, a.length() - i - 1);
	}

	for (int i = 0; i < b.length(); i++) {
		i2 += G[z.find(b[i])] * pow(10, b.length() - i - 1);
	}
	
	for (int i = 0; i < c.length(); i++) {
		i3 += G[z.find(c[i])] * pow(10, c.length() - i - 1);
	}

	if (i1 + i2 == i3 && G[z.find('M')] != 0)
	{
		for (int i = 0; i < z.length(); i++) {
			cout << z[i] << " = " << G[i] << endl;
		}
		cout << endl << endl;
		count++;
	} 
}

void assgn (string z, int k, int G[], string a, string b, string c)
{	
	if (k == z.length())
	{
		check(z, G, a, b, c);
	}

	else
	{
		for (int i = 0; i < 10; i++)
		{
			int j = 0;
			for (j = 0; j < k; j++)
			{
				if (G[j] == i)
					break;
			}
			if (G[j] == i)
				continue;
			
			G[k] = i;
			assgn(z, k + 1, G, a, b, c);
		}
	}
}


int main()
{
	string s1, s2, s3;
	
	s1 = "SEND";
	s2 = "MORE";
	s3 = "MONEY";
	/*
	cout << "  " << s1 << endl;
	cout << " " << "+" << s2 << endl;
	cout << "=" << s3 << endl; 
	*/
	
	string x = s1 + s2 + s3;
	string z;

	for (int i = 0; i < x.length(); i++) {
		if (z.find(x[i]) == string::npos)
			z = z + x[i];
	}

	int G[z.length()];
	assgn(z, 0, G, s1, s2, s3);
	
	cout << count;
	return 0;
}