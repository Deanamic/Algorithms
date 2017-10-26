#include <bits/stdc++.h>
using namespace std;

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

//returns de eulerian cycle starting at u, cycle is in reverse order
void find_cycle(int u){
    while(nxt[u] < adj[u].size()){
        int go = adj[u][nxt[u]++];
        if(!E[go].used){
            E[go].used = 1;
            int to = (E[go].u ^ E[go].v ^ u);
            find_cycle(to);
        }
    }
    cycle.push_back(u);
}

//directed graph
vector<int> next; //stores last visited vertex index
vector<vector<int>> adj;
vector<int> cycle;

//returns the eulerian cycle with reverse order
void find_cycle(int u){
    while(next[u] < adj[u].size())
        find_cycle(adj[u][next[u]++]);
    cycle.push_back(u);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
}
