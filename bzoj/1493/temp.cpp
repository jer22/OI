#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
#define ss printf("orz\n");
#define maxn 510000
int getint()
{
    char c;int res;
    while(c=getchar(),c<'0'||c>'9');
    res=c-'0';
    while(c=getchar(),c>='0'&&c<='9')
        res=res*10+c-'0';
    return res;
}
int root,tr[maxn][2],fa[maxn],cnt;
int lcol[maxn],col[maxn],rcol[maxn],sum[maxn],siz[maxn];
bool rev[maxn],tag[maxn];
int n,m;
void print(int now)
{
    int l=tr[now][0],r=tr[now][1];
    printf("%d %d %d %d %d %d\n",now,tr[now][0],tr[now][1],lcol[now],rcol[now],sum[now]);
    if(l) print(l);
    if(r) print(r);
}
 
void pushup(int rt)
{
    if(rt==0) return;
    int l=tr[rt][0],r=tr[rt][1];
    siz[rt]=siz[l]+siz[r]+1;
    lcol[rt]=rcol[rt]=col[rt];
    if(l)lcol[rt]=lcol[l];
    if(r)rcol[rt]=rcol[r];
    sum[rt]=sum[l]+sum[r]+1;
    if(l&&col[rt]==rcol[l])
    {
        sum[rt]--;
    }
    if(r&&col[rt]==lcol[r])
    {
        sum[rt]--;
    }
}
void pushdown(int rt)
{
    if(rt==0) return;
    int l=tr[rt][0],r=tr[rt][1];
    if(tag[rt])
    {
        tag[rt]=0;
        if(l)
        {
            sum[l]=1;tag[l]=1;
            lcol[l]=rcol[l]=col[l]=col[rt];
        }
        if(r)
        {
            sum[r]=1;tag[r]=1;
            lcol[r]=rcol[r]=col[r]=col[rt];
        }
    }
    if(rev[rt])
    {
        rev[rt]^=1;rev[l]^=1;rev[r]^=1;
        if(l)
        {
            swap(lcol[l],rcol[l]);
            swap(tr[l][0],tr[l][1]);
        }
        if(r)
        {
            swap(lcol[r],rcol[r]);
            swap(tr[r][0],tr[r][1]);
        }
    }
}
void rotate(int x,int &rt)
{
    int l,r,y,z;
    y=fa[x];z=fa[y];
    if(tr[y][0]==x) l=0;
    else l=1;r=l^1;
    if(y==rt) rt=x;
    else
    {
        if(tr[z][0]==y) tr[z][0]=x;
        else tr[z][1]=x;
    }
    fa[x]=z;fa[y]=x;fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];tr[x][r]=y;
    pushup(y);pushup(x);
}
 
void splay(int x,int &rt)
{
    int y,z;
    while(x!=rt)
    {
        y=fa[x];z=fa[y];
        if(y!=rt)
        {
            if((tr[y][0]==x)^(tr[z][0]==y)) rotate(x,rt);
            else rotate(y,rt);
        }
        rotate(x,rt);
    }
}
int select(int now,int rk)
{
    if(rev[now]||tag[now]) pushdown(now);
    int l=tr[now][0],r=tr[now][1];
    int rak=siz[l]+1;
    if(rak==rk) return now;
    if(rak>rk) return select(l,rk);
    else return select(r,rk-rak);
}
void print()
{
    for(int i=1;i<=n;i++)
    {
        printf("%d ",col[select(root,i+1)]);
    }
    printf("\n");
}
void solve_change(int x,int val)
{
    tag[x]=1;col[x]=val;
    sum[x]=1;
    rcol[x]=lcol[x]=col[x];
}
 
