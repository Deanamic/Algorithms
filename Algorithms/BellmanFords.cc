#include <bits/stdc++.h>
using namespace std;

/*
	Bellman-Ford is an SSSP Algorithm which works with negative weights.
 	The idea being, the shortest path from any u to any other edge at most will have V-1 edges in between
	Unless there are negative cycles.
	Complexity O(VE)
*/

vector<int> dist;
const int oo = 1e9;

struct edge{
	int v,w;
};

vector<vector<edge>> adj;

void bellmanford(int V,int source){
	dist[source] = 0;
	for(int I = 0; I < V; ++I){
		for(int i = 0; i < V; ++i){
			for(edge e: adj[i]) {
				dist[e.v] = min(dist[e.v], dist[i] + e.w);
			}
		}
	}
}

bool checkcycle(int V){
	for(int i = 0; i < V; ++i){
		for(edge e: adj[i]) {
			if(dist[e.v] > dist[i] + e.w) return true;
		}
	}
	return false;
}

int main(){
	int n,m,a,b,c;
	cin >> n >> m;
	adj = vector<vector<edge>>(n);
	for(int i = 0; i < m; ++i){
		cin >> a >> b >> c;
		adj[a].push_back({b,c});
	}
	dist = vector<int>(n,oo);
	bellmanford(n, 0);
	bool negativecycle = checkcycle(n);
	for(int i = 0; i < n; ++i) cout << dist[i] <<' ';
	cout << endl;
	cout << (negativecycle ? "yes" : "no") << endl;
}
