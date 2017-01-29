#include <bits/stdc++.h>
using namespace std;

using VI = vector<int>;
using VVI = vector<VI>;
const int INF = 1e9;

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
 
struct Fenwick{
	int n; //Size of array
	vector<int> tree;
	
	void Build(const vector<int>& v, int m){ //Initializes the tree
		n = m;
		tree = vector<int>(m+1,0);
		for(int i = 0; i < n; ++i){
			update(i,v[i]);
		}
	}
	
	int read(int idx){ //Gives the sum [1,idx]
	    int sum = 0;
		idx++;
	    while (idx > 0){
	        sum += tree[idx];
	        idx -= (idx & -idx);
	    }
	    return sum;
	}

	void update(int k ,int val){ //Increases the k-th value
		k++;
	    while (k <= n){
	        tree[k] += val;
	        k += (k & -k);
	    }
	}

	void scale(int c){ //multiplies all numbers by a c factor
    	for (int i = 1 ; i <= n ; i++)
        	tree[i] = tree[i] * c;
	}
};
