#include <bits/stdc++.h>
using namespace std;

/*
FFT:
    Given 2 polynomials we will multiply them with O(nlogn) complexity instead of O(n<sup>2</sup>)
    We will achieve this using properties of complex numbers, in particular the roots 1.
    The idea is that any collection of n+1 points define one and only 1 n degree polynomial.
*/

inline int rev (int num, int lg_n) {
    int res = 0;
    for (int i=0; i<lg_n; ++i)
        if (num & (1<<i))
            res |= 1<<(lg_n-1-i);
    return res;
}

void fft (vector<complex<double>> & a, bool invert) {
    int n = (int) a.size();
    int lg_n = 0;
    while ((1 << lg_n) < n)  ++lg_n;

    for (int i=0; i<n; ++i) {
        if (i < rev(i,lg_n)) {
            swap (a[i], a[rev(i,lg_n)]);
        }
    }

    for (int len=2; len<=n; len<<=1) {
        double ang = 2*M_PI/len * (invert ? -1 : 1);
        complex<double> wlen (cos(ang), sin(ang));
        for (int i=0; i<n; i+=len) {
            complex<double> w (1);
            for (int j=0; j<len/2; ++j) {
                complex<double> u = a[i+j],  v = a[i+j+len/2] * w;
                a[i+j] = u + v;
                a[i+j+len/2] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        for (int i=0; i<n; ++i) {
            a[i] /= n;
        }
    }
}

vector<int> multiply (const vector<int> & a, const vector<int> & b) {
    vector<complex<double>> fa (a.begin(), a.end()),  fb (b.begin(), b.end());
    size_t n = 1;
    while (n < max (a.size(), b.size()))  n <<= 1;
    n <<= 1;
    fa.resize (n),  fb.resize (n);
    vector<int> res;
    fft (fa, false),  fft (fb, false);
    for (size_t i=0; i<n; ++i)
        fa[i] *= fb[i];
    fft (fa, true);

    res.resize(n);
    for (size_t i=0; i<n; ++i)
        res[i] = int (fa[i].real() + 0.5);
    return res;
}


int main() {
    int n;
    cin >> n;
    vector<int> p1(n),p2(n);
    for(int i = 0; i < n; ++i){
        cin >> p1[i];
    }
    for(int i = 0; i < n; ++i){
        cin >> p2[i];
    }
    auto ans = multiply(p1,p2);
    for(int i : ans) cout << i << ' ';
    cout << endl;
}
