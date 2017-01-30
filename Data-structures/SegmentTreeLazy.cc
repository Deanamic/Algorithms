#include <bits/stdc++.h>
using namespace std;

/* Segment Tree/ Interval Tree
 * Stores information in a Heap
 * Modification, lookup in O(logn)
 * Provides Tools to update intervals
 * All intervals are [ , )
*/

struct LazySegmentTree{
    vector<int> Seg;
    vector<int> lazy;
    int n;

    void build(vector<int>& v, int m){
		n = m;
        Seg = lazy = vector<int> (4*n,0);
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
        if (lazy[id] != 0) {
            Seg[id] +=  (right-left)*lazy[id];
            if (x + 1 < y) {
                lazy[2*id] += lazy[id];             // Lazy propagation
                lazy[2*id + 1] += lazy[id];
            }
            lazy[id] = 0;
        }
		if(left >= y or right <= x){
			return 0;
		}
		if(left >= x and right <= y){
			return Seg[id];
		}
		int mid = (left + right)/2;
		return find(x, y, 2*id, left, mid) + find(x, y, 2*id + 1, mid, right);
	}

    int updateinterval(int p, int x, int y){
		updateinterval(p, 1, x, y, 0, n);
	}

    void updateinterval (int p, int id, int x, int y, int left, int right) {
        if (lazy[id] != 0) {
            Seg[id] +=  (right-left)*lazy[id];
            if (x + 1 < y) {
                lazy[2*id] += lazy[id];
                lazy[2*id + 1] += lazy[id];
            }
            lazy[id] = 0;
        }
        if(left >= y or right <= x){
			return;
		}
		if(left >= x and right <= y){
            Seg[id] +=  (right-left)*p;
            if (x + 1 < y)  {
                lazy[2*id] += p;
                lazy[2*id + 1] += p;
            }
            return;
        }
        int mid = (left + right)/2;
        updateinterval (p, 2*id, x, y, left, mid);
        updateinterval (p, 2*id, x, y, mid, right);
        Seg[id] = Seg[2*id] + Seg[2*id + 1];

    }
};
