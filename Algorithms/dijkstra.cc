#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
const int INF = 1e9;

/*
 *Dijkstra, Fins the single source shortest path in O(E+VlogV)
 * Graph must have positive edges or else it will fail.
 * In such case use Bellman Ford's Algorithm
*/


struct Node{
	int node;
	int weight;
	bool operator< (const Node& n) const{
		return weight > n.weight;
	}
};

int main(){
	int n; //number of nodes;
	int m; //number of edges;
	cin >> n >> m;
	vector<vector<Node> > v(n);
	for(int i = 0; i < m; ++i){
		int a, b, cost;
		cin >> a >> b >> cost;
		v[a].push_back({b,cost});
		v[b].push_back({a,cost}); //supposing its directed
	}
	priority_queue<Node> pq;
	    /* The priority queue will contain all the distances to nodes
	    * the first element will be the one which is closest, as all the weights are
	    * positive, this distance cannot be made shorter, hence after we check all posible
	    * edges to take from this node, we will check for the next closest node
	    * This is the VlogV factor in complexity
	    */
	    
	pq.push({0,0}); //we suppose we want to compute the sssp from node 0
	vector<int> d(n,INF);
	d[0] = 0;
	while(!pq.empty()){
		Node n = pq.top(); pq.pop();
		if(d[n.node] == n.weight){
    		for(int i = 0 ; i < v[n.node].size(); ++i){
    		    /* We check all possible edges here
    		    * This is the E factor in complexity
    		    */
    			if(d[v[n.node][i].node] > d[n.node] + v[n.node][i].weight){
    				d[v[n.node][i].node] = d[n.node] + v[n.node][i].weight;
    				pq.push({v[n.node][i].node, d[v[n.node][i].node]});
    			}
    		}
		}
	}
}
