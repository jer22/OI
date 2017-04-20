#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <stack>

using namespace std;

const int MAXN = 200005;

int p;
vector<int> arr[MAXN];
bool vis[MAXN];
int tot = 0;
int num[MAXN], cnt[MAXN];
int dp[MAXN], pre[MAXN];
int ban[MAXN];

template <class T>
T exgcd(T a, T b, T &x, T &y) {
	if (!b) {
		x = 1, y = 0;
		return a;
	}
	T t, ret;
	ret = exgcd(b, a % b, x, y);
	t = x, x = y, y = t - a / b * y;
	return ret;
}

int main() {
	freopen("c.in", "r", stdin);
	int n;
	scanf("%d %d", &n, &p);
	for (int x; n; n--) {
		scanf("%d", &x);
		ban[x] = 1;
	}
	for (int i = 1; i < p; ++i) {
		if (ban[i]) continue;
		int x = __gcd(i, p);
		arr[x].push_back(i);
		cnt[x]++;
		if (!vis[x]) {
			num[++tot] = x;
		}
		vis[x] = 1;
	}
	sort(num + 1, num + tot + 1);
	if (!tot) {
		if (ban[0])
			cout << 0 << endl;
		else cout << "1\n0";
		return 0;
	}
	assert(num[1] == 1);
	for (int i = 1; i <= tot; i++)
		dp[i] = cnt[num[i]];
	int ans = 0, id = 1;
	for (int i = 2; i <= tot; i++) {
		for (int j = 1; j < i; j++) {
			if (num[i] % num[j]) continue;
			if (dp[j] + cnt[num[i]] > dp[i]) {
				pre[i] = j;
				dp[i] = dp[j] + cnt[num[i]];
			}
		}
		if (dp[i] > ans) {
			ans = dp[i];
			id = i;
		}
	}
	stack<int> fff;
	while (id) {
		int x = num[id];
		for (int i = 0; i < arr[x].size(); i++) {
			fff.push(arr[x][i]);
		}
		id = pre[id];
	}
	int c = !ban[0] + fff.size();
	printf("%d\n", c);
	int pre = fff.top();
	printf("%d", pre);
	fff.pop();
	int t = 0;
	while (!fff.empty()) {
		int nex = fff.top();
		fff.pop();
		// pre -> nex
		// pre * ? == nex
		t++;
		int x, y;
		exgcd(pre, p, x, y);
		x = (x % p + p) % p;
		printf(" %lld", (long long)x * (nex / __gcd(pre, p)) % p);


		pre = nex;
	}
	if (!ban[0]) printf(" 0\n");
	else printf("\n");
	return 0;
}
