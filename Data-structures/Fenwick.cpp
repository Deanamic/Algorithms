#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef vector<LL> VI;
typedef vector<VI> VVI;
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


/*Fenwick tree
 * El Fenwick tree es una estructura para calcular y manipular "prefix sums"
 * apartir de una estructura de arbol binario
 * Puedes consultar:
 * -la suma de [1,b] --> suma de [a,b] esta indexado en 1
 * -puedes aumentar el valor k-esimo
 * -puedes multiplicar todos los elementos por k
 * Complejidad O(logn) para consultar y actualizar
 * Complejidad O(N) multiplicar
 */

int read(int idx){ //da la suma de frecuencias de [1,a]
    int sum = 0;
    while (idx > 0){
        sum += tree[idx];
        idx -= (idx & -idx);
    }
    return sum;
}


void update(int idx ,int val, int n){ //aumenta del valor k-esimo
    while (idx <= n){
        tree[idx] += val;
        idx += (idx & -idx);
    }
}

//para construirlo haremos un for(i,n) update(i,v[i],n)