int query()
{
    if(n==0) return 0;
    int ans=sum[root]-2;
    int x=col[select(root,2)];
    int y=col[select(root,n+1)];
    //printf("%d %d %d\n",ans,x,y);
    if(x==y) return max(ans-1,1);
    return ans;
}
void roll(int k)
{
    if(k==0||k==n) return;
    int x=select(root,n-k+1);
    int y=select(root,n+2);
    splay(x,root);splay(y,tr[root][1]);
    x=y;y=tr[x][0];
    tr[x][0]=0;fa[y]=0;
    pushup(x);pushup(fa[x]);
   // print();
   // print(root);
    int xx=select(root,1);
    int yy=select(root,2);
    splay(xx,root);splay(yy,tr[root][1]);
    tr[yy][0]=y;fa[y]=yy;
    pushup(yy);pushup(xx);
   // ss
  //  printf("%d\n",k);
  //  print();
  //  print(root);
  //  ss
    
   // print(root);
  //  printf("%d\n",sum[root]);
  //  ss
}
int countseg(int l,int r)
{
    if(l<=r)
    {
        int x=select(root,l);
        int y=select(root,r+2);
        splay(x,root);
        splay(y,tr[root][1]);
        return sum[tr[y][0]];
    }
    else
    {
        roll(n-l+1);
        int ans=countseg(1,r+n-l+1);
        roll(l-1);
        return ans;
    }
}
void solve_rever(int x)
{
    if(tag[x]) return;
    rev[x]^=1;
    swap(tr[x][0],tr[x][1]);
    swap(lcol[x],rcol[x]);
}
void flip()
{
    if(n<=2) return;
    int x=select(root,2),y=select(root,n+2);
    splay(x,root);splay(y,tr[root][1]);
    solve_rever(tr[y][0]);pushup(y);pushup(x);
}
void change(int l,int r,int val)
{
    if(l<=r)
    {
        int x=select(root,l);
        int y=select(root,r+2);
        splay(x,root);splay(y,tr[root][1]);
        solve_change(tr[y][0],val);
        pushup(y);pushup(x);
    }
    else
    {
        roll(n-l+1);
        change(1,r+n-l+1,val);
        roll(l-1);
    }
}
void Swap(int l,int r)
{
    if(l==r) return;
    int x=col[select(root,l+1)];
    int y=col[select(root,r+1)];
    change(l,l,y);
    change(r,r,x);
}
void build(int l,int r,int f)
{
    if(l>r)return;
    int now=l,last=f;
    if(l==r)
    {
        lcol[now]=rcol[now]=col[l];
        fa[now]=last;sum[now]=siz[now]=1;
        if(l<f)tr[last][0]=now;
        else tr[last][1]=now;
        return;
    }
    int mid=(l+r)>>1;now=mid;
    build(l,mid-1,mid);build(mid+1,r,mid);
    fa[now]=last;
    pushup(now);
    if(mid<f)tr[last][0]=now;
    else tr[last][1]=now;
}
 
int main()
{
    freopen("1493.in", "r", stdin);
    n=getint();m=getint();
    for(int i=1;i<=n;i++) col[i+1]=getint();
    cnt=n+2;
    col[1]=col[n+2]=0;
    build(1,n+2,0);
    root=(n+3)>>1;
    m=getint();
    char op[10];
    int x,y,z;
    while(m--)
    {
        scanf("%s",op);
        if(op[0]=='R')
        {
            x=getint();
            roll(x);
        }
        else if(op[0]=='F')
        {
            flip();
        }
        else if(op[0]=='S')
        {
            x=getint();y=getint();
            Swap(x,y);
        }
        else if(op[0]=='P')
        {
            x=getint();y=getint();z=getint();
            change(x,y,z);
        }
        else if(op[0]=='C'&&strlen(op)==1)
        {
            printf("%d\n",query());
        }
        else
        {
            x=getint();
            y=getint();
            printf("%d\n",countseg(x,y));
        }
        
        // ss
        // ss
        // print(root);
        // ss
        // ss
        
    }
    return 0;
}
/*
10 4
4 4 2 2 1 4 2 3 1 4
11
C
F
C
R 2
P 9 8 2
CS 2 8
F
R 8
CS 2 6
S 10 5
S 2 5
*/