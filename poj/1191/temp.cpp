//1191
#include <stdio.h>
#include <iostream>
#include <cmath>

using namespace std ;

double dp[15][9][9][9][9] ,s[9][9] ;
int n ;

double ss(int x1,int y1,int x2,int y2)
{
    double sss = s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1] ;
    return sss * sss ;
}

double DFS(int k,int x1,int y1,int x2,int y2)
{
    if(k == 1) return ss(x1,y1,x2,y2) ;
    if(fabs(dp[k][x1][y1][x2][y2]) > 1e-6) return dp[k][x1][y1][x2][y2] ;
    double minn = 1 << 29 ;
    for(int i = x1 ; i < x2 ; i++)
        minn = min(minn,min(DFS(k-1,x1,y1,i,y2)+ss(i+1,y1,x2,y2),DFS(k-1,i+1,y1,x2,y2)+ss(x1,y1,i,y2))) ;
    for(int i = y1 ; i < y2 ; i++)
        minn = min(minn,min(DFS(k-1,x1,y1,x2,i)+ss(x1,i+1,x2,y2),DFS(k-1,x1,i+1,x2,y2)+ss(x1,y1,x2,i))) ;
    dp[k][x1][y1][x2][y2] = minn ;
    return minn ;
}
int main()
{
    freopen("1191.in", "r", stdin);
    scanf("%d",&n) ;
    int x ;
    //memset(s,0,sizeof(s)) ;
    for(int i = 1 ; i <= 8 ; i++)
        for(int j = 1 ; j <= 8 ; j++)
        {
            scanf("%d",&x) ;
            s[i][j] = x + s[i-1][j]+s[i][j-1]-s[i-1][j-1] ;
        }
    printf("%.3lf\n",sqrt(DFS(n,1,1,8,8)/n-(s[8][8]/n)*(s[8][8]/n)) );
    return 0 ;
}