//C++ Template

#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
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
 * TRIE/prefix tree/radix tree
 * Es un arbol donde cada nodo es una subparte de el objeto almacenado
 * tal que en un recorrido podemos obtener el objeto inicial
 */

//http://codeforces.com/contest/706/problem/D
/*
 *Crearemos un trie tal que cada nodo es 1/0 para saber los numeros que
 *tenemos
 * cnt1 cnt0 diran cuantos 1/0 hay en el nodo
 * nxt1 nxt0 diran cual es el nodo hijo de cada nodo dependiendo de si mi
 * bit es 1/0
*/

struct nodo{
	int cnt1,cnt0;
	int nxt1, nxt0;
};

vector <nodo> TRIE(10000000,{0,0,0,0});
int last = 0;
int main(){
	int q;
	cin >> q;
	FOR(i,q){
		int x;
		char c;
		int start = 0; //TRIE[0] es la raiz
		cin >> c >> x;
		int aux = x;
		int bit[32];
			FOR(i,32){
				bit[i] = x % 2;
				x /= 2;
			}
		if (c == '+'){
			FOR2(i,31){
				if (bit[i]){
					++TRIE[start].cnt1;
					if (TRIE[start].nxt1 == 0){
						++last;
						TRIE[start].nxt1 = last;
					}
					start = TRIE[start].nxt1;
				}
				else {
					++TRIE[start].cnt0;
					if (TRIE[start].nxt0 == 0){
						++last;
						TRIE[start].nxt0 = last;
					}
					start = TRIE[start].nxt0;
				}

			}
		}
		else if (c == '-'){
			FOR2(i,31){
				if (bit[i]){
					--TRIE[start].cnt1;
					start = TRIE[start].nxt1;
				}
				else {
					--TRIE[start].cnt0;
					start = TRIE[start].nxt0;
				}
			}
		}
		else if (c == '?'){
			int ans = 0;
			FOR2(i,31){
				if (bit[i]){
					if (TRIE[start].cnt0 > 0) {
						ans += (1 << i);
						start = TRIE[start].nxt0;
					}
					else start = TRIE[start].nxt1;
				}
				else {
					if (TRIE[start].cnt1 > 0){
						ans += (1 << i);
						start = TRIE[start].nxt1;
					}
					else start = TRIE[start].nxt0;
				}
			}
			cout << max(aux,ans) << '\n';
		}
	}
}
