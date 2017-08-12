#include <bits/stdc++.h>
using namespace std;

/*
 * Given a undirected graph with n vertices and m edges
 * we are asked to find:
 *	 	articulation points
 * 		bridges
 * Our algorithm will run in O(V+E)
*/

vector<int> dfs_num; //when a vertex is visited for the first time
vector<int> dfs_low; //stores the lowest value dfs_num reachable from the subtree
vector<int> articulation; //stores articulation points
vector<int> bridge;
vector<int> parent;
vector<vector<int>> adj;
vector<pair<int,int>> E;
int cnt = 0;
int dfsroot;
int rootchildren;

void dfs(int u){
	dfs_num[u] = dfs_low[u] = cnt++;
	for(int t : adj[u]){
        int v = E[t].first ^ E[t].second  ^ u;

		//not visited
		if( dfs_num[v] == -1){
            if(u == dfsroot) rootchildren++; //special case it must have more than 1 children
			parent[v] = u; //we assign its parent to avoid cycles a-b-a
			dfs(v);
            dfs_low[u] = min(dfs_low[u], dfs_low[v]);

            //after we have performed the dfs from v if the lowest it can go is still larger than
            //the time we went in, it must mean it can't visit any edge before us => we must be a articulation point
			if(dfs_low[v] >= dfs_num[u]){
				articulation[u] = 1;
			}

            //if it is strictly larger, which means it can't even visit us, the edge we are passing must be a bridge.
			if(dfs_low[v] > dfs_num[u]){
				bridge[t] = 1;
			}

		}
		//already visited => cycle
		else if (v != parent[u]){
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
		}
	}
}

int main(){
	int n,m;
	cin >> n >> m;
	adj = vector<vector<int>>(n);
	dfs_low = dfs_num = parent = vector<int>(n,-1);
	articulation = vector<int>(n,0);
    bridge = vector<int>(m,0);
    E = vector<pair<int,int>>(m);
	for(int i = 0; i < m; ++i){
		int x,y;
		cin >> x >> y;
        E[i] = {x,y};
		adj[x].push_back(i);
		adj[y].push_back(i);
	}
	for (int i = 0; i < n; ++i){
		if (dfs_num[i] == -1) {
			dfsroot = i;
			rootchildren = 0;
			dfs(i);
			articulation[dfsroot] = (rootchildren > 1);
		}
	}
}
