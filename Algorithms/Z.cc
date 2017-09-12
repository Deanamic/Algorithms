#include <bits/stdc++.h>
using namespace std;

/*
 * Z-Algorithm, the i-th position of the vector saves the length
 * of the longest suffix ending at the i-th position equal to
 * the prefix of the string
 * O(n)
 */

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    int L, R;
    L = R = 0;
    vector<int> Z(n, 0);
    for (int i = 1; i < n; ++i){
        if (i < R) Z[i] = min(Z[i-L], R-i);
        else Z[i] = 0;

        while (Z[i] + i < n and s[Z[i]] == s[i+Z[i]]) ++Z[i];
        if (i+Z[i] > R){
            L = i;
            R = i + Z[i];
        }
    }
    cout << endl;
}
