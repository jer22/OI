#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define maxn (1000010)
ll n,K,p,fib[10000010],len[maxn],indfib[maxn],inv[maxn];
bool vis[maxn];

struct Matrix
{
	ll a,b; ll s[4][4];
	Matrix () { memset(s,0,sizeof(s)); }
	friend inline Matrix operator * (const Matrix &x,const Matrix &y)
	{
		Matrix z; z.a = x.a; z.b = y.b;
		for (ll i = 1;i <= z.a;++i)
			for (ll j = 1;j <= z.b;++j)
				for (ll k = 1;k <= x.b;++k)
					(z.s[i][j] += x.s[i][k]*y.s[k][j]%p)%=p;
		return z;
	}
}save[maxn];

inline ll exgcd(ll a,ll b,ll c)
{
	if (a == 0) return -1;
	else if (c % a == 0) return c/a;
	ll t = exgcd(b % a,a,((-c % a)+a)%a);
	if (t == -1) return -1;
	return (t*b+c)/a;
}

inline Matrix qsm(Matrix x,ll y)
{
	Matrix ret;
	ret.a = ret.b = x.a; ret.s[1][1] = ret.s[2][2] = ret.s[3][3] = 1;
	for (;y;y >>= 1,x = x*x)
		if (y & 1) ret = ret*x;
	return ret;
}

int main()
{
	freopen("2432.in","r",stdin);
	scanf("%lld %lld %lld",&n,&K,&p);
	fib[1] = fib[2] = 1;
	for (ll i = 3;;++i)
	{
		fib[i] = fib[i-1] + fib[i-2];
		if (fib[i] >= K) fib[i] -= K;
		if (!indfib[fib[i]]) indfib[fib[i]] = i;
		if (fib[i] == 1&&fib[i-1] == 1) break;
	}
	Matrix ans,mul,dec; bool sign = false;
	ans.a = 1; ans.b = 3; ans.s[1][1] = ans.s[1][3] = 1;
	mul.a = mul.b = 3; mul.s[1][2] = mul.s[2][1] = mul.s[2][2] = mul.s[3][3] = 1;
	dec.a = dec.b = 3; dec.s[1][1] = dec.s[2][2] = dec.s[3][3] = 1; dec.s[3][2] = -1;
	for (ll t = 1;n;)
	{
		if (!inv[t]) inv[t] = exgcd(t,K,1);
		if (inv[t] == -1) { ans = ans*qsm(mul,n); n = 0;}
		else
		{
			if (!vis[t]||sign)
			{
				vis[t] = true;
				if (!indfib[inv[t]])
				{
					ans = ans*qsm(mul,n); n = 0;
				}
				else
				{
					len[t] = indfib[inv[t]];
					if (n >= len[t])
					{
						n -= len[t];
						save[t] = qsm(mul,len[t])*dec;
						ans = ans*save[t];
						(t *= fib[len[t]-1])%=K;
					}
					else { ans = ans*qsm(mul,n); n = 0; }
				}
			}
			else
			{

				ll cnt = 0; Matrix ret; ret.a = ret.b = 3; ret.s[1][1] = ret.s[2][2] = ret.s[3][3] = 1;
				for (ll i = t*fib[len[t]-1]%K;i != t;(i *= fib[len[i]-1])%=K)
					cnt += len[i],ret = ret * save[i];
				cnt += len[t],ret = save[t]*ret;
				ans = ans*qsm(ret,n/cnt); n %= cnt;
				sign = true;
			}
		}
	}
	printf("%lld",(ans.s[1][2]+p)%p);
	return 0;
}
