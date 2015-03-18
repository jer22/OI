#include<cstring>
#include<cstdlib>
#include<iostream>
#include<cmath>
#include<cstdio>
using namespace std;
#define N 2010
int ws1[N],wv[N],wa[N],wb[N];
int rank1[N],height[N],sa[N];
char str[N];
int a[N],n;
int dp[N][25];

int min(int a,int b)
{
    return a>b?b:a;
}

int cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b] && r[a+l]==r[b+l];
}

void da(int *r,int *sa,int n,int m)
{
    int i,j,p,*x=wa,*y=wb,*t;
    for(i=0;i<m;i++)
        ws1[i]=0;
    for(i=0;i<n;i++)
        ws1[x[i]=r[i]]++;
    for(i=1;i<m;i++)
        ws1[i]+=ws1[i-1];
    for(i=n-1;i>=0;i--)
        sa[--ws1[x[i]]]=i;
    for(j=1,p=1;p<n;j*=2,m=p)
    {
        for(p=0,i=n-j;i<n;i++)
            y[p++]=i;
        for(i=0;i<n;i++)
            if(sa[i]>=j)
                y[p++]=sa[i]-j;
        for(i=0;i<n;i++)
            wv[i]=x[y[i]];
        for(i=0;i<m;i++)
            ws1[i]=0;
        for(i=0;i<n;i++)
            ws1[wv[i]]++;
        for(i=1;i<m;i++)
            ws1[i]+=ws1[i-1];
        for(i=n-1;i>=0;i--)
            sa[--ws1[wv[i]]]=y[i];
        for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
}

void calheight(int *r,int *sa,int n)
{
    int i,j,k=0;
    for(i=1;i<=n;i++)
        rank1[sa[i]]=i;
    for(i=0;i<n;height[rank1[i++]]=k)
        for(k?k--:0,j=sa[rank1[i]-1];r[i+k]==r[j+k];k++) ;
}

void RMQ()//RMQ预处理
{
    int i,j;
    memset(dp,127,sizeof(dp));
    for(i=1;i<=n*2+1;i++)
        dp[i][0]=height[i];
    for(j=1;(1<<j)<=2*n+1;j++)
        for(i=1;i+(1<<j)-1<=2*n+1;i++)
            dp[i][j]=min(dp[i][j-1],dp[i+(1<<(j-1))][j-1]);
}

int lcp(int l,int r)//求最长公共前缀
{
    int a=rank1[l],b=rank1[r];
    if(a>b)
        swap(a,b);
    a++;
    int t=(int)(log(double(b-a+1))/log(2.00));
    return min(dp[a][t],dp[b-(1<<t)+1][t]);
}

int main()
{
    freopen("1297.in", "r", stdin);
    int i,res,flag,max;
    while(scanf("%s",str)!=EOF)
    {
        max=0;
        n=strlen(str);
        for(i=0;i<n;i++)
            a[i]=(int)str[i];
        a[n]=1;
        for(i=0;i<n;i++)
            a[i+n+1]=int(str[n-i-1]);
        a[2*n+1]=0;
        da(a,sa,n*2+2,123);
        calheight(a,sa,2*n+1);
        RMQ();
        for(i=0;i<n;i++)
        {
            res=lcp(i,2*n-i)*2-1;
            if(max<res)//奇数时
            {
                max=res;
                flag=i;
            }
            if(i>0)//偶数时
            {
                res=lcp(i,2*n-i+1)*2;
                if(max<res)
                {
                    max=res;
                    flag=i;
                }
            }
        }
        if(max%2==1)
            for(i=flag-max/2;i<=flag+max/2;i++)
                printf("%c",str[i]);
        else
            for(i=flag-max/2;i<=flag+max/2-1;i++)
                printf("%c",str[i]);
        printf("\n");
    }
    return 0;
}