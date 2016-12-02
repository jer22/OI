#include <bits/stdc++.h>
using namespace std ;

typedef long long LL ;
typedef pair < int , int > pii ;
typedef pair < LL , int > pli ;

#define clr( a , x ) memset ( a , x , sizeof a )

const int MAXN = 300005 ;
const double pi = acos ( -1.0 ) ;

struct P {
    double r , i ;
    P () {}
    P ( double r , double i ) : r ( r ) , i ( i ) {}
    P operator + ( const P& p ) const {
        return P ( r + p.r , i + p.i ) ;
    }
    P operator - ( const P& p ) const {
        return P ( r - p.r , i - p.i ) ;
    }
    P operator * ( const P& p ) const {
        return P ( r * p.r - i * p.i , r * p.i + i * p.r ) ;
    }
} ;

P x1[MAXN] , x2[MAXN] ;
double a[MAXN] , b[MAXN] ;
int g[MAXN] ;
int mod , p ;

void DFT ( P y[] , int n , int rev ) {
    for ( int i = 1 , j , k , t ; i < n ; ++ i ) {
        for ( j = 0 , t = i , k = n >> 1 ; k ; k >>= 1 , t >>= 1 ) {
            j = j << 1 | t & 1 ;
        }
        if ( i < j ) swap ( y[i] , y[j] ) ;
    }
    for ( int s = 2 , ds = 1 ; s <= n ; ds = s , s <<= 1 ) {
        P wn ( cos ( rev * 2 * pi / s ) , sin ( rev * 2 * pi / s ) ) ;
        for ( int k = 0 ; k < n ; k += s ) {
            P w ( 1 , 0 ) , t ;
            for ( int i = k ; i < k + ds ; ++ i ) {
                y[i + ds] = y[i] - ( t = w * y[i + ds] ) ;
                y[i] = y[i] + t ;
                w = w * wn ;
            }
        }
    }
}

void FFT ( P x1[] , P x2[] , int n ) {
    DFT ( x1 , n , 1 ) ;
    DFT ( x2 , n , 1 ) ;
    for ( int i = 0 ; i < n ; ++ i ) {
        x1[i] = x1[i] * x2[i] ;
    }
    DFT ( x1 , n , -1 ) ;
    for ( int i = 0 ; i < n ; ++ i ) {
        x1[i].r /= n ;
    }
}

void solve () {
    int x = mod == 103 ? 5 : 2 ;
    p = mod - 1 ;
    g[0] = 1 ;
    b[0] = 0 ;
    for ( int i = 1 ; i < mod ; ++ i ) {
        g[i] = g[i - 1] * x % mod ;
    }
    for ( int i = 0 ; i < mod ; ++ i ) {
        scanf ( "%lf" , &a[i] ) ;
        if ( i ) b[0] += a[i] ;
        b[i] = a[0] ;
    }
    int n = 1 ;
    while ( n < mod + mod ) n <<= 1 ;
    for ( int i = 0 ; i < p ; ++ i ) {
        x1[i] = P ( a[g[p - 1 - i]] , 0 ) ;
        x2[i] = P ( pow ( 2.0 , pow ( sin ( 2 * pi * g[i] / mod ) , 3.0 ) ) , 0 ) ;
    }
    for ( int i = p ; i < n ; ++ i ) x1[i] = x2[i] = P ( 0 , 0 ) ;
    FFT ( x1 , x2 , n ) ;
    for ( int i = p ; i < n ; ++ i ) x1[i % p].r += x1[i].r ;
    for ( int i = 1 ; i < mod ; ++ i ) b[g[i]] += x1[( i - 1 ) % p].r ;//( i - 1 ) % p = ( i - 2 + mod ) % p
    for ( int i = 0 ; i < mod ; ++ i ) printf ( "%.3f " , b[i] ) ;
    puts ( "" ) ;
}

int main () {
    freopen("5958.in", "r", stdin);
    while ( ~scanf ( "%d" , &mod ) ) solve () ;
    return 0 ;
}