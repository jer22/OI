#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXN 200010
#define MOD 10007

using namespace std;

int n;
vector<int> edges[MAXN];
int w[MAXN];
int main() {
	freopen("1351.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &a, &b);
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	for (int i = 1; i <= n; i++) {
		scanf("%d", &w[i]);
	}
	int ans = 0;
	int maxnum = 0;
	for (int i = 1; i <= n; i++) {
		int first = 0;
		int second = 0;
		int temp = 0;
		int t = 0;
		for (int j = 0; j < edges[i].size(); j++) {
			if (w[edges[i][j]] > first)  {
				second = first;
				first = w[edges[i][j]];
			}
			else if (w[edges[i][j]] > second) second = w[edges[i][j]];
			temp += w[edges[i][j]];
			temp %= MOD;
			t += w[edges[i][j]] * w[edges[i][j]];
			t %= MOD;
		}
		maxnum = max(maxnum, first * second);
		temp = temp * temp % MOD;
		temp -= t;
		while (temp < 0) temp += MOD;
		ans += temp;
		ans %= MOD;
	}
	printf("%d %d\n", maxnum, ans);
	return 0;
}
