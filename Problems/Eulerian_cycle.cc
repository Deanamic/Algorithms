#include <bits/stdc++.h>
using namespace std;

/*
Given a connected undirected graph
There exists an Eulerian cycle iff all vertices have an even degree
There exists an Eulerian tour iff all but 2 vertices have an even degree

Given a connected directed Graph
There exists an Eulerian cycle iff all vertices have the same number of entering and exiting edges
There exists an Eulerian tour iff all vertices but 2 have the same entering and exiting edges and the other 2 have a |difference| of 1.

*/
vector<int> next; //stores last visited vertex index
vector<vector<int>> adj(n);
vector<int> cycle(m);
int p = m; //m is the number of edges 

void find_cycle(int u){
    while(next[u] <= adj[u].size())
        find_cycle(adj[u][next[u]++]);
    cycle[p--] = u;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
