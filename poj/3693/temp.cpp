#include<cstdio>
#include <iostream>
#include <algorithm>
#include<cstring>
using namespace std;
const int maxn=100010;
int sa[maxn],wa[maxn],wb[maxn],Ws[maxn],n,r[maxn],height[maxn],rank[maxn],rmq[maxn][20],f[maxn],b[maxn];
char str[maxn];
inline int min(int a,int b)
{
	return a<b?a:b;
}
inline int max(int a,int b)
{
	return a>b?a:b;
}
int cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m)
{
	int i,j,p;
	int *x=wa,*y=wb,*t;
	for(i=0;i<m;i++)Ws[i]=0;
	for(i=0;i<n;i++)Ws[x[i]=r[i]]++;
	for(i=1;i<m;i++)Ws[i]+=Ws[i-1];
	for(i=n-1;i>=0;i--)sa[--Ws[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		for(p=0,i=n-j;i<n;i++)y[p++]=i;
		for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
		for(i=0;i<m;i++)Ws[i]=0;
		for(i=0;i<n;i++)Ws[x[i]]++;
		for(i=1;i<m;i++)Ws[i]+=Ws[i-1];
		for(i=n-1;i>=0;i--)sa[--Ws[x[y[i]]]]=y[i];
		for(t=x,x=y,y=t,p=1,i=1,x[sa[0]]=0;i<n;i++)
			x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
}
void cal(int *r,int *sa,int n)
{
	int i,j;
	for(i=1;i<=n;i++)rank[sa[i]]=i;
	int k=0;
	for(i=0;i<n;height[rank[i++]]=k)
		for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
}
void RMQ(int n)
{
	int i,j;
	for(i=2;i<=n;i++) rmq[i][0]=height[i];
	rmq[1][0]=100000;
	for(j=1;(1<<j)<=n;j++)
	for(i=1;i+(1<<j)-1<=n;i++)
		rmq[i][j]=min(rmq[i][j-1],rmq[i+(1<<(j-1))][j-1]);
}
int get(int x)
{
	int cnt=-1;
	while(x)
	{
		cnt++;
		x>>=1;
	}
	return cnt;
}
int ask(int i,int j)
{
	if(i>j)
	{
		int k=i;
		i=j;
		j=k;
	}
	i++;
	int t=get(j-i+1);
	return min(rmq[i][t],rmq[j-(1<<t)+1][t]);
}
int main()
{
	freopen("3693.in", "r", stdin);
	int pro=0;
	while(scanf("%s",str)&&strcmp(str,"#"))
	{
		memset(f,0,sizeof(f));
		int i,j,l,k;
		int n=strlen(str);
		int maxn=-1;
		for(i=0;i<n;i++)
		{
			r[i]=str[i]-'a'+1;
			if(maxn<r[i])maxn=r[i];
		}
		r[n]=0;
		maxn++;
		da(r,sa,n+1,maxn);	
		cal(r,sa,n);
		RMQ(n);
		int ans=0;
		for(l=1;l<n/2;l++)
			for(j=0;j<(n-1)/l;j++)
		{
			int x=j*l,y=(j+1)*l;
			int z=ask(rank[x],rank[y]);
			f[l]=max(f[l],z/l+1);
			if(z%l) 
			{
				z=ask(rank[x-(l-z%l)],rank[y-(l-z%l)]);
				f[l]=max(f[l],z/l+1);
			}
		}
		int m=0;
		for(l=1;l<n/2;l++)
			if(ans<f[l])ans=f[l];
		for(l=1;l<n/2;l++)
			if(ans==f[l])
			{
			b[m++]=l;
			}
		int ff=1;	
		printf("Case %d: ",++pro);
		for(i=1;ff&&i<=n;i++)
			for(j=0;ff&&j<m;j++)
			{
				int x=sa[i];
				if(x+b[j]>=n)continue;
				int z=ask(rank[x],rank[x+b[j]]);
				if(z>=(ans-1)*b[j])
				{
					ff=0;
					for(k=x;k<x+ans*b[j];k++)printf("%c",str[k]);
					puts("");
					break;
				}
			}
	}
	return 0;
}