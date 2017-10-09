#include <bits/stdc++.h>
using namespace std;

//returns det if matrix has full rank
double Gauss(vector<vector<double>>& a, vector<double>& b, vector<double>& ans) {
    double det = 1;
	int n = a.size();
	for(int i = 0; i < n; ++i){
		int x = i;
		for(int j = i + 1; j < n; ++j){
            if (fabs(a[j][i]) > fabs(a[x][i])) x = j;
        }
		if (i != x) swap(b[i], b[x]), swap(a[i], a[x]), det *= -1;
        if(a[i][i] == 0) return 0;
        det *= a[i][i];
		for(int j = i + 1; j < n; ++j) {
			double v = a[j][i] / a[i][i];
			if (v != 0) {
                b[j] -= v * b[i];
                for(int k = i + 1; k < n; ++k){
                    a[j][k] -= v * a[i][k];
                }
            }
		}
	}
    for(int i = n-1; i >= 0; --i){
        ans[i] = b[i];
        for(int j = n-1; j > i; --j){
            ans[i] -= ans[j]*a[i][j];
        }
        ans[i] /= a[i][i];
    }
    return det;
}
