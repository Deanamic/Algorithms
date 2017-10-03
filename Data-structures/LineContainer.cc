#include <bits/stdc++.h>
using namespace std;

/*
 * Line Container
 * Allows to add lines and check the maximum at any point in O(logN) time
 */

bool Q;
struct Line {
    //K is slope, m is the constant and p is the last point where this line is MAX
	mutable long long k, m, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};

struct LineContainer : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const long long oo = LLONG_MAX;

    //floored division, e.g -1/2 = -1 instead of 0
	long long div(long long a, long long b) {
		return a / b - ((a ^ b) < 0 && a % b);
    }

    //Return true if we Y is not valuable to the right of x (when y is .end() it is valuable)
    //It also calculates up to which point X is valuable
    //Precondition : the slope of x is <= slope of y
	bool isect(iterator x, const iterator y) {
        //If there is no next line, this line is valueble up to infinity
		if (y == end()) {
            x->p = oo;
            return false;
        }
        //assert(x->k <= y->k);

        //if they have the same slope, x is either always on top of y or always under
		if (x->k == y->k) x->p = x->m > y->m ? oo : -oo;

        //if they have different slope, we have that this lines cross at (m-m')/(k'-k)
		else x->p = div(y->m - x->m, x->k - y->k);

        //return x is valuable to the right of Y
		return x->p >= y->p;
	}

	void add(long long k, long long m) {
        //We insert a new line, and get a pointer to the next one
		auto z = insert({k, m, 0}), y = z++, x = y;
        //lets delete lines to the right of y which aren't valuable
		while (isect(y, z)) z = erase(z);

        //if y is not the first line in the container we check if it holds value beyond the previous one
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));

        //If we did not erase the new line, it is possible that a number of lines previous to
        //it should be deleted
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}

	long long query(long long x) {
        //searches for the lower bound using the p value
		Q = 1;
        auto l = *lower_bound({0,0,x});
        Q = 0;
		return l.k * x + l.m;
	}
};

int main() {
    long long x, y;
    LineContainer L;
    while(cin >> x >> y) {
        L.add(x,y);
    }
}
