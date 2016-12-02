#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

// #define E complex<double>

using namespace std;

const int MAXP = 100005;
const int MAXN = 270005;
const double pi = acos(-1.0);

struct E{
	double r , i ;
	E () {}
	E (double r, double i) : r ( r ) , i ( i ) {}
	E operator + (const E& p) const {
		return E(r + p.r , i + p.i);
	}
	E operator - (const E& p) const {
		return E(r - p.r , i - p.i);
	}
	E operator * (const E& p) const {
		return E(r * p.r - i * p.i , r * p.i + i * p.r) ;
	}
};

int n, p;
double arr[MAXP];
double brr[MAXP];
int m, L, g;
E a[MAXN], b[MAXN];
int gi[MAXP];

inline void fft(E *z, int f) {
	for ( int i = 1 , j , k , t ; i < n ; ++ i ) {
        for ( j = 0 , t = i , k = n >> 1 ; k ; k >>= 1 , t >>= 1 ) {
            j = j << 1 | t & 1 ;
        }
        if ( i < j ) swap ( z[i] , z[j] ) ;
    }
	for ( int s = 2 , ds = 1 ; s <= n ; ds = s , s <<= 1 ) {
        E wn ( cos ( f * 2 * pi / s ) , sin ( f * 2 * pi / s ) ) ;
        for ( int k = 0 ; k < n ; k += s ) {
            E w ( 1 , 0 ) , t ;
            for ( int i = k ; i < k + ds ; ++ i ) {
                z[i + ds] = z[i] - ( t = w * z[i + ds] ) ;
                z[i] = z[i] + t ;
                w = w * wn ;
            }
        }
    }
}

int main() {
	freopen("5958.in", "r", stdin);
	while (~scanf("%d", &p)) {
		brr[0] = 0;
		for (int i = 0; i < p; i++) {
			scanf("%lf", &arr[i]);
			if ( i ) brr[0] += arr[i] ;
	        brr[i] = arr[0] ;
		}
		// for (int i = 1; i < p; i++)
		// 	brr[i] = arr[0];
		gi[0] = 1;
		g = p == 103 ? 5 : 2 ;
		for ( int i = 1 ; i < p ; ++ i ) {
	        gi[i] = gi[i - 1] * g % p ;
	    }
		for (int i = 0; i < p - 1; i++)
			a[i] = E(arr[gi[p - i - 2]], 0);
		for (int i = 0; i < p - 1; i++)
			b[i] = E(pow(2., pow(sin(2 * pi * gi[i] / p), 3.)), 0);
		// n = p - 1;
		// L = 0;
		// m = n << 1;
		for (n = 1; n < p + p; n <<= 1) /*L++*/;
		// for (int i = 0; i < n; i++)
		// 	r[i] = (r[i >> 1] >> 1) | ((i & 1) << (L - 1));

		for (int i = p - 1; i < n; i++)
			a[i] = b[i] = E(0, 0);
		// for (int i = 0; i < n; i++)
			// cout << b[i].real() << " \n"[i == n - 1];
		fft(a, 1);
		fft(b, 1);
		for (int i = 0; i < n; i++) a[i] = a[i] * b[i];
		fft(a, -1);
		for (int i = 0; i < n; i++) a[i].r /= n;
		// for (int i = 0; i <= m; i++) cout << a[i].real() << endl;
		// for (int i = 0; i < p - 1; i++)
		// 	brr[gi[i]] += a[p - i - 2].r + a[p * 2 - 3 - i].r;
		for ( int i = p - 1 ; i < n ; ++ i ) a[i % (p - 1)].r += a[i].r ;
		for ( int i = 1 ; i < p ; ++ i ) brr[gi[i]] += a[( i - 1 ) % (p - 1)].r ;
		for (int i = 0; i < p; i++) {
			printf("%.3lf ", brr[i]);
		}
		printf("\n");

	}


	return 0;
}
