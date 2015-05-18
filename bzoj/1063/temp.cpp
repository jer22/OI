#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <string>
#define M 200005
#define LL long long
using namespace std;
struct edge
{
	int y,ne;
}e[M];
int h[M],tot,n,m,v[M];
LL f[M][11][3],mod;
void Addedge(int x,int y)
{
	e[++tot].y=y;
	e[tot].ne=h[x];
	h[x]=tot;
}
LL Get(LL x)
{
	if (x&&x%mod==0) return mod;
	return x%mod;
}
void dfs(int x)
{
	v[x]=1;
	for (int i=0;i<=10;i++)
		f[x][i][0]=1LL;
	for (int i=h[x];i;i=e[i].ne)
	{
		int y=e[i].y;
		if (v[y]) continue;
		dfs(y);
		for (int j=0;j<=10;j++)
		{
			LL f1=0,f2=0;
			f1=f[y][j][0]+f[y][j][1];
			if (j)
				f2=f[y][j-1][0]+f[y][j-1][1]+f[y][j-1][2];
			f[x][j][2]=Get(f[x][j][2]*f2+f[x][j][1]*f1);
			f[x][j][1]=Get(f[x][j][1]*f2+f[x][j][0]*f1);
			f[x][j][0]=Get(f[x][j][0]*f2);
		}
	}
}
int main()
{
	freopen("1063.in", "r", stdin);
        scanf("%d%d%lld",&n,&m,&mod);
	for (int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		Addedge(x,y),Addedge(y,x);
	}
	if (m!=n-1)
	{
		puts("-1"),puts("-1");
		return 0;
	}
	dfs(1);
	for (int i=0;i<=10;i++)
		if (f[1][i][0]+f[1][i][1]+f[1][i][2]>0)
		{
			printf("%d\n",i);
			printf("%lld\n",(f[1][i][0]+f[1][i][1]+f[1][i][2])%mod);
			return 0;
		}
	puts("-1"),puts("-1");
	return 0;
}
