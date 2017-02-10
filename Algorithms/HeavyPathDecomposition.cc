#include <bits/stdc++.h>
using namespace std;

/*
 * Heavy Path Decomposition is an Algorithm which allows
 * Checking a LA in O(n),O(logn) time
 * it does so by decompositioning recursively a tree by
 * its heaviest subtree
 */

struct HeavyPath {
    /*
        First we would Make a DFS with number of nodes in each subtree
        Then we would make 1 vector and 1 matrix, to save the paths and
        saving a pointer to the path
        We then compute the binarylifting on the tree and make paths length 2k
    */
    int V;
    vector<int> Nodes;
    vector<int> Path_Change;
    vector<pair<int,int> > Point;
    vector<vector<int> >Paths;
    vector<vector<int> > adj;
    int dfs(int p, int node){
        for (int i = 0; i < adj[node].size(); ++i) {
            if (adj[node][i] != p) {
                Nodes[node] += dfs(node, adj[node][i]);
            }
        }
        return Nodes[node];
    }

    void build_path(int path, int p, int node){
        int mx = -1;
        int add;
        for (int i = 0; i < adj[node].size(); ++i) {
            if (adj[node][i] != p) {
                if(Nodes[adj[node][i]] > mx){
                    mx = Nodes[adj[node][i]];
                    add = adj[node][i];
                }
            }
        }
        Point[add] = {path, Paths.size()};
        Paths[path].push_back(add);
        build_path(path, node, add);
        for (int i = 0; i < adj[node].size(); ++i) {
            if (adj[node][i] != p and adj[node][i] != add) {
                Path_Change.push_back(node);
                Paths.push_back(vector<int>(0));
                Point[add] = {Paths[node].size()-1, 0};
                build_path(Paths[node].size()-1, node, adj[node][i]);
            }
        }
    }

    void build(int n){
        V = n;
        Nodes = vector<int> (V,1);
        Point = vector<pair<int,int> > (V);
        dfs(0, 0);
        Point[0] = {0, 0};
        Path_Change.push_back(-1);
        Paths.push_back(vector<int>(0));
        build_path(0,0,0);
        for(int i = 0; i < Paths.size(); ++i){
            reverse(Paths[i].begin(),Paths[i].end());
            int point = Path_Change[i];
            while(point != -1){
                Paths[i].push_back(Paths[Point[point].first][Point[point].second]);
                point = Point[point].second-1;
                if(point == -1) point = Path_Change[Point[point].first];
            }
            reverse(Paths[i].begin(),Paths[i].end());
        }
    }
};

int main(){
    int n;

    cin >> n;

}
