/**************************************************************
    Problem: 2756
    User: zhouhebin
    Language: C++
    Result: Accepted
    Time:7096 ms
    Memory:79436 kb
****************************************************************/
  
#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
#define inf (1LL<<50)
#define N 1610
#define S 0 
#define T (n*m+1)
#define pos(x,y) (x-1)*m+y
using namespace std;
int mx[4]={1,0,-1,0},my[4]={0,1,0,-1};
inline LL read()
{
    LL x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int tt,n,m,cnt,Mx,s1,s2;
LL sum1,sum2,l,r,tot,ans,QAQ;
int a[55][55];
struct edge{int to,next;LL v;}e[5000000];
int head[N],q[N],h[N];
inline void ins(int u,int v,LL w)
{
    e[++cnt].to=v;
    e[cnt].v=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
inline void insert(int u,int v,LL w)
{
    ins(u,v,w);
    ins(v,u,0);
}
inline bool bfs()
{
    memset(h,-1,sizeof(h));
    int t=0,w=1;
    q[0]=S;h[S]=0;
    while (t!=w)
    {
        int now=q[t++];if (t==1605)t=0;
        for (int i=head[now];i;i=e[i].next)
            if (e[i].v&&h[e[i].to]==-1)
            {
                h[e[i].to]=h[now]+1;
                q[w++]=e[i].to;
                if (w==1605)w=0;
            }
    }
    return h[T]!=-1;
}
inline LL dfs(int x,LL f)
{
    if (x==T||!f)return f;
    LL w,used=0;
    for (int i=head[x];i;i=e[i].next)
        if (e[i].v&&h[e[i].to]==h[x]+1)
        {
            w=dfs(e[i].to,min(e[i].v,f-used));
            e[i].v-=w;
            e[i^1].v+=w;
            used+=w;
            if (used==f)return f;
        }
    if (!used)h[x]=-1;
    return used;
}
inline void dinic(){while (bfs())ans+=dfs(S,inf);}
inline void build(LL x)
{
    ans=0;cnt=1;tot=0;
    memset(head,0,sizeof(head));
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
            if ((i+j)&1)
            {
                insert(S,pos(i,j),x-a[i][j]);
                for(int k=0;k<4;k++)
                {
                    int nx=i+mx[k],ny=j+my[k];
                    if (nx<1||ny<1||nx>n||ny>m)continue;
                    insert(pos(i,j),pos(nx,ny),inf);
                }
                tot+=x-a[i][j];
            }else insert(pos(i,j),T,x-a[i][j]);
}
inline bool jud(LL x)
{
    build(x);
    dinic();
    return ans==tot;
}
inline void work()
{
    n=read();m=read();
    sum1=sum2=s1=s2=Mx=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=m;j++)
        {
            a[i][j]=read();
            Mx=max(Mx,a[i][j]);
            if ((i+j)&1)sum1+=a[i][j],s1++;
            else sum2+=a[i][j],s2++;
        }
    if(s1!=s2)
    {
        LL des=(sum1-sum2)/(s1-s2);
        if (des>=Mx&&jud(des))printf("%lld\n",ans);
            else printf("-1\n");
        return;
    }
    QAQ=inf;l=Mx;r=2000000000;
    while (l<=r)
    {
        LL mid=(l+r)>>1;
        if (jud(mid))QAQ=min(QAQ,ans),r=mid-1;
        else l=mid+1;
    }
    printf("%lld\n",QAQ);
}
int main()
{
	freopen("2756.in", "r", stdin);
    tt=read();
    while (tt--)work();
    return 0;
}