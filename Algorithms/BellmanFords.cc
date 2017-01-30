//C++ Template

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

//------------------------------------------------------------------
/*
 * Bellman-Ford es un algoritmo de SSSP que funciona en presencia de 
 * pesos negativos
*/

/*
 * tiene una complejidad de O(VE) con lista de adyancencia
 * O(V^3) con matriz de adyacencia
*/
VI dist;
struct edge{
	int to,weight;
};
vector<vector<edge> > adj;

void bellmanford(int V,int source){
	dist[source] = 0;
	FOR(i,V){
		FOR(j,V){
			FOR(k,SIZE(adj[j])){
				dist[adj[j][k].to] = min(dist[adj[j][k].to], dist[j]+adj[j][k].weight);
			}
		}
	}
}

bool checkcycle(int V){
	FOR(i,V){
		FOR(j,SIZE(adj[i])){
			if (dist[adj[i][j].to] > dist[i] + adj[i][j].weight)
				return true;
		}
	}
	return false;
}

int main(){
	int n,m,a,b,c;
	cin >> n >> m;
	adj = vector<vector<edge> >(n);
	FOR(i,m) {
		cin >> a >> b >> c;
		adj[a].PB(edge{b,c});
	}
	dist = VI(n,(5e8));
	bellmanford(n, 0);
	bool negativecycle = checkcycle(n);
	FOR(i,n) cout << dist[i] <<' ';
	cout << (negativecycle ? "yes" : "no") << endl;
}
