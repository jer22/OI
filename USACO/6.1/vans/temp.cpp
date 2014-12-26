#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxx=100000000;
int n;
int dp[1001][9][60];
void init()
{
	freopen("vans.in","r",stdin);
	freopen("vans.out","w",stdout);
	cin>>n;
	n--;
}
void add(int k,int v1,int v2)
{
	int i,jin;
	jin=0;
	for (i=1; i<=59; i++)
	{
		dp[k][v1][i]+=dp[k-1][v2][i]+jin;
		jin=0;
		if (dp[k][v1][i]>maxx)
		{
			jin=dp[k][v1][i]/maxx;
			dp[k][v1][i]%=maxx;
		}
	}
}
void doit()
{
	memset(dp,0,sizeof(dp));
	dp[1][3][1]=1; dp[1][7][1]=1;
	int i;
	for (i=2; i<=n; i++)
	{
		add(i,1,3); add(i,1,8);
		add(i,3,1); add(i,3,4); add(i,3,6); add(i,3,7);
		add(i,4,3);
		add(i,6,3); add(i,6,8);
		add(i,7,1); add(i,7,6);
		add(i,7,7);
		add(i,8,3); add(i,8,8);
	}
}
void print()
{
	add(n+1,2,3); add(n+1,2,8);
	add(n+1,2,3); add(n+1,2,8);
	int i,j;
	i=59;
	while (i>1 && dp[n+1][2][i]==0) i--;
	cout<<dp[n+1][2][i];
	for (j=i-1; j>=1; j--) printf("%08d",dp[n+1][2][j]);
	cout<<endl;
}
int main()
{
	init();
	doit();
	print();
}