#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define POS(X,Y) *X.find_by_order(Y)
#define ORD(X,Y) X.order_of_key(Y)
/* 
 * tree actua como un set pero con dos funciones extra
 * find_by_order() que devuelve un iterador al elemento k-esimo
 * 
 * order_of_key() que devuelve el numero de elementos mas pequeños
 * estrictos que X
 * 
 * Complejidad:
 * 	-insert 				O(logn)
 * 	-erase 					O(logn)
 * 	-findbyorder 			O(logn)
 * 	-orderofkey	 			O(logn)
 * 	-iterate thourgh set 	O(n)
*/

int main(){
}
