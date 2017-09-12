#include<bits/stdc++.h>
using namespace std;

//Checked at http://codeforces.com/problemset/gymProblem/101398

const int MAXN = 5000;
stack<int> st;
int m[MAXN], comp[MAXN];
vector<int> adj[2][5000];
int c = 0;
int n;

void addedge(int u, int v) {
    adj[0][u].push_back(v);
    adj[1][v].push_back(u);
}

void dfs(int u, int t) {
    m[u] = 1;
    for(int v : adj[t][u]) if(!m[v]) dfs(v,t);
    if(t) comp[u] = c;
    else st.push(u);
}

void kosaraju(int n) {
    memset(m, 0, sizeof(m));
    for(int i = 0; i < n; ++i) if(!m[i]) dfs(i,0);
    memset(m, 0, sizeof(m));
    while(st.size()) {
        int u = st.top();
        st.pop();
        if(!m[u]) dfs(u,1), c++;
    }
}

int main() {
    int n, m;
    while(cin >> n >> m) {
        for(int i = 0; i < 2*n; ++i){
            adj[0][i] = adj[1][i] = vector<int>();
        }
        for(int i = 0; i < m; ++i){
            int x, y;
            cin >> x >> y;
            x = ((abs(x) << 1) | (x < 0)) - 2;
            y = ((abs(y) << 1) | (y < 0)) - 2;
            addedge(x^1, y);
            addedge(y^1, x);
        }
        kosaraju(2*n);
        int can = comp[0] > comp[1];
        for(int i = 0; i < 2*n; i+=2){
            if(comp[i] == comp[i|1]) can = 0;
        }
        if(can) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
