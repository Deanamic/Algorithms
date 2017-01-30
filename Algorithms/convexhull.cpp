#include <bits/stdc++.h>
using namespace std;

/*
 * Convex hull
 * Nos devuelve un vector de puntos que forman la convex hull
 * Complejidad O(nlogn) : O(nlogn) ordenar, O(n) crear la convex hull
 */

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

int query(punto p){ //checks if a point lies within the convexhull O(logn)
	int l = 0, r = half;
	while (l + 1 < r){
		int m = (l+r)/2;
		if(H[m].x >= p.x) r = m;
		else l = m;
	}
	if(H[l].x > p.x or l == half) return 0;
	if(cross(H[l], p, H[l+1]) > 0) return 0;
	l = half-1;
	r = H.size();
	while (l + 1 < r){
		int m = (l+r)/2;
		if(H[m].x <= p.x) r = m;
		else l = m;
	}
	if(H[l].x < p.x or l == H.size()-1) return 0;
	if(cross(H[l], p, H[l+1]) <= 0) return 1;
	return 0;
}
