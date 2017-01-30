#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef long long LL;
VI v;

/*
 *kruskal,MST. Devuelve el arbol generador con minimo peso
 *Complejidad O(E log E)
*/

/*
 *merge find set, si la posicion no esta cambiada es su propio padre, 
 *sino asigna a este el padre de su padre.
*/

int mfset(int x){ 
	
    if (v[x] == -1) return x;
    return v[x] = mfset(v[x]);
}

struct aresta{
	int nodo1, nodo2, peso;
}:

struct comp{
	bool operator()(aresta a,aresta b){
		return a.peso < b.peso;
	}
};


int main(){
    int a, b; //a es el numero de elementos, b el numero de arestas
    cin >> a >> b;
	priority_queue<aresta,vector <aresta>, comp> pq;
	v = VI(a,-1);//inicializamos un vector en -1 para la funcion mfset, indicara el padre de cada nodo
	for (int i = 0; i < b; ++i){
		aresta n;
		cin >> n.nodo1 >> n.nodo2 >> n.peso;
		pq.push(n);
	}
	LL sum = 0;
	int vertex = 1;
	while (vertex < a){ //en un MST hay n-1 aristas
		int peso = pq.top().peso;
		int n1 = pq.top().nodo1;
		int n2 = pq.top().nodo2;
		pq.pop(); //iniciamos en el camino con menos  peso 
		if((mfset(n1) != mfset(n2))){ //si tienen el mismo padre no lo contamos
			sum += peso;	//añadimos el peso
			++vertex;			//sumamos al numero de vertices
			v[mfset(n1)] = mfset(n2); //asignamos al padre de uno el padre de uno.
		}
	}
	cout << sum << '\n';
}
