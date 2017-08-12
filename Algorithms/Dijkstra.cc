#include <bits/stdc++.h>
using namespace std;

const int oo = 1e9;

/*
 *Dijkstra, Fins the single source shortest path in O(E+VlogV)
 * Graph must have positive edges or else it will fail.
 * In such case use Bellman Ford's Algorithm
*/

struct Node{
	int u;
	int w;
	bool operator< (const Node& n) const{
		return w > n.w;
	}
};

vector<vector<Node>> adj;
int dijkstra(int s, int t, int n) {
	priority_queue<Node> pq;
	vector<int> d(n,oo);
	d[s] = 0;
	pq.push({s,d[s]});
	while(pq.size()){
		Node n = pq.top(); pq.pop();
		int u = n.u, _w = n.w;
		if(u == t) return d[t];
		if(d[u] == _w){
			for(Node N : adj[u]){
				int v = N.u, w = N.w;
				if(d[v] > d[u] + w){
					d[v] = d[u] + w;
					pq.push({v, d[v]});
				}
			}
		}
	}
	return d[t];
}
int main(){
	int n; //number of nodes;
	int m; //number of edges;
	cin >> n >> m;
	adj = vector<vector<Node> >(n);
	for(int i = 0; i < m; ++i){
		int a, b, cost;
		cin >> a >> b >> cost;
		adj[a].push_back({b,cost});
		adj[b].push_back({a,cost}); //supposing its undirected
	}
	cout << dijkstra(0, n-1, n) << endl;
}
