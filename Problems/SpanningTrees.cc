#include <bits/stdc++.h>
using namespace std;


long long Det(vector<vector<long long>>& a) {
    int n = a.size();
    long long ans = 1;
    for(int i = 0; i < n; ++i){
        for(int j = i+1; j < n; ++j){
            while(a[j][i] != 0) {
                long long t = a[i][i]/a[j][i];
                if(t) {
                    for(int k = i; k < n; ++k){
                        a[i][k] = (a[i][k] - a[j][k]*t);
                    }
                }
                swap(a[i], a[j]);
                ans *= -1;
            }
        }
        ans = ans * a[i][i];
        if(!ans) return ans;
    }
    return ans;

}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> adj(n-1, vector<long long> (n-1, 0));
    vector<int> sz(n, 0);
    for(int i = 0; i < m; ++i){
        int x, y;
        cin >> x >> y;
        --x, --y;
        if(max(x,y) != n-1) adj[x][y] = adj[y][x] = -1;
        ++sz[x];
        ++sz[y];
    }

    for(int i = 0; i < n-1; ++i){
        adj[i][i] = sz[i];
    }

    cout << Det(adj) << endl;
}
