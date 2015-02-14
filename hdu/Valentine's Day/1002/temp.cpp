#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

int prime[50],cnt[50],cp,ans;
long long n,finans[1500];

void fac(long long n)
{
	int m=sqrt(n+0.5);
	for (int i=2;i<=m;i++)
		if (!(n%i))
		{
			while (!(n%i))
			{
				cnt[cp]++;
				n/=i;
			}
			prime[cp++]=i;
		}
	if (n!=1)
	{
		cnt[cp]=1;
		prime[cp++]=n;
	}
}

long long gcd(long long a,long long b)
{
	return b?gcd(b,a%b):a;
}

void dfs(int cur,long long x)
{
	cout << cur << endl;	
	if (cur>=cp)
	{
		if (((n ^ x) < n) && gcd(n,n^x)==x) finans[ans++]=n^x;
		return ;
	}
	for (int i=0;i<=cnt[cur];i++)
	{
		dfs(cur+1,x);
		x*=prime[cur];
	}
}

int main()
{
	freopen("1002.in", "r", stdin);
	scanf("%lld",&n);
	fac(n);
	dfs(0,1);
	ans--;
	sort(finans,finans+ans);
	printf("%d\n",ans);
	for (int i=0;i<ans;i++) printf("%lld ",finans[i]);
	return 0;
}