#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define N 55000

using namespace std;

int n;
long long c,sum[N],f[N],dp[N];
int q[N];

inline void read()
{
    scanf("%d%lld",&n,&c); c+=1;
    for(int i=1;i<=n;i++)
    {
        scanf("%lld",&sum[i]);
        sum[i]+=sum[i-1];
        f[i]=sum[i]+(long long)i;
    }
}

inline long long S(int x,int y)
{
    return 2*(f[x]-f[y]);
}

inline long long G(int x,int y)
{
    return dp[x]-dp[y]+(f[x]+c)*(f[x]+c)-(f[y]+c)*(f[y]+c);
}

inline void go()
{
    int h=1,t=2;
    q[1]=0;
    for(int i=1;i<=n;i++)
    {
        while(h<t-1&&G(q[h+1],q[h])<=S(q[h+1],q[h])*f[i]) h++;
        dp[i]=dp[q[h]]+(f[i]-f[q[h]]-c)*(f[i]-f[q[h]]-c);
        while(h<t-1&&G(i,q[t-1])*S(q[t-1],q[t-2])<=G(q[t-1],q[t-2])*S(i,q[t-1])) t--;
        q[t++]=i;
    }
    printf("%lld\n",dp[n]);
}

int main()
{
    freopen("1010.in", "r", stdin);
    read();
    go();
    return 0;
}