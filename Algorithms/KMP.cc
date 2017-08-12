#include <bits/stdc++.h>
using namespace std;

/* El kmp es un algoritmo que nos da la longitud del prefijo mas largo
 * repetido dentro del string hasta la posicion k
 * complejidad O(n)
*/

void KMP(string s){
	vector<int> v(s.size() + 1);
	v[0] = -1;
	for(size_t i = 0; i < v.size(); ++i){
		int j = v[i];
		while(j > -1 and s[j] != s[i]) j = v[j];
		v[i + 1] = j + 1;
	}
}
