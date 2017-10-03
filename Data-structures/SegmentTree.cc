#include <bits/stdc++.h>
using namespace std;

/* Segment Tree/ Interval Tree
 * Stores information in a Heap
 * Modification, lookup in O(logn)
 * All intervals are [ , )
*/

struct SegmentTree{
    vector<int> Seg;
	int n;

	void build(vector<int>& v, int m){
		n = m;
        Seg = vector<int> (4*n,0);
		build(v, 1, 0, n);
	}
	void build( vector<int>& v, int id,int left, int right){
		if(left + 1 >= right){
			Seg[id] = v[left];
			return;
		}
		int mid = (left + right)/2;
		build(v, id * 2, left, mid);
		build(v, id * 2 + 1, mid, right);
		Seg[id] = Seg[id*2] + Seg[id*2 + 1];
	}

	int find(int x, int y){
		return find(x, y, 1, 0, n);
	}
	int find(int x, int y, int id, int left, int right){
		if(left >= y or right <= x){
			return 0;
		}
		if(left >= x and right <= y){
			return Seg[id];
		}
		int mid = (left + right)/2;
		return find(x, y, 2*id, left, mid) + find(x, y, 2*id + 1, mid, right);
	}

	void update(int p, int new_value){
		update(p, new_value, 1, 0, n);
	}
	void update(int p, int new_value, int id, int left, int right){
		if(left + 1 >= right){
			Seg[id] = new_value;
			return;
		}
		int mid = (left+right)/2;
		if(p < mid) update(p, new_value, 2*id, left, mid);
		else update(p, new_value, 2*id + 1, mid, right);
		Seg[id] = Seg[id*2] + Seg[id*2 + 1];
	}
};
