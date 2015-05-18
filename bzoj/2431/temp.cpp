#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<bitset>
#include<cstring>
#define ll long long 
#define inf 2000000000
#define mod 10000
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,K;
int f[1005][1005],s[1005][1005];
int main()
{
	freopen("2431.in", "r", stdin);
	n=read();K=read();
	f[1][0]=1;
	for(int i=0;i<=K;i++)s[1][i]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=0;j<=K;j++)
		{
			f[i][j]=s[i-1][j];
			if(j-i>=0)f[i][j]-=s[i-1][j-i];
			f[i][j]=(f[i][j]+mod)%mod;
			cout << f[i][j] << ' ';
		}
		cout << endl;
		s[i][0]=1;
		for(int j=1;j<=K;j++)
			s[i][j]=(s[i][j-1]+f[i][j])%mod;
	}
	printf("%d",f[n][K]);
	return 0;
}