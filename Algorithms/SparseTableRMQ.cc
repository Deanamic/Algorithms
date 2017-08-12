#include <bits/stdc++.h>
using namespace std;

/*
 *  Sparse table is an algorithm which uses a table to store values of the answer
 *  to the query in intervals of length 2^i for 0 <= i <= MAXLOG
 *  It is specially useful for RMQ (O(nlogn) preprocess and O(1) queries)
 *  or LCA. This code will use the RMQ algorithm to process the range minimum query
 *  ! Sparse table doesnt allow for modifications
 */

struct SparseTable {
    vector<vector<int> > ST;
    vector<int > P;
    vector<int> v;
    int N;
    int MAXLOG = 0;

    void build(int n){
        N = n;
        while ((1 << MAXLOG) <= N) ++MAXLOG;
        ST = vector<vector<int> > (N, vector<int> (MAXLOG));
        P = vector<int> (N+1);
        v = vector<int> (N);
        for (int i = 0; i < N; ++i) {
            cin >> v[i];
        }

        int LOG = 0;
        for(int i = 1; i < N + 1; ++i){
            P[i] = ((1<<LOG) > i ?  LOG-1 : ++LOG-1);
        }
        // Dynamic Sparse table building
        for(int i = 0; i < N; ++i) ST[i][0] = i;
        for (int j = 1; j < MAXLOG; ++j) {
            for (int i = 0; i + (1 << j) - 1 < N; ++i) {
                if (v[ST[i][j - 1]] < v[ST[i + (1 << (j - 1))][j - 1]])
                     ST[i][j] = ST[i][j - 1];
                else
                     ST[i][j] = ST[i + (1 << (j - 1))][j - 1];
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
        int LOG = P[r-l+1];

        // we need an interval range such the we can cover [l,r] with
        // [l , l + 2^LOG) and [r - 2^LOG + 1, r+1)
        // hence we need the maximum LOG, such that 2^LOG is smaller than
        // the range or [l,r]
        // Which has been preprocessed before
        return min(v[ST[l][LOG]], v[ST[r - (1 << LOG) + 1][LOG]]);

    }

    //Overload if we do not one to store v in the struct
    void build(int n, const vector<int>& V){
        N = n;
        while ((1 << MAXLOG) <= N) ++MAXLOG;
        ST = vector<vector<int> > (N, vector<int> (MAXLOG));
        P = vector<int> (N+1);
        int LOG = 0;
        for(int i = 1; i < N + 1; ++i){
            P[i] = ((1<<LOG) > i ?  LOG-1 : ++LOG-1);
        }
        // Dynamic Sparse table building
        for(int i = 0; i < N; ++i) ST[i][0] = i;
        for (int j = 1; j < MAXLOG; ++j) {
            for (int i = 0; i + (1 << j) - 1 < N; ++i) {
                if (V[ST[i][j - 1]] < V[ST[i + (1 << (j - 1))][j - 1]])
                     ST[i][j] = ST[i][j - 1];
                else
                     ST[i][j] = ST[i + (1 << (j - 1))][j - 1];
            }
        }
    }

    int query(int l, int r, const vector<int>& V){
        int LOG = P[r-l+1];

        // we need an interval range such the we can cover [l,r] with
        // [l , l + 2^LOG) and [r - 2^LOG + 1, r+1)
        // hence we need the maximum LOG, such that 2^LOG is smaller than
        // the range or [l,r]
        // Which has been preprocessed before
        return min(V[ST[l][LOG]], V[ST[r - (1 << LOG) + 1][LOG]]);

    }
};

int main(){
    int n;
    cin >> n;
    SparseTable S;
    S.build(n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        cout << S.query(x, y) << endl;
    }

}
