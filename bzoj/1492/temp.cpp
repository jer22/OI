#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#define eps 1e-9
#define inf 0x7fffffff
#define ll long long
using namespace std;
int n,top,stack[100005];
double f[100005];
struct point{double x,y,a,b,k,rate;int w;}p[100005],t[100005];
double getk(int a,int b)
{
	if(!b)return -1e20;
	if(fabs(p[a].x-p[b].x)<eps)return 1e20;
	return (p[b].y-p[a].y)/(p[b].x-p[a].x);
}
inline bool operator<(point a,point b){return a.k>b.k;}
void solve(int l,int r)
{
	if(l==r)
	{
		f[l]=max(f[l],f[l-1]);
		p[l].y=f[l]/(p[l].a*p[l].rate+p[l].b);
		p[l].x=p[l].rate*p[l].y;
		return;
	}//分治到底了显然我们可以直接计算出结果 
	int l1,l2,mid=(l+r)>>1,j=1;
//============================================================================
	l1=l;l2=mid+1;
	for(int i=l;i<=r;i++)
	    if(p[i].id<=mid)t[l1++]=p[i];
	    else t[l2++]=p[i];
	    for(int i=l;i<=r;i++)p[i]=t[i];
//============================================================================
//这一部分是要将一块原顺序分为左右两块 
	solve(l,mid);//递归左边
	top=0;
	for(int i=l;i<=mid;i++)
	{
		while(top>1&&getk(stack[top-1],stack[top])<getk(stack[top-1],i)+eps)
		    top--;
		stack[++top]=i;
    }//左边维护一个凸包
    stack[++top]=0;
    for(int i=mid+1;i<=r;i++)
    {
    	while(j<top&&getk(stack[j],stack[j+1])+eps>p[i].k)j++;//用左边的点作为决策更新右边 
        f[p[i].id]=max(f[p[i].id],p[stack[j]].x*p[i].a+p[stack[j]].y*p[i].b);
	}
	solve(mid+1,r);//递归右边 
	l1=l;l2=mid+1;
	for(int i=l;i<=r;i++)
	   if(((p[l1].x<p[l2].x||(fabs(p[l1].x-p[l2].x)<eps&&p[l1].y<p[l2].y))||l2>r)&&l1<=mid)t[i]=p[l1++];
	   else t[i]=p[l2++];
    for(int i=l;i<=r;i++)p[i]=t[i];
}
int main()
{
//============================================================================
	//freopen("cash.in","r",stdin);
    //freopen("cash.out","w",stdout);
	scanf("%d%lf",&n,&f[0]);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf%lf%lf",&p[i].a,&p[i].b,&p[i].rate);
		p[i].k=-p[i].a/p[i].b;p[i].id=i;
	}
//============================================================================
	sort(p+1,p+n+1);//这里按照斜率进行排序，保证分治的每一块斜率是有序的 
	solve(1,n);
	printf("%.3lf",f[n]);
	return 0;
}