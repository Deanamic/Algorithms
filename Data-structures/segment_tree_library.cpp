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
/*
 * Segment Tree Library
 * Es una estructura de datos que almacena datos y facilita el acceso 
 * a intervalos. (la suma, el minimo, el maximo etc.
 * 
 * Tiene Complejidad O(nlogn) su construccion y O(logn) buscar informacion
*/

vector <int> v;
vector <int> s;
void build(int id,int left, int right){ //inicializado a 1, 0, n-1
	if(left == right){	//	intervalo cerrado cerrado
		s[id] = v[left];
		return;
	}
	int mid = (left + right)/2;
	//construimos los hijos recursivamente
	build(id * 2, left, mid);
	build(id * 2 + 1, mid + 1, right);
	s[id] = s[id*2] + s[id*2 + 1];
}

int find(int id,int left, int right, int x, int y){
	if(left > y or right < x){
		//el intervalo en el que no movemos esta fuera del que buscamos
		return 0;
	}
	if(left >= x and right <= y){
		//estamos dentro del intervalo
		return s[id];
	}
	//si estamos parcialmente en el intervalo bajamos por el arbol
	int mid = (left + right)/2;
	return find(2*id, left, mid, x, y) + find(2*id+1,mid + 1, right, x, y);
}
