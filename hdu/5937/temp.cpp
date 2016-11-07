//
//by coolxxx
//#include<bits/stdc++.h>
#include<iostream>
#include<algorithm>
#include<string>
#include<iomanip>
#include<map>
#include<stack>
#include<queue>
#include<set>
#include<bitset>
#include<memory.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<stdbool.h>
#include<math.h>
#pragma comment(linker,"/STACK:1024000000,1024000000")
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(a) ((a)>0?(a):(-(a)))
#define lowbit(a) (a&(-a))
#define sqr(a) ((a)*(a))
#define swap(a,b) ((a)^=(b),(b)^=(a),(a)^=(b))
#define mem(a,b) memset(a,b,sizeof(a))
#define eps (1e-8)
#define J 10000
#define mod 1000000007
#define MAX 0x7f7f7f7f
#define PI 3.14159265358979323
#define N 24
#define M 1004
using namespace std;
typedef long long LL;
double anss;
LL aans;
int cas,cass;
int n,m,lll,ans;
int num[10];
int a[N]={
	112,
	123,
	134,224,
	145,235,
	156,246,336,
	167,257,347,
	178,268,358,448,
	189,279,369,459};
int b[N][3]={
	{1,1,2},
	{1,2,3},
	{1,3,4},{2,2,4},
	{1,4,5},{2,3,5},
	{1,5,6},{2,4,6},{3,3,6},
	{1,6,7},{2,5,7},{3,4,7},
	{1,7,8},{2,6,8},{3,5,8},{4,4,8},
	{1,8,9},{2,7,9},{3,6,9},{4,5,9}};
int c[N]={
	1,
	2,
	2,1,
	2,2,
	2,2,1,
	2,2,2,
	2,2,2,1,
	2,2,2,2};
int d[N]={
	1,
	3,
	5,6,
	8,10,
	12,14,15,
	17,19,21,
	23,25,27,28,
	30,32,34,36};
void dfs(int top,int le,int l)
{
	if((ans-top)*3>=le)return;
	if(ans-top>=d[l-1])return;
	int i,x,y,z;
	ans=max(ans,top);
	for(i=l-1;i>=0;i--)
	{
		x=b[i][0],y=b[i][1],z=b[i][2];
		num[x]--,num[y]--,num[z]--;
		if(num[x]>=0 && num[y]>=0 && num[z]>=0)
			dfs(top+1,le-3,i);
		if(c[i]>1)
		{
			num[x]--,num[y]--,num[z]--;
			if(num[x]>=0 && num[y]>=0 && num[z]>=0)
				dfs(top+2,le-6,i);
			num[x]++,num[y]++,num[z]++;
		}
		num[x]++,num[y]++,num[z]++;
	}
}
int main()
{
	#ifndef ONLINE_JUDGE
	freopen("5937.in","r",stdin);
//	freopen("2.txt","w",stdout);
	#endif
	int i,j,k;
	int x,y,z;
//	init();
//	for(scanf("%d",&cass);cass;cass--)
	for(scanf("%d",&cas),cass=1;cass<=cas;cass++)
//	while(~scanf("%s",s))
//	while(~scanf("%d%d",&n,&m))
	{
		printf("Case #%d: ",cass);
		z=0;ans=0;
		for(i=1;i<10;i++)
		{
			scanf("%d",&num[i]);
			num[i]=min(num[i],17-i);
			z+=num[i];
		}
		if(num[9])i=20;
		else if(num[8])i=16;
		else if(num[7])i=12;
		else if(num[6])i=9;
		else if(num[5])i=6;
		else if(num[4])i=4;
		else if(num[3])i=2;
		else if(num[2])i=1;
		dfs(0,z,i);
		printf("%d\n",ans);
	}
	return 0;
}
/*
//

//
*/
