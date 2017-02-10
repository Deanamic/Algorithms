#include <bits/stdc++.h>
using namespace std;

/*
 * Binary Lifting is an Algorithm which takes O(nlogn),O(logn) to precompute
 * and answer query to the level anscestor problem by storing the 2^i ancestor
 * of every node
 */

struct BinaryLifting {
    vector<vector<int> > BL;
    vector<vector<int> > adj;
    vector<int> P;
    vector<int> Anc;
    int V,E;
    int MAXLOG = 0;

    void dfs(int p, int node){
        for (int i = 0; i < adj[node].size(); ++i) {
            if (adj[node][i] != p) {
                Anc[adj[node][i]] = p;
                dfs(node, adj[node][i]);
            }
        }
    }

    void build(int n){
        V = n;
        E = n-1;
        Anc.resize(V);
        Anc[0] = 0;
        P.resize(V+1);
        while ((1 << MAXLOG) <= V) ++MAXLOG;
        BL = vector<vector<int> > (V, vector<int> (MAXLOG));
        for (int i = 0; i < E; ++i) {
            int x, y;
            cin >> x >> y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        int LOG = 0;
        for (int i = 1; i < V + 1; ++i) {
            P[i] = ((1 << LOG) > i ? LOG - 1 : ++LOG - 1);
        }
        // Dynamic Sparse table building
        for (int i = 0; i < V; ++i) {
            BL[i][0] = Anc[i];
        }
        for (int j = 1; 1 << j < V; ++j) {
            for (int i = 0; i < V; ++i) {
                BL[i][j] = BL[BL[i][j-1]][j-1];
            }
        }
    }

    int maxjump(int depth, int node){
        return BL[node][P[depth]];
    }
};

int main(){
    int n;

    cin >> n;


}
