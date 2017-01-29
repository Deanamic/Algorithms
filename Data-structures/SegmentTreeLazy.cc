#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int v[1000000], seg[4000000];                       // v es l'array base i seg el vector segment tree;
int n;
int lazy[4000000];                                  // array on guardo els canvis que encara s'han de fer

void build(int x, int y, int node) {                // constructor: x, y = interval en el que estic; node = node en el que estic
    if (x == y) seg[node] = v[x];                   // si x == y estic a una fulla => en aquest node el valor es el de l'array base
    else {
        build (x, (x+y)/2, 2*node);                 // contrueixo el subarbre que surt d'aquest node i poso a seg[node] el maxim del subarbre
        build ((x+y)/2 + 1, y, 2*node + 1);
        seg[node] = max (seg[2*node], seg[2*node + 1]);
    }
}

int query(int a, int b, int x, int y, int node) {   // buscador de maxim: a i b es l'interval que busco; x i y es en el que estic
    if (lazy[node] != 0) {
        seg[node] += lazy[node];
        if (x != y) {
            lazy[2*node] += lazy[node];             // Lazy propagation
            lazy[2*node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (a <= x and b >= y) return seg[node];        // si en el que estic esta inclos en el que busco, en retorno el maxim
    if (b < x or a > y) return 0;                   // si en el que estic es disjunt del que busco, retorno 0
    return max (query(a, b, x, (x+y)/2, 2*node), query(a, b, (x+y)/2 + 1, y, 2*node+1)); // si no es cap de les interiors (vol dir que esta mig inclos,
    // crido al subarbre
}

void updateinterval (int a, int b, int x, int y, int diff, int node) { // preparador lazy: a i b es el que busco, x i y es en el que estic
    if (lazy[node] != 0) {
        seg[node] += lazy[node];
        if (x != y) {
            lazy[2*node] += lazy[node];
            lazy[2*node + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
    if (a <= x and y<= b) {                  // si en el que estic esta inclos en el que busco, l'actualitzo i afegeixo lazy als fills
        seg[node] += diff;
        if (x != y) {
            lazy[2*node] += diff;
            lazy[2*node + 1] += diff;
        }
        return;
    }
    if (b < x or a > y) return;             // si son disjunts no faig res
    updateinterval (a, b, x, (x+y)/2, diff, 2*node);        // si encara no ha fet res => esta inclos parcialment => actualitzo
    updateinterval (a, b, (x+y)/2 + 1, y, diff, 2*node + 1);// les branques i despres el node
    seg[node] = max (seg[2*node], seg[2*node + 1]);

}
int main() {
}
