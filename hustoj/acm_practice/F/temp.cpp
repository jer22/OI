/*
dp[i][state] 前i个按钮,使得Xi,Xj,Xk状态为state的方法数。
X^3=x1+x2+x3...xn)^3=sigma(Xi*Xj*Xk)。
E[X]*2^M=X1+X2+...+Xn
E[X^3]*2^M=X^3=sigma(Xi*Xj*Xk)
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int FUCK=1e9+7;  
const int maxn=55;
long long temp[maxn];  
long long dp[maxn][8];  
int n,m;

int main()
{
	int cas=1,T;
	cin>>T;
	while(T--)
	{
		cin>>n>>m;
		for(int i=0;i<m;i++)  
        {  
            long long t=0;  
            int k;
            cin>>k;  
            for(int j=1;j<=k;j++)
            {   int x;
            	scanf("%d",&x);  
                x--;  
                t |= (1ll<<x);  
            }
            temp[i]=t;
        }
        int ans=0;
        for(int i=0;i<n;i++)  
            for(int j=0;j<n;j++)
                for(int k=0;k<n;k++)
                {  
          			memset(dp,0,sizeof(dp));
          			dp[0][0]=1;
          			for(int t=0;t<m;t++)  
                    {
                    	int flag=0;  
    					if(temp[t]>>i & 1) flag ^= 1; 
    					if(temp[t]>>j & 1) flag ^= 2;
    					if(temp[t]>>k & 1) flag ^= 4;
                        for(int x=0;x<8;x++) 
                        {  
                            dp[t+1][x^flag]=(dp[t+1][x^flag]+dp[t][x])%FUCK;  
                            dp[t+1][x]=(dp[t+1][x]+dp[t][x])%FUCK;  
                        }  
                    }
                    ans=(ans+dp[m][7])%FUCK;  
                }
        printf("Case #%d: %d\n",cas++,ans);
	}		
	return 0;
}