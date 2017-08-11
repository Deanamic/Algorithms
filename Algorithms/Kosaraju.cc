#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
stack<int> st;
int m[MAXN], comp[MAXN];
int c = 0;
int n;

void dfs(int u, int t) {
    m[u] = 1;
    for(int v : adj[u]) if(!m[v]) dfs(v,t);
    if(t) comp[u] = c;
    else st.push(u);
}

void kosaraju() {
    memset(m, 0, sizeof(m));
    for(int i = 0; i < n; ++i) if(!m[i]) dfs(i,0);
    memset(m, 0, sizeof(m));
    while(st.size()) {
        int u = st.top();
        st.pop();
        if(!m[u]) dfs(u,1), c++;
    }
}
