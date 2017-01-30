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
 * Floyd-Warshall
 * devuelve el camino mas corto de todas los vertices a todos los
 * otros vertices
 * Complejidad O(V^3)
*/

/*
 * aplicaremos esta funcion sobre la matriz de adyacencia
 * complejidad de memoria O(V^2)
*/

VVI adj;
void floydwarshall(int V){
	FOR(i,V) {
		FOR(j,V){
			FOR(k,V){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
}

int main(){
	int a,b,c,n,m;
	cin >> n >> m;
	adj = VVI(n,VI(n,int(1e9)));
	FOR(i,m){
		cin >> a >> b >> c;
		adj[a][b] = c; //dirigido
	}
	floydwarshall(n);
	FOR(i,n){
		FOR(j,n){
			cout << adj[i][j] <<' ';
		}
		cout << '\n';
	}
	
}
