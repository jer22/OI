#include<cstdio>

#include<cstdlib>

#include<cmath>

#include<cstring>

#include<algorithm>

#include<iostream>

#include<vector>

#include<map>

#include<set>

#include<queue>

#include<string>

#define inf 1000000000

#define maxn 500000+5

#define maxm 500+100

#define eps 1e-10

#define ll long long

#define pa pair<int,int>

#define for0(i,n) for(int i=0;i<=(n);i++)

#define for1(i,n) for(int i=1;i<=(n);i++)

#define for2(i,x,y) for(int i=(x);i<=(y);i++)

#define for3(i,x,y) for(int i=(x);i>=(y);i--)

#define mod 1000000007

using namespace std;

inline int read()

{

    int x=0,f=1;char ch=getchar();

    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}

    while(ch>='0'&&ch<='9'){x=10*x+ch-'0';ch=getchar();}

    return x*f;

}
struct edge{int go,next;ll w;}e[2*maxn];
int n,m,tot,s[maxn],head[maxn];
ll f[maxn],g[maxn],z[maxn][2],d[maxn];
bool v[maxn],a[maxn];
inline void insert(int x,int y,int z)
{
    e[++tot]=edge{y,head[x],z};head[x]=tot;
    e[++tot]=edge{x,head[y],z};head[y]=tot;
}
inline void down(int x)
{
    v[x]=1;s[x]=a[x];
    for(int i=head[x],y;i;i=e[i].next)
        if(!v[y=e[i].go])
        {
            down(y);
            s[x]+=s[y];
            if(s[y])g[x]+=g[y]+e[i].w*2;
        }
    v[x]=0;    
}
inline void up(int x)
{
    v[x]=1;
    for(int i=head[x],y;i;i=e[i].next)
        if(!v[y=e[i].go])
        {
           if(s[y])f[y]=f[x]+g[x]-g[y];else f[y]=f[x]+g[x]-g[y]+2*e[i].w;
            
            up(y);
        }
    v[x]=0;
}
inline void update(int y,int x)
{
    if(y>z[x][0]){z[x][1]=z[x][0];z[x][0]=y;}
    else if(y>z[x][1])z[x][1]=y;
}
inline void dp1(int x)
{
    v[x]=1;
    for(int i=head[x],y;i;i=e[i].next)
    if(!v[y=e[i].go])
    {
        dp1(y);
        if(s[y])update(z[y][0]+e[i].w,x);//update(z[y][1]+e[i].w,x);
    }
    v[x]=0;
}
inline void dp2(int x)
{
    v[x]=1;
    for(int i=head[x],y;i;i=e[i].next)
    if(!v[y=e[i].go])
    {
        d[y]=max(d[y],d[x]+e[i].w);
        if(z[x][0]==z[y][0]+e[i].w)d[y]=max(d[y],z[x][1]+e[i].w);
        else d[y]=max(d[y],z[x][0]+e[i].w);
        dp2(y);
    }
    v[x]=0;
}

int main()

{

    // freopen("input.txt","r",stdin);

    // freopen("output.txt","w",stdout);

    n=read();m=read();
    for1(i,n-1){int x=read(),y=read();insert(x,y,read());}
    for1(i,m)a[read()]=1;
    down(1);
    up(1);
    dp1(1);
    dp2(1);
    //for1(i,n)printf("%d %d %d %d\n",i,f[i],g[i],z[i][0]);
    for1(i,n)printf("%lld\n",f[i]+g[i]-max(d[i],z[i][0]));

    return 0;

}