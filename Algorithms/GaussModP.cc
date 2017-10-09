#include <bits/stdc++.h>
using namespace std;

const long long mod = 7;

long long binpow(long long a, long long k) {
    long long ans = 1;
    while(k > 0) {
        if(k & 1) {
            ans *= a;
        }
        k >>= 1;
        a *= a;
        a %= mod;
        ans %= mod;
    }
    return ans;
}

long long inv(long long a) {
    return binpow(a, mod - 2);
}

long long Gauss(vector<vector<long long>>& a, vector<long long>& b, vector<long long>& ans) {
	int n = a.size();
    long long det = 1;
    for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j){
			while (a[j][i] != 0) { // gcd step
				long long t = a[i][i] / a[j][i];
				if (t) {
                    b[i] = (b[i] - b[j] * t) % mod;
                    for(int k = i; k < n; ++k){
    					a[i][k] = (a[i][k] - a[j][k] * t) % mod;
                    }
                }
                swap(b[i], b[j]);
				swap(a[i], a[j]);
				det *= -1;
			}
		}
		det = det * a[i][i] % mod;
		if (!det) return 0;
	}

    for(int i = n-1; i >= 0; --i){
        ans[i] = b[i]%mod;
        for(int j = n-1; j > i; --j){
            ans[i] = (ans[i] - ans[j]*a[i][j])%mod;
        }
        ans[i] = ((ans[i]*inv(a[i][i]))%mod + mod)%mod;
    }
	return (det + mod) % mod;
}


int main() {
    int n;
    while(cin >> n) {
        vector<vector<long long>> v(n, vector<long long> (n));
        vector<long long> b(n), ans(n);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cin >> v[i][j];
            }
        }
        for(int i = 0; i < n; ++i){
            cin >> b[i];
        }
        if(Gauss(v, b, ans)) {
            for(auto i : ans) cout << i << ' ';
            cout << endl;
        }
    }
}
