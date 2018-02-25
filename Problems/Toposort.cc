#include <bits/stdc++.h>
using namespace std;

/*
dfs and applications
*/

/*
Given an DAG, obtain a topological sort if it contains no cycles
We'll need an 
- visited vector
- outgoing edge list, adj
- result vector
We will return true in case it has cycles
*/

int pos = n;

bool Toposort(int u){
    vis[u] = 2;
    for(int i : adj[u]){
        if(vis[i] == 2) return true; 
        if(!vis[i]) Toposort(i);
    }
    vis[u] = 1;
    result[--pos] = u;
    return false;
}

int main(){


}
