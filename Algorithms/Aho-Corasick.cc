#include <bits/stdc++.h>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
typedef long double LD;

#define FOR(i,n) for(int i=0;i<n;++i)
#define DEBUG(X) cerr<<#X<<' '<<X<<endl

//#define endl '\n'

int CUR = 1;

struct node{
    char val;
    int next1, next0;
    int pare;
    bool end;
};


vector<node> TRIE;
vector<int> sufl;
vector<vector<int>> g;
vector<int> v;

int suf(int p);

int go(int p, char c){
    int s = c - '0';
    if(g[s][p] != -1) return g[s][p];
    if(s == 0){
        if(TRIE[p].next0 != 0) return g[s][p] = TRIE[p].next0;
        if(p == 0 and TRIE[p].next0 == 0) return g[s][p] = 0;
        return g[s][p] = go(suf(p), c);
    }
    else {
        if(TRIE[p].next1 != 0) return g[s][p] = TRIE[p].next1;
        if(p == 0 and TRIE[p].next1 == 0) return g[s][p] = 0;
        return g[s][p] = go(suf(p), c);
    }
}

int suf(int p){
    if(sufl[p] != -1) return sufl[p];
    if(p == 0) return sufl[p] = 0;
    if(TRIE[p].pare == 0) return sufl[p] = 0;
    return sufl[p] = go(suf(TRIE[p].pare),TRIE[p].val);
}

bool dfs_cycle(int x, int p){
    if(v[x] == 2) return true;
    v[x] = 2;
    for(int i = 0; i < 2; ++i){
        if(v[g[i][x]] != 1 and !TRIE[g[i][x]].end){
            if (dfs_cycle(g[i][x],x)) return true;
        }
    }
    v[x] = 1;
    return false;
}

void addTRIE(string& s){
    int pos = 0;
    for(int i = 0; i < (int)s.size(); ++i){
        if(s[i] == '0'){
            if(TRIE[pos].next0 == 0){
                TRIE.push_back({s[i],0,0,pos,0});
                TRIE[pos].next0 = (pos = CUR++);
            }
            else{
                pos = TRIE[pos].next0;
            }
        }
        else{
            if(TRIE[pos].next1 == 0){
                TRIE.push_back({s[i],0,0,pos,0});
                TRIE[pos].next1 = pos = CUR++;
            }
            else{
                pos = TRIE[pos].next1;
            }
        }
    }
    TRIE[pos].end = 1;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    TRIE.push_back({'&',0,0,0,0});
    while(n--){
        string s;
        cin >> s;
        addTRIE(s);
    }
    sufl.resize(CUR,-1);
    g.resize(2,vector<int> (CUR,-1));
    queue<int> q;
    q.push(0);
    vector<int> vis(CUR,-1);
    v.resize(CUR,0);
    while(q.size()){
        int p = q.front(); q.pop();
	TRIE[p].end |= TRIE[suf(p)].end;
	if(!TRIE[p].end){
	    if(vis[p] == -1){
		vis[p] = 1;
		q.push(go(p,'0'));
		q.push(go(p,'1'));
	    }
	}
	else v[p] = 1;
    }
    if(dfs_cycle(0,-1)) cout << "YES" << endl;
    else cout << "NO" << endl;
}
