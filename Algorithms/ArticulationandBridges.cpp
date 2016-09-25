#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
typedef map<int,int>::iterator ITmii;

#define EPS 1e-9
#define FOR1(x,y,z) for( int x = y; x < z ; ++x)
#define FOR(x,y) FOR1(x,0,y)
#define FOR2(x,y) for(int x = y; x >= 0; --x)
#define PB push_back
#define ALL(X) (X).begin(), (X).end()
#define SORT(X) sort(ALL(X))
#define SIZE(X) ((int)(X).size())

/* 
 * Given a undirected graph with n vertices and m edges 
 * we are asked to find:
 *	 	articulation points
 * 		bridges
 * Our algorithm will run in O(V+E)
*/

VI dfs_num; //when a vertex is visited for the first time
VI dfs_low; //stores the lowest value dfs_num reachable from the subtree
VI articulation; //stores articulation points
VI parent;
VVI adj; //adjacency matrix
/*we can see that we will only update dfs_low to a lower value if there
 *is a cycle (backtracks to an earlier value)
 */
 
 /*
  * given u,v neighbours 
  * if dfs_low(v) >= dfs_num(u) 
  * it means there is no backedge from v to a parent of u(cycle)
  * to go its parent
  * you must go through u, which makes it an articulation point
  */
  
  //there is a special case if we start the dfs with an
  //articulation point
  
  /*
   * given u,v neighbours 
   * if dfs_low(v) > dfs_num(u) then edge u,v is a bridge
   * i.e. there is no dfs subtree from v that return to u
   */
  
 
 int cnt = 0; 
 int dfsroot;
 int rootchildren;
 // this will count when we arrive in the dfs 


//https://jutge.org/problems/P37339_en
//find bridges and print in ascending order
struct Edge{
	int u;
	int v;
	//int weight;
	bool operator< (const Edge& a) const{
		if(a.u != u) return a.v < v;
		return a.u < u;
	}
	//we can overload the operator to have a default less comparison
};
priority_queue<Edge> pq;

//-----
void dfs(int u){
	dfs_num[u] = dfs_low[u] = cnt++;
	for(int i = 0; i < adj[u].size(); ++i){
		int v = adj[u][i];
		if(u == dfsroot) rootchildren++; //special case it must have more than 1 children
		
		//not visited
		if( dfs_num[v] == -1){  
			parent[v] = u; //we assign its parent to avoid cycles a-b-a
			dfs(v);
			
			if(dfs_low[v] >= dfs_num[u]){
				articulation[u] = true;
			}
				
			if(dfs_low[v] > dfs_num[u]){
				pq.push({min(u,v),max(u,v)});
				dfs_low[u] = min(dfs_low[u], dfs_num[v]);
			}
		}
		//already visited => cycle
		else{
			dfs_low[u] = min(dfs_low[u], dfs_num[v]);
			
		}
	}

}

int main(){
	int n,m;
	cin >> n >> m;
	adj = VVI(n);
	dfs_low = dfs_num = parent = VI(n,-1);
	articulation = VI(n,0);
	
	for(int i = 0; i < m; ++i){
		int x,y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	for (int i = 0; i < n; ++i){
		
		if (dfs_num[i] == -1) {
			dfsroot = i;
			rootchildren = 0;
			dfs(i);
			articulation[dfsroot] = (rootchildren > 1);
		}
	}
	//print
	
	
}
