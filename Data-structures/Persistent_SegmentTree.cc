#include <bits/stdc++.h>
using namespace std;

/* Persistent Segment Tree/ Interval Tree
 * Stores information in a Heap
 * Modification, lookup in O(logn)
 * All intervals are [ , )
 * Saves a Past versions of the tree
*/

struct PSegmentTree{
    vector<int> Seg;
    vector<int> L,R, root;
	int n;
    int q;
    int NEXT_ID = 1;
    int Kth_Root = 1;
	void build(vector<int>& v, int m, int k){
        q = k;
		n = m;
        L = R = Seg = vector<int> (4*n,0);
        root = vector<int> (q);
        root[0] = 0;
		build(v, 0, 0, n);
	}
	void build( vector<int>& v, int id,int left, int right){
		if(left + 1 >= right){
			Seg[id] = v[left];
			return;
		}
		int mid = (left + right)/2;
        L[id] = NEXT_ID++;
	    R[id] = NEXT_ID++;
		build(v, L[id], left, mid);
		build(v, R[id], mid, right);
		Seg[id] = Seg[L[id]] + Seg[R[id]];
	}

	int find(int x, int y, int k){
		return find(x, y, root[k], 0, n);
	}
	int find(int x, int y, int id, int left, int right){
		if(left >= y or right <= x){
			return 0;
		}
		if(left >= x and right <= y){
			return Seg[id];
		}
		int mid = (left + right)/2;
		return find(x, y, L[id], left, mid) + find(x, y, R[id], mid, right);
	}

	void update(int p, int new_value){
		root[Kth_Root] = update(p, new_value, root[Kth_Root-1], 0, n);
        Kth_Root++;
	}
	int update(int p, int new_value, int id, int left, int right){
        int ID = NEXT_ID++;
		if(left + 1 >= right){
			Seg[ID] = new_value;
			return ID;
		}
		int mid = (left+right)/2;
        L[ID] = L[id],
        R[ID] = R[id];
		if(p < mid) L[ID] = update(p, new_value, L[ID], left, mid);
		else R[ID] = update(p, new_value, R[ID], mid, right);
		Seg[ID] = Seg[L[ID]] + Seg[R[ID]];
        return ID;
	}
};
