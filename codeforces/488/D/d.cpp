#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <cmath>

#define INF 0x3f3f3f3f

using namespace std;

struct Num_s {
	long long id, value;
	bool operator < (const Num_s & n) const {
		return value > n.value;
	}
};

struct Num_b {
	long long id, value;
	bool operator < (const Num_b & n) const {
		return value < n.value;
	}
};

int n, s, len;
long long arr[100010];
int l[100010];
long long dp[100010];
long long minnum[100010][30];
priority_queue<Num_s> small;
priority_queue<Num_b> big;
void init() {
	l[n + 1] = INF;
	for (int i = n; i >= 1; i--) {
		l[i] = min(l[i + 1], i);
		for (; l[i] >= 1; l[i]--) {
			while (!big.empty() && big.top().id > i)
				big.pop();
			while (!small.empty() && small.top().id > i)
				small.pop();
			if ((big.empty() && small.empty()) || (abs(big.top().value - arr[l[i]]) <= s && abs(small.top().value - arr[l[i]]) <= s)) {
				// if (!big.empty()) cout<<i<<' '<<l[i]<<' '<<arr[l[i]]<<' '<<big.top().value<<' '<<small.top().value<<endl;
				Num_b num;
				num.id = i;
				num.value = arr[l[i]];
				big.push(num);
				Num_s _num;
				_num.id = i;
				_num.value = arr[l[i]];
				small.push(_num);
				continue;
			} else break;
		}
		l[i]++;
	}
	// for (int i=1;i<=n;i++) cout<<l[i]<<' ';
	// 	cout<<endl;
}

int rmq(int a, int b) {
	int k = log(b - a + 1) / log(2);
	int ans = min(minnum[b][k], minnum[b - (1 << k) + 1][k]);
	return ans;
}

void cal()
{
	while (!small.empty()) small.pop();
	Num_s num;
	num.id=0;
	num.value=0;
	small.push(num);
	for (int i=1;i<=n;i++)
	{
		while (!small.empty() && small.top().id<l[i]-1)
		{
			small.pop();
		}
		if (i-len>0)
		{
			Num_s num;
			num.id=i-len;
			num.value=dp[i-len];
			small.push(num);
		}
		if (i-len<l[i]-1) 
		{
			dp[i]=INF;
			continue;
		} 
		if (small.empty())
		{
			dp[i]=INF;
		}
		else
		{
			dp[i]=small.top().value+1;
			// cout<<i<<' '<<l[i]<<' '<<small.top().id<<' '<<dp[i]<<endl;
		}
	}
	if (dp[n]==INF) dp[n]=-1;
	cout<<dp[n]<<endl;
}


int main() {
	// freopen("d.in", "r", stdin);
	cin >> n >> s >> len;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
	}
	init();
	//cal();




	// for (int i = 1; i <= n; i++) {
	// 	cout << l[i] << ' ';
	// // }
	for (int i = 1; i <= n; i++) {
		dp[i] = INF;
	}
	for (int i = 1; i <= n; i++) {
		int a = l[i] - 1;
		int b = i - len;
		if (b >= a) {
			dp[i] = rmq(a, b) + 1;
		}
		minnum[i][0] = dp[i];
		for (int j = 1;; j++) {
			if (i - (1 << j) + 1 > 0)
				minnum[i][j] = min(minnum[i - (1 << (j - 1))][j - 1], minnum[i][j - 1]);
			else break;
		}
	}
	if (dp[n] == INF) cout << -1 << endl;
	else cout << dp[n] << endl;
	return 0;
}
