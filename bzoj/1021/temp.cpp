#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<iostream>
#define MAXM 1000
#define N 6
#define update(a,b) ((a)=(a)<(b)?(a):(b))
using namespace std;
const int money[]={1,5,10,20,50,100};
int F[2][3*MAXM+10][3*MAXM+10],a[N],b[N],c[N],sa,sb,sc,ea,eb,ec,sum,now;
int gcd(int a,int b){  return !b?a:gcd(b,a%b);  }
void read()
{
    int x,y,z;
    scanf("%d %d %d",&x,&y,&z);
    for(int i=N-1;i>=0;i--)
    {
        scanf("%d",&a[i]);
        sa=sa+a[i]*money[i];
    }
    for(int i=N-1;i>=0;i--)
    {
        scanf("%d",&b[i]);
        sb=sb+b[i]*money[i];
    }
    for(int i=N-1;i>=0;i--)
    {
        scanf("%d",&c[i]);
        sc=sc+c[i]*money[i];
    }
    ea=sa-x+z,eb=sb-y+x,ec=sc-z+y,sum=sa+sb+sc;
}
void Dp()
{
    for(int i=0;i<=MAXM;i++)
        for(int j=0;j<=MAXM;j++)
            F[now][i][j]=1<<30;
    F[now][sa][sb]=0;
    if(ea<0||eb<0||ec<0)
    {
        printf("impossible\n");
        return ;
    }
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<=MAXM;j++)
            for(int k=0;k<=MAXM;k++)
                F[now^1][j][k]=F[now][j][k];
        int GCD=money[i],x,y;
        for(int r=i+1;r<N;r++)
            GCD=gcd(GCD,money[r]);
        for(x=0;(ea-x)%GCD;x++);
        for(y=0;(eb-y)%GCD;y++);
        if((ec-(sum-x-y))%GCD)  continue;
        for(int j=x;j<=MAXM;j+=GCD)
        {
            if(sum-j-y<0)  break;
            for(int k=y;k<=MAXM;k+=GCD)
            {
                int vc=sum-j-k;
                if(vc<0)  break;
                if(F[now][j][k]==1<<30)  continue;
                for(int r=0;r<=a[i];r++) {
                    if(j>=r*money[i]) {
                        for(int l=0;l<=r;l++) {
                            if(k+l*money[i]<=MAXM&&vc+(r-l)*money[i]<=MAXM) {
                                update(F[now^1][j-r*money[i]][k+l*money[i]],F[now][j][k]+r);
                            }
                        }
                    }
                }
                for(int r=0;r<=b[i];r++)
                    if(k>=r*money[i]) {
                        for(int l=0;l<=r;l++)
                            if(j+l*money[i]<=MAXM&&vc+(r-l)*money[i]<=MAXM) {
                                update(F[now^1][j+l*money[i]][k-r*money[i]],F[now][j][k]+r);
                            }
                    }
                for(int r=0;r<=c[i];r++)
                    if(vc>=r*money[i]) {
                        for(int l=0;l<=r;l++)
                            if(j+l*money[i]<=MAXM&&k+(r-l)*money[i]<=MAXM)
                                update(F[now^1][j+l*money[i]][k+(r-l)*money[i]],F[now][j][k]+r);
                    }
                for(int r=0;r<=a[i];r++)
                    if(j>=r*money[i]) {
                        for(int l=0;l<=b[i];l++)
                            if(k>=l*money[i]&&vc+(r+l)*money[i]<=MAXM)
                                update(F[now^1][j-r*money[i]][k-l*money[i]],F[now][j][k]+r+l);
                    }
                for(int r=0;r<=a[i];r++)
                    if(j>=r*money[i]) {
                        for(int l=0;l<=c[i];l++)
                            if(vc>=l*money[i]&&k+(r+l)*money[i]<=MAXM)
                                update(F[now^1][j-r*money[i]][k+(l+r)*money[i]],F[now][j][k]+r+l);
                    }
                for(int r=0;r<=c[i];r++)
                    if(vc>=r*money[i]) {
                        for(int l=0;l<=b[i];l++)
                            if(k>=l*money[i]&&j+(l+r)*money[i]<=MAXM)
                                update(F[now^1][j+(l+r)*money[i]][k-l*money[i]],F[now][j][k]+r+l);
                    }
            }
        }
        now^=1;
    }
    F[now][ea][eb]==1<<30?printf("impossible\n"):printf("%d\n",F[now][ea][eb]);
}
int main()
{
    freopen("1021.in", "r", stdin);
    read();
    Dp();
    return 0;
}