#include <bits/stdc++.h>
using namespace std;

/*
 *kruskal,MST. Devuelve el arbol generador con minimo peso
 *Complejidad O(E log E)
 *merge find set, si la posicion no esta cambiada es su propio padre,
 *sino asigna a este el padre de su padre.
*/

vector<int> p;
inline int mfset(int x){
    return (p[x] == -1 ?  x : p[x] = mfset(p[x]));
}

struct edge{
	int u,v,w;
	bool operator <(const edge& E) const {
		return w > E.w;
	}
};

int main(){
	int n, m;
    cin >> n >> m;
	priority_queue<edge> pq;
	p = vector<int> (n,-1);
	for (int i = 0; i < m; ++i){
		int u, v, w;
		cin >> u >> v >> w;
		pq.push({u,v,w});
	}
	long long sum = 0;
	int vertex = 1;
	while (vertex < n){ //en un MST hay n-1 aristas
		int w = pq.top().w;
		int u = pq.top().u;
		int v = pq.top().v;
		pq.pop(); //iniciamos en el camino con menos  peso
		if((mfset(u) != mfset(v))){ //si tienen el mismo padre no lo contamos
			sum += w;	//añadimos el peso
			++vertex;			//sumamos al numero de vertices
			p[mfset(u)] = mfset(v); //asignamos al padre de uno el padre de uno.
		}
	}
	cout << sum << '\n';
}
