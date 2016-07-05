#include <bits/stdc++.h>
using namespace std;

#define FOR1(x,y,z) for( int x = y; x < z ; ++x)
#define FOR(x,y) FOR1(x,0,y)
#define endl '\n'
#define mp(x,y) make_pair(x,y)
#define SIZE(X) ((int)(X).size())
typedef pair<int, int> II;
typedef vector<II> VII;
typedef vector<VII> VVII;
#define INF int(1e9)

/*
 *dijkstra, busca el camino minimo en un grafo con pesos y dirigidos
 *complexidad O(E+VlogV) 
*/

struct compare{ //estruct para que el priority queue ordene de pesos pequeños a mayores
	bool operator()(II a, II b){
		return a.second > b.second;
	}
};


int main(){
	int n,m;
	cin >> n >> m; //n es el numero de nodos, m el numero de caminos dirigidos
	VVII v(n); //creamos una lista de adyacencia con el pair <nodo que conecta, peso>
	FOR(i,m){
		int origen, destino,peso;
		cin >> origen >> destino >> peso;
		//--origen; --destino; si estuviese indexado a 1  
		v[origen].PB(mp(destino,peso)); //añadimos este camino a la lista
	}
	VI d(n,INF); //iniciamos un vector con caminos, la distancia es infinita si no hay arestas
	d[0] = 0; //ir al mismo sitio cuesta 0
	priority_queue <II,VII,compare> pq; //creamos la priority_queue ordenado de menos peso a mayor peso
	pq.push(mp(0,0)); //empezamos desde el 0
	while (not pq.empty()){ //mientras la cola no este vacia, puede haber un camino mas optimo
		II top = pq.top(); pq.pop(); //sacamos siempre el camino con menor valor
		int origen = top.first;
		FOR(i,SIZE(v[origen])){ //miramos que caminos podemos hacer desde este sitio
			int to = v[origen][i].first, peso = v[origen][i].second; //guardamos a donde vamos, y el peso de ese camino
			if (d[to] > d[origen] + peso){ //si podemos ir a una aresta, con menor ESTRICTO peso pasando por el nodo origen, cambiamos su peso, y reconsideramos el camino optimo 
				//sabiendo que existe una aresta tal que esta mas cerca de el inicio
				d[to] = d[origen] + peso; //asignamos el nuevo minimo
				pq.push(mp(to,d[to])); //metemos al vector esta nueva forma de llegar para recalcular
			}
		}
	} //cuando la cola se vacie significa que no existe ningun camino mas corto
	FOR1(i,1,n){ //imprimimos el camino minimo a cada sitio
		if (d[i] == int(1e9)) cout << "no";
		else cout << d[i];
		cout << endl;
	}
}
