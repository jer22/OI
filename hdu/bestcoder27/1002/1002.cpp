#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n, m;
long long dist[100005];
int main() {
	freopen("1002.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		for (int i = 2; i <= n; i++) {
			cin >> dist[i];
			dist[i] += dist[i - 1];
		}
		int start, mid, end;
		for (int i = 1; i <= m; i++) {
			long long ans = 0;
			scanf("%d %d", &mid, &end);
			start = (i - 1) % n + 1;
			if (start <= mid) {
				ans += dist[mid] - dist[start];
				if (mid <= end) {
					ans += dist[end] - dist[mid];
				} else {
					ans += dist[n] - dist[end];
					ans += dist[n] - dist[mid];
				}
			} else {
				ans += (dist[n] - dist[start]) * 2 + dist[start] - dist[mid];
				if (mid >= end) {
					ans += dist[mid] - dist[end];
				} else {
					ans += dist[mid] + dist[end];
				}
			}
			cout << ans << endl;
		}
	}

	return 0;
}
