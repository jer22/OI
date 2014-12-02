#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int max(int a,int b)  
{  
    return a>b?a:b;  
}  
int main(void)  
{  freopen("1064.in", "r", stdin);
    int m,n,i,j,k,t1,t2,k1,k2;  
    int v[100],p[100],q[100],cost[32005];  
    scanf("%d%d",&n,&m);  
    for(i=1;i<=m;i++)  
       scanf("%d%d%d",&v[i],&p[i],&q[i]);  
    memset(cost,0,sizeof(cost));  
    for(i=1;i<=m;i++)  
    {  
        t1=0;t2=0;k1=0;k2=0;  
        if(q[i]==0)  
        {  
            for(j=i+1;j<=m;j++)  
               if(q[j]==i)  
               {  
                   t1=j;  
                   k1=1;  
                   break;  
               }  
            for(j=t1+1;j<=m;j++)  
               if(q[j]==i)  
               {  
                   t2=j;  
                   k2=1;  
                   break;  
               }  
            for(j=n;j>=v[i];j--)  
            {  
                cost[j]=max(cost[j-v[i]]+v[i]*p[i],cost[j]);  
                if(k1&&(j-v[i]-v[t1]>=0))  
                   cost[j]=max(cost[j-v[i]-v[t1]]+v[i]*p[i]+v[t1]*p[t1],cost[j]);  
                if(k2&&(j-v[i]-v[t2]>=0))  
                   cost[j]=max(cost[j-v[i]-v[t2]]+v[i]*p[i]+v[t2]*p[t2],cost[j]);  
                if(k1&&k2&&(j-v[i]-v[t1]-v[t2]>=0))  
                   cost[j]=max(cost[j-v[i]-v[t1]-v[t2]]+v[i]*p[i]+v[t2]*p[t2]+v[t1]*p[t1],cost[j]);  
            }  
  
        }  
    }  
    printf("%d",cost[n]);  
    return 0;  
}  