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
 * Convex hull
 * Nos devuelve un vector de puntos que forman la convex hull
 * Complejidad O(nlogn) : O(nlogn) ordenar, O(n) crear la convex hull
 */

typedef double double;   // coordinate type
typedef double double;  // must be big enough to hold 2*max(|coordinate|)^2
vector<punto> H;
vector<punto> P

struct punto {
	double x, y;
	bool operator <(const punto &p) const {
		return (x < p.x or (x == p.x and y < p.y));
	}
};

// Producto vectorial
// mayor que 0 si el giro es horario, igual 0 si es colinear, 
// menor que 0 si es antihorario
double cross(const punto &O, const punto &A, const punto &B) {
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Devuelve la lista en sentido antihorario
// El ultimo punto es igual al primero
void convex_hull() {
	int n = P.size(), k = 0;
	H = vector<punto> (2*n);

	// ordenamos los puntos
	sort(P.begin(), P.end());

	// construimos la convexhull inferior
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// construimos la convexhull superior
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	H.resize(k-1);
}
