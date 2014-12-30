#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, m;
int arr[1000005];
long long dp[2][200005][2];
int main() {
	//freopen("1024.in", "r", stdin);
	while (~scanf("%d %d", &m, &n)) {
		//if (m>200000) {while (1);}
		for (int i = 1; i <= n; i++)
			scanf("%d", &arr[i]);
		int idx = 0;
		for (int j=0;j<=m;j++) dp[idx][j][0]=dp[idx][j][1]=-1111111111111LL;
		dp[idx][0][0]=0;

		for (int i=1;i<=n;i++)
		{
			idx^=1;
			for (int j=0;j<=m;j++) dp[idx][j][0]=dp[idx][j][1]=-1111111111111LL;
			dp[idx][0][0]=0;
			for (int j=1;j<=m;j++)
			{
				dp[idx][j][0]=max(dp[1-idx][j][0],dp[1-idx][j][1]);
				dp[idx][j][1]=max(dp[1-idx][j][1]+arr[i],dp[1-idx][j-1][0]+arr[i]);
				dp[idx][j][1]=max(dp[idx][j][1],dp[1-idx][j-1][1]+arr[i]);
			}
		}
		cout << max(dp[idx][m][0],dp[idx][m][1]) << endl;
	}



	return 0;
}
