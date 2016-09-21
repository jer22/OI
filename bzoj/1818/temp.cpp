#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,cnt,ans,hash[100001],tr[100001];
struct point{int x,y;}a[100001];
struct seg{int k,x,y,r;}s[1000001];
inline bool cmp1(point a,point b)
{if(a.x==b.x){return a.y<b.y;}return a.x<b.x;}
inline bool cmp2(point a,point b)
{if(a.y==b.y){return a.x<b.x;}return a.y<b.y;}
inline bool cmp3(seg a,seg b)
{
	if(a.y==b.y)return a.k<b.k;
	return a.y<b.y;
}
int find(int x)
{
    int l=1,r=n,mid;
    while(l<=r)
    {
		int mid=(l+r)>>1;
		if(hash[mid]<x)l=mid+1;
		else if(hash[mid]>x)r=mid-1;
		else return mid;
	} 
}
void insert(int k,int l,int r,int t)//0横线,1竖线 
{
	if(!k){s[++cnt].x=find(l);s[cnt].r=find(r);s[cnt].y=t;}
	else{
		s[++cnt].x=find(t);s[cnt].y=l;s[cnt].k=1;
		s[++cnt].x=find(t);s[cnt].y=r;s[cnt].k=-1; 
	}
}
void build()
{
	sort(a+1,a+n+1,cmp1);
	for(int i=2;i<=n;i++)
        if(a[i].x==a[i-1].x)
            insert(1,a[i-1].y,a[i].y,a[i].x);
    sort(a+1,a+n+1,cmp2);
	for(int i=2;i<=n;i++)
		if(a[i].y==a[i-1].y)
			insert(0,a[i-1].x,a[i].x,a[i].y);
}
int lowbit(int x){return x&(-x);}
void update(int x,int y)
{
	while(x<=n)
	{
		tr[x]+=y;
		x+=lowbit(x);
	}
}
int ask(int x)
{
	int s=0;
	while(x)
	{
		s+=tr[x];
		x-=lowbit(x);
	}
	return s;
}
void work()
{
	for(int i=1;i<=cnt;i++)
	{
		if(!s[i].k)ans+=ask(s[i].r-1)-ask(s[i].x);
		else update(s[i].x,s[i].k);
	}
}
int main()
{
	freopen("1818.inin", "r", stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
    {
		scanf("%d%d",&a[i].x,&a[i].y);
		hash[i]=a[i].x;
	}
    sort(hash+1,hash+n+1);
	build();
    sort(s+1,s+cnt+1,cmp3);
    work();
    printf("%d",ans+n);
	return 0;
}