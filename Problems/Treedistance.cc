#include <bits/stdc++.h>
using namespace std;

// instead of computing the sum of distances from one edge to another we will
// count how many times an edge appears.
// We can see fvfry edge will appear sv*(n-sv) times
// Where n is the number of vertex

long long n;
vector<vector<int> > adj;

int dfs(int node, int par){
  long long f = 1;
  for(int i = 0; i < adj[node].size(); ++i){
    if(adj[node][i] != par){
      f += dfs(adj[node][i], par);
    }
  }
  ans += f*(n-f);
  return f;
}

int main(){
  int n;
  cin >> n;
  for(int i = 0; i < n-1; ++i){
    int x,y;
    cin >> x >> y;
    --x; --y;
    adj[x].push_back(y);
    adj[y].push_back(x);
  }
  dfs(0,0);
  cout << ans << endl;
}
  
