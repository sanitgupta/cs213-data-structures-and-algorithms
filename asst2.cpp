#include<iostream>
#include<vector>
#include<algorithm>
#include<unistd.h>
#include<iomanip>

using namespace std;

class heap
{
	public:
	int next;
	vector<vector<double> > h;

		heap() 
		{ 
		    next = 0; 
		}
		
		void add (vector<double> ad)
		{
		    h.push_back(ad);
		    next++;
		    heapUp();
		}
		
		vector<double> remove ()
		{	
			vector<double> temp = h[0];
		    if (next == 0)
		        cout << "UNDERFLOW";
		    else 
		        {
		            h[0] = h[next - 1];
		            next = next - 1;
		            h.erase(h.begin() + next);
		            heapDown(0);
		        }

		    return temp;     
		}

		void display()
		{
			int k = 2;
			for (int i = 0; i < next; i++)
			{
				cout << h[i][0] << " ";

				if (i + 2 == k)
				{
					cout << endl;
					k = k * 2;
				}
			}
		}

		int p (int i)
		{
			return (i - 1)/2;
        }
        
        int l (int i)
		{
		    return 2 * i + 1;
		}
		
		int r (int i)
		{
		    return 2 * i + 2;
		}
		
		bool lC (int i)
		{
		    return l(i) < next;
		}
		
		bool rC (int i)
		{
			return r(i) < next;
		}
		
		void heapUp()
		{
		    int r = next - 1;
		    while (h[p(r)][1] > h[r][1] && r != 0)
		    {
		        vector<double> temp;
		        temp = h[p(r)];
		        h[p(r)] = h[r];
		        h[r] = temp;
		        r = p(r);
		    }
		}
		
		void heapDown(int i)
		{
			vector<double> temp;
			
			if (lC(i) && rC(i))    
			    if (h[l(i)][1] < h[r(i)][1])
			    {
			    	if (h[i][1] > h[l(i)][1])    
			    	{
			    		temp = h[l(i)];
			        	h[l(i)] = h[i];
			        	h[i] = temp;
			    	}
			    	heapDown(l(i));
			    }
			    
			    else
			    {
			    	if (h[i][1] > h[r(i)][1])    
			    	{
			    		temp = h[r(i)];
			        	h[r(i)] = h[i];
			        	h[i] = temp;
			    	}
			    	heapDown(r(i));
			    }
			else if (lC(i))
			{
				if (h[i][1] > h[l(i)][1])    
			    	{
			    		temp = h[l(i)];
			        	h[l(i)] = h[i];
			        	h[i] = temp;
			    	}
			    	heapDown(l(i));
			}
			else if(rC(i))
			{
				if (h[i][1] > h[r(i)][1])    
			    	{
			    		temp = h[r(i)];
			        	h[r(i)] = h[i];
			        	h[i] = temp;
			    	}
			    	heapDown(r(i));
			}
		}
};

int main()
{
    int n, nc = 0;
    double a, b, t, tt = 0, d;
    cin >> n;
    vector <vector<double> > o(n, vector<double>());
    vector <double> v, s;

    for (int i = 0; i < n; i++) {
        cin >> a;
        cin >> b;
    	o[i].push_back(a);
    	o[i].push_back(b);
    }
    
    heap H;
    
    for(int i = 0; i < n - 1; i++) {
    	d = o[i + 1][0] - o[i][0];
    	if (d >= 0)
    		t = (d - 2) / (o[i][1] - o[i + 1][1]);
    	else
    		t = (d + 2) / (o[i][1] - o[i + 1][1]);
       	
       	if (o[i][1] - o[i + 1][1] == 0)
    	{
    	    t = -1;
    	}

    	if ((d - 2 == 0 && o[i][1] - o[i + 1][1] < 0)||(d + 2 == 0&&o[i][1] - o[i + 1][1] > 0))
   			t = -1;

    	v.push_back(i);
    	v.push_back(t);
    	H.add(v);
    	v.clear();
    }


    while (H.next != 0)
    {
    	s = H.remove();

    	if (s[1] >= 0 && s.size() == 2)
    	{
    		tt += s[1];
    		nc++;
    		for (int i = 0; i < H.h.size(); i++) {
    			H.h[i][1] -= s[1];
    		}
    		
    		for (int i = 0; i < n; i++) {
    			o[i][0] += o[i][1] * s[1];
    		}
    		//collision
    		double coll;
    		coll = o[s[0]][1];
    		o[s[0]][1] = o[s[0] + 1][1];
    		o[s[0] + 1][1] = coll;

    		//aftereffect
    		if (s[0] + 1 < n - 1)
    		{
    			for (int i = 0; i < H.h.size(); i++) {
    				if (H.h[i][0] == s[0] + 1)
    					H.h[i].push_back(-1);
    			}
    			d = o[s[0] + 1][0] - o[s[0] + 2][0];
    			if (d >= 0)
    				t = (d - 2) / (o[s[0] + 2][1] - o[s[0] + 1][1]);
    			else
    				t = (d + 2) / (o[s[0] + 2][1] - o[s[0] + 1][1]);

    		    if ((d - 2 == 0 && o[s[0] + 2][1] - o[s[0] + 1][1] < 0)||(d + 2 == 0 && o[s[0] + 2][1] - o[s[0] + 1][1] > 0))
   					t = -1;


    			if (o[s[0] + 2][1] - o[s[0] + 1][1] == 0)
    			{
    	    		t = -1;
    			}

    			v.push_back(s[0] + 1);
		    	v.push_back(t);
		    	H.add(v);
		    	v.clear();
    		}

    		if (s[0] - 1 >= 0)	
    		{
    			for (int i = 0; i < H.h.size(); i++) {
    				if (H.h[i][0] == s[0] - 1)
    					H.h[i].push_back(-1);
    			}
    			
    			d = o[s[0] - 1][0] - o[s[0]][0];
    			if (d >= 0)
    				t = (d - 2) / (o[s[0]][1] - o[s[0] - 1][1]);
    			else
    				t = (d + 2) / (o[s[0]][1] - o[s[0] - 1][1]);

    		    if ((d - 2 == 0 && o[s[0]][1] - o[s[0] - 1][1] < 0)||(d + 2 == 0 && o[s[0]][1] - o[s[0] - 1][1] > 0))
   					t = -1;

    			if (o[s[0]][1] - o[s[0] - 1][1] == 0)
    			{
    	    		t = -1;
    			}

				v.push_back(s[0] - 1);
		    	v.push_back(t);
		    	H.add(v);
		    	v.clear();
    		}

    	}
    }
    if (nc != 0)
    {
        cout << nc << endl;
        cout << fixed << setprecision(10) << tt << endl;
    
        for (int i = 0; i < n; i++)
        {
        	cout << fixed << setprecision(10) << o[i][0] << " " << o[i][1] << endl;
        }
    }
    else
        cout << -1;

    return 0;
}