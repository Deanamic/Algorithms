#include<bits/stdc++.h>
using namespace std;

const int MAXN = 100010;
stack<int> st;
int m[MAXN], comp[MAXN];
vector<int> adj[2][MAXN];
int c = 0;
int n;

/* Kosaraju algorithm finds SCC
    we will first do a dfs and add the visited edges in postorder
    Observations:
        - if there is a path from u to v and v to u, the order in the stack is unknown
        - if there is a only path from u to v, u will be pushed to the stack later than v.

    Then, we will perform dfs with reverse edges from the top of the stack. Let u be the vertex on
    top of the stack. We know that any vertex v in the stack reachable from u with reverse edges means
    there is a path from v to u, but due to the above observations there must also be a path from u to v.
    hence they must be in the same SCC.

    More over the components will from a DAG, and it will be given in toplogical order.
    To solve the 2-sat promblem we simply have to go in reverse of the component number.
    Complexity O(m + n)
*/

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
