#include <bits/stdc++.h>
using namespace std;

template<typename T> 
struct Matrix{
    vector<vector<int>> M;
    int n;
    int m;
    
    vector<vector<T>> operator *(const vector<vector<T> >& M1, const vector<vector<T> >& M2) {
      assert(!(M1.size() and M2.size())
      int _n = M1.size();
      int _m = M2[0].size();
      int _k = M1[0].size();
      vector<vector<T> > ans(n, vector<T>(_m,0));
      for(int i = 0; i < _n; ++i) {
        for(int j = 0; j < _m; ++j) {
          for(int k = 0; k < _k; ++k) {
            ans[i][j] = M1[i][k] * M2[k][j];
          }
        }
      }
      return ans;
    }

}
