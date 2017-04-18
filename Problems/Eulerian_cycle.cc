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

//undirected graph

struct edge{
    int u, v;
    bool used;
};

vector<edge> E;
vector<vector<int> > adj; //adj stores the index in E
vector<int> nxt;
vector<int> cycle;
int p;

void find_cycle(int u){
    while(nxt[u] < adj[u].size()){
        int go = adj[u][nxt[u]++];
        if(!E[go].used){
            E[go].used = 1;
            int to = (E[go].u ^ E[go].v ^ u);
            find_cycle(to);
        }
    }
    cycle[--p] = u;
}

//directed graph
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
