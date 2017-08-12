#include <bits/stdc++.h>
using namespace std;

/*
 *  LCA or Lowest Common Ancestor is a common tree
 *  Problem where we should find the common Ancestor
 *  Of 2 nodes with maximum depth.
 *  We will describe an algorithm which works in
 *  O(n) Preprocessing and O(1) queries
 *  Although we can also use:
 *      -SparseTable (O(n),O(logN))
 *      -BinaryLifting (O(nlogn),O(logn)
 *  This method is a little faster and uses 2 facts
 *      -LCA can be reduced to RMQ in linear time
 *      -RMQ where adjacent elements differ by one can
 *          be answered with O(n) preprocessing
 */
struct SparseTable {
    //ST saves the index, not the value
    vector<vector<int> > ST;
    vector<int > P;
    int N;
    int MAXLOG = 0;

    void build(int n, const vector<int>& V){
        N = n;
        while ((1 << MAXLOG) <= N) ++MAXLOG;
        ST = vector<vector<int> > (N, vector<int> (MAXLOG));
        P = vector<int> (N + 1);
        int LOG = 0;
        for (int i = 1; i < N + 1; ++i) {
            if(1 << (LOG+1) <= i) P[i] = ++LOG;
            else P[i] = LOG;
        }
        // Dynamic Sparse table building
        for (int i = 0; i < N; ++i) {
            ST[i][0] = i;
        }
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
        int LOG = P[r - l + 1];

        // we need an interval range such the we can cover [l,r] with
        // [l , l + 2^LOG) and [r - 2^LOG + 1, r+1)
        // hence we need the maximum LOG, such that 2^LOG is smaller than
        // the range or [l,r]
        // Which has been preprocessed before
        if (V[ST[l][LOG]] < V[ST[r - (1 << LOG) + 1][LOG]])
            return ST[l][LOG];
        return ST[r - (1 << LOG) + 1][LOG];

    }
};

struct Tree {
    vector<vector<int> > adj;
    int V, E;
    int LOG;
    vector<int> Eulerian_tour, RMQ_reduction, Ocurrence;
    SparseTable S;
    // This vectors will save the ith value in the eulerian tour and its depth
    // And the first appereance of each node
    // Note that Eulerian_tour and RMQ_reduction will have size 2*N -1
    // We will root the tree at 0

    void Eulerian_dfs(int p, int u, int depth){
        if (Ocurrence[u] == -1) Ocurrence[u] = Eulerian_tour.size();
        Eulerian_tour.push_back(u);
        RMQ_reduction.push_back(depth);
        for (int v : adj[u]) {
            if (v != p) {
                Eulerian_dfs(u, v, depth + 1);
                Eulerian_tour.push_back(u);
                RMQ_reduction.push_back(depth);
            }
        }
    }

    void build(int n){
        V = n;
        E = n - 1;
        adj.resize(V);
        Ocurrence = vector<int> (V, -1);
        for (int i = 0; i < E; ++i) {
            int x, y;
            cin >> x >> y; // we suppose nodes are 0-indexed
            adj[x].push_back(y);
            adj[y].push_back(x);
        }
        Eulerian_dfs(0, 0, 0);
        S.build(RMQ_reduction.size(), RMQ_reduction);
    }

    int query(int l, int r){
        int L = min(Ocurrence[l], Ocurrence[r]);
        int R = max(Ocurrence[l], Ocurrence[r]);
        return Eulerian_tour[S.query(L, R, RMQ_reduction)];
    }

};

int main(){
    int n;

    cin >> n;
    Tree T;
    T.build(n);
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i){
        int x,y;
        cin >> x >> y;
        cout << T.query(x,y) << endl;
    }

}
