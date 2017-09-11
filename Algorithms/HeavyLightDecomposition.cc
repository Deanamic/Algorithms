#include<bits/stdc++.h>
using namespace std;

/*************************************************************************************
Problem: Heavy-light decomposition, https://jutge.org/problems/P53018_en/statement
A Decomposition for graphs to make most operations O(logN)
**************************************************************************************/

struct Fenwick{
	int n; //Size of array
	vector<long long> tree;

	void Build(int m){ //Initializes the tree
		n = m;
		tree = vector<long long>(m+1,0);
	}

	long long read(int idx){ //Gives the sum [1,idx]
	    long long sum = 0;
		idx++;
	    while (idx > 0){
	        sum += tree[idx];
	        idx -= (idx & -idx);
	    }
	    return sum;
	}

	void update(int k ,long long val){ //Increases the k-th value
		k++;
	    while (k <= n){
	        tree[k] += val;
	        k += (k & -k);
	    }
	}
};

struct node{
    int id;
    vector<int> adj;
    int sz;
    int head = -1;
    long long w = 0;
    int p = -1;
    int par;
    Fenwick F;
    void push_back(int x) {
        adj.push_back(x);
        return;
    }

    void Build() {
        F.Build(sz);
    }

    void update(long long _id, long long _w) {
        F.update(_id, _w);
    }

    long long read(int idx) {
        return F.read(idx);
    }

};

vector<node> Node;

struct edge{
    int u, v;
    long long w;
    inline int getEdge(int x) {
        return u^v^x;
    }
}E[10010];

int dfs(int u, int p) {
    Node[u].sz = 1;
    Node[u].p = Node[p].p + 1;
    Node[u].par = p;
    for(int i : Node[u].adj) {
        int v = E[i].getEdge(u);
        if(v != p) {
            Node[u].sz += dfs(v, u);
            Node[v].w = E[i].w;
        }
    }
    return Node[u].sz;
}

void HLD(int u, int p) {
    if(Node[u].head == -1) Node[u].head = u, Node[u].id = 0;
    for(int i : Node[u].adj) {
        int v = E[i].getEdge(u);
        if(v != p) {
            if(2*Node[v].sz > Node[u].sz) Node[v].head = Node[u].head, Node[v].id = Node[u].id + 1;
            HLD(v, u);
        }
    }
}

void getDist(int u, int p) {
    if(Node[u].head == u) {
        Node[u].Build();
    }
    Node[Node[u].head].update(Node[u].id, Node[u].w);
    for(int i : Node[u].adj) {
        int v = E[i].getEdge(u);
        if(v != p) getDist(v, u);
    }
}

void ChangeDist(int u, int v, long long w) {
    if(Node[u].p < Node[v].p) return ChangeDist(v, u, w);
    Node[Node[u].head].update(Node[u].id, -Node[u].w);
    Node[Node[u].head].update(Node[u].id, Node[u].w = w);
}

long long getAns(int u, int v) {
    long long ans = 0;
    while(Node[u].head != Node[v].head) {
        if(Node[Node[u].head].p > Node[Node[v].head].p){
            ans += Node[Node[u].head].read(Node[u].id);
            u = Node[Node[u].head].par;
        }
        else {
            ans += Node[Node[v].head].read(Node[v].id);
            v = Node[Node[v].head].par;
        }
    }
    if(Node[u].p > Node[v].p) {
        ans += Node[Node[u].head].read(Node[u].id);
        ans -= Node[Node[v].head].read(Node[v].id);
    }
    else {
        ans += Node[Node[v].head].read(Node[v].id);
        ans -= Node[Node[u].head].read(Node[u].id);
    }
    return ans;
}

void solve(int n, int m) {
    int l = 0;
    Node = vector<node>(n);
    for(int i = 0; i < n-1; ++i){
        int u,v,x;
        cin >> u >> v >> x;
        Node[u].push_back(l);
        Node[v].push_back(l);
        E[l++] = {u,v,x};
    }
    dfs(0,0);
    HLD(0,0);
    getDist(0,0);
    while(m--) {
        char c;
        cin >> c;
        if(c == 'q') {
            int u, v;
            cin >> u >> v;
            cout << getAns(u, v) << endl;
        }
        else {
            int u, v, w;
            cin >> u >> v >> w;
            ChangeDist(u, v, w);
        }
    }
    cout << endl;
}

int main(){
    int n, m;
    while(cin >> n >> m) solve(n, m);
}
