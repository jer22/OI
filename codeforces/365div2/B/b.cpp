#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, k;
int val[100005];
int cap[100005];
bool vis[100005];
int nex[100005];
vector<long long> edges;
vector<int> notc;

void getnex() {
	int t = 0;
	for (int i = 1; i < n; i++) {
		while (vis[i] && i <= n) i++;
		nex[t] = i;
		t = i;
	}
}

int main() {
	// freopen("b.in", "r", stdin);
	cin >> n >> k;
	long long sum = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &val[i]);
		sum += val[i];
	}
	val[0] = val[n];
	val[n + 1] = val[1];

	long long sumk = 0;
	long long ans = 0;
	for (int i = 1; i <= k; i++) {
		scanf("%d", &cap[i]);
		vis[cap[i]] = 1;
		sumk += val[cap[i]];
	}
	vis[0] = vis[n];
	vis[n + 1] = vis[1];

	for (int i = 1; i <= n; i++) {
		if (vis[i]) {
			ans += val[i] * (sum - val[i]);
		} else {
			ans += val[i] * sumk;
			if (!vis[i - 1]) ans += val[i] * val[i - 1];
			if (!vis[i + 1]) ans += val[i] * val[i + 1];
		}
	}
	// cout << ans << endl;
	cout << ans / 2 << endl;

	return 0;
}
