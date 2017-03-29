#include <bits/stdc++.h>
using namespace std;

int main() {
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i){
        vector<int> V;
        int n;
        cin >> n;
        while (n--) {
            int x;
            cin >> x;
            //LIS ALGORITHM
            int i = lower_bound(V.begin(), V.end(), x) - V.begin();
            if (i < (int)V.size()){
                if (x < V[i]) V[i] = x;
            }
            else V.push_back(x);
        }
        cout << V.size() << endl;
    }
}
