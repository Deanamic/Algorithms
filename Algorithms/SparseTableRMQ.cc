#include <bits/stdc++.h>
using namespace std;

/*
 *  Sparse table is an algorithm which uses a table to store values of the previous
 *  2^i for 0 <= i <= MAXLOG
 *  It is specially useful for RMQ (O(nlogn) preprocess and O(1) queries)
 *  or LCA. This code will use the RMQ algorithm to process the range minimum query
 *  ! Sparse table doesnt allow for modifications
 */

struct SparseTable {
    vector<vector<int> > ST;
    int MAXLOG = 0;
    void build(int n, const vector<int>& v){
        while ((1 << MAXLOG) <= n) ++MAXLOG;
        ST = vector<vector<int> > (n, vector<int> (MAXLOG));

        // Dynamic Sparse table building
        for (int j = 0; j < MAXLOG; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i + (1 << j) - 1 < n)
                    ST[i][j] = (j ? min(ST[i][j - 1], ST[i + (1 << (j - 1))][j - 1]) : v[i]);
            }
        }
        // ST[i][j] is the minimum of a interval of length 2^j
        // intervals are from [i, i+2^j)
        // We will build the segments by length
        // building a segment is easy, to have ST[i][j]
        // we simply take segments [i , i + 2^j-1) and [i + 2^j-1, i + 2^j)
    }

// query range [l,r]
    int query(int l, int r){
        int LOG = 0;

        while ((1 << LOG) <= r - l + 1) ++LOG;
        // we need an interval range such the we can cover [l,r] with
        // [l , l + 2^LOG) and [r - 2^LOG + 1, r+1)
        // hence we need the maximum LOG, such that 2^LOG is smaller than
        // the range or [l,r]
        --LOG;
        return min(ST[l][LOG], ST[r - (1 << LOG) + 1][LOG]);

    }
};

int main(){
    int n;

    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }
    SparseTable S;
    S.build(n, v);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        cout << S.query(x, y) << endl;
    }

}
