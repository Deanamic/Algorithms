#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<int> VI;
typedef vector<VI> VVI;
const LL INF = 1000000000000000000LL;
/*
 *maxflow, devuelve el maximo flujo que puede pasar por un grafo 
 *dirigido con pesos
 *complejidad O(V^2E)
*/

#define VEI(w,e) ((E[e].u == w) ? E[e].v : E[e].u) // 
#define CAP(w,e) ((E[e].u == w) ? E[e].cap - E[e].flow : E[e].flow)
#define ADD(w,e,f) E[e].flow += ((E[e].u == w) ? (f) : (-(f)))

struct Aristas {
    int u, v; //que dos nodos conecta
    LL cap, flow; //cuanto flujo puede pasar, cuanto flujo esta pasando
};

VI d, act;
VVI adj;
vector<Aristas> E;

bool bfs(int s, int t) { //mira que podemos ir de t a s
    queue<int> Q;
    d = VI(adj.size(), -1); //iniciamos el vector a -1
    d[t] = 0; //el lugar donde vamos es 0
    Q.push(t);
    while (not Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = 0; i < adj[u].size(); ++i) {
            int e = adj[u][i], v = VEI(u, e); //vamos de u a v
            if (CAP(v, e) > 0 and d[v] == -1) { //si podemos pasar agua de u a v, y no hemos pasado por v
                d[v] = d[u] + 1; //d[i] es la distancia a t
                Q.push(v);
            }
        }
    }
    return d[s] >= 0; //miramos si podemos llegar hasta s
}

LL dfs(int u, int t, LL bot) {
    if (u == t) return bot; //hemos llegado al final
    for (; act[u] < adj[u].size(); ++act[u]) { 
        int e = adj[u][act[u]]; //cogemos los nodos donde puede ir
        if (CAP(u, e) > 0 and d[u] == d[VEI(u, e)] + 1) { //si podemos pasar agua por la direccion escogida y el bfs ha pasado por donde vamos
            LL inc = dfs(VEI(u, e), t, min(bot, CAP(u, e))); //hacemos el dfs de donde hemos llegado, miramos el maxiomo de agua
            if (inc) {
                ADD(u, e, inc); //si podemos pasar agua, pasamos agua y actualizamos el valor en el nodo
                return inc;
            }
        }
    }
    return 0;
}

//S es el Source, t es el Sink
LL maxflow(int s, int t) { //en la fila del node, guardem no els nodes on conecta, sino quines arestes passan per ella 
    for (int i = 0; i < E.size(); ++i) E[i].flow = 0; //inicializamos el flow de todos en 0
    LL flow = 0, bot;
    while (bfs(s, t)) { //hacemos un bfs de source hasta la salida, con una matriz/lista? de adyancentes y vector de nodos
        act = VI(adj.size(), 0); //el vector act es un vector inicializado en 0, de el numero de nodos
        while ((bot = dfs(s, t, INF))) flow += bot; //sumamos el agua posible
    } 
    return flow;
}
