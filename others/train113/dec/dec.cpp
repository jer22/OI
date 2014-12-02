#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>

#define MAXN  200010

using namespace std;

int n, k;
long long arr[MAXN];
map<long long, int> cnt;
map<long long, int> vis;
long long ans = 0;

int cmp(long long a, long long b) {
	return a>b;
}

int main() {
	freopen("dec.in", "r", stdin);
	freopen("dec.out", "w", stdout);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		cnt[arr[i]]++;
	}
	sort(arr, arr + n, cmp);
	for (int i = 0; i < n; i++) {
		if (!vis[arr[i]])
			ans += cnt[arr[i]] * cnt[arr[i] - k];
		vis[arr[i]] = 1;
	}
	cout << ans << endl;
	return 0;
}
