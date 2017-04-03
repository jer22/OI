#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const double PI = 4 * atan(1.0);
const int MAXN = 400005;
const long long P = 998244353ll;
const long long G = 3ll;
long long mul(long long x, long long y) {
	return (x * y - (long long)(x / (long double)P * y + 1e-3) * P + P) % P;
}
long long qpow(long long x, long long k, long long p){
	long long ret = 1;
	while (k) {
		if (k & 1) ret = mul(ret, x);
		k >>= 1;
		x = mul(x, x);
	}
	return ret;
}
int len;
int rev[MAXN];
long long w[MAXN];
void set(){
    for(int i = 0; i < len; i++){
        int cur=0;
        for(int j=1,x=i;j<len;j<<=1,x>>=1)cur=(cur<<1)+(x&1);
        rev[i]=cur;
    }
    w[0]=1;w[1]=qpow(G,(P-1)/len, P);
    for(int i = 2; i <= len; i++)w[i]=mul(w[i-1], w[1])%P;
}
long long v[MAXN];
void dft(long long *y,int sig){
    for(int i=0; i < len; i++)v[rev[i]]=y[i];
    for(int i=2,tot=len,hal,cur;i<=len;i<<=1){
        tot>>=1,cur=sig?len:0,hal=i>>1;
        for(int j=0;j<hal;j++){
            for(int k=j,wi=w[cur];k<len;k+=i){
                long long u=v[k],r=mul(v[k+hal],wi)%P;
                v[k]=(u+r)%P;
                v[k+hal]=(u+P-r)%P;
            }
            sig?cur-=tot:cur+=tot;
        }
    }
    for(int i=0;i < len; i++)y[i]=v[i];
    if (sig == 1) {
		long long inv = qpow(len, P - 2, P);
		for (int i = 0; i < len; i++) y[i] = mul(y[i], inv);
	}
}
int t, n;
long long x[MAXN], y[MAXN];
long long a[MAXN/2], dp[MAXN/2];
void CDQ(int l, int r)
{
	if (l == 0 && r == 0) {return;}
    if (l == r) { dp[l] = (dp[l] + 0 * a[l]) % P; return; } 
    int mid = (l + r) >> 1; 
    CDQ(l, mid);
    len = 1;
    int len1 = mid - l + 1, len2 = r - l + 1;
    while(len < len2) len <<= 1;
    for (int i = 0; i < len1; i++) {
    	x[i] = dp[i + l];
    }
    for (int i = len1; i < len; i++) x[i] = 0;
    for (int i = 0; i < len2; i++) {
    	y[i] = a[i];
    }
    for (int i = len2; i < len; i++) y[i] = 0; 
    set();
    dft(x, 0);
    dft(y, 0);
    for (int i = 0; i < len; i++) x[i] = mul(x[i], y[i]);
    dft(x, 1);

    for (int i = mid+1; i <= r; i++)
    {
        dp[i] = (dp[i] + x[i - l]) % P;
    }
    CDQ(mid + 1, r);
}
int main()
{
	int t;
	freopen("b.in", "r", stdin);
    while(~scanf("%d %d",&n, &t) && n)
    {
    	dp[0] = t;
        for (int i = 1; i <= n; i++)
        {
            scanf("%lld",&a[i]);
            a[i] %= P;
            // dp[i] = 0;
        }
        CDQ(0, n);
        printf("%lld\n", dp[n]);
    }
}