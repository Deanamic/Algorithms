#include <bits/stdc++.h>
using namespace std;

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

vector<vector<int>> adj;
const int oo = 1e9;
void FloydWarshall(int n){
	for(int k = 0; k < n; ++k){
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
			}
		}
	}
}

int main(){
	int a,b,c,n,m;
	cin >> n >> m;
	adj = vector<vector<int>>(n,vector<int>(n,oo));
	for(int i = 0; i < m; ++i){
		cin >> a >> b >> c;
		adj[a][b] = c; //dirigido
	}
	FloydWarshall(n);
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			cout << adj[i][j] <<' ';
		}
		cout << '\n';
	}

}
