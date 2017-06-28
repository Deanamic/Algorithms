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
/* El kmp es un algoritmo que nos da la longitud del prefijo mas largo 
 * repetido dentro del string hasta la posicion k
 * complejidad O(n)
 * 
*/

string a, b;
string s = a + '&' + b; //esto lo hacemos para encontrar prefijos de a (en particular todo a) en b asumiendo que ni a ni b contienen &
vector<int> vi(a.size() + 1);

void KMP(){
	vi[0] = -1;
	for(int i = 0; i < c-1; ++i){
		int j = vi[i];
		while(j > -1 and s[j] != s[i]) j = vi[j]; 
		vi[i + 1] = j + 1;
	}
}
