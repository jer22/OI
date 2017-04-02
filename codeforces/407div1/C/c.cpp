#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1005;

int n, k;
bool vis[MAXN << 1];
int dist[MAXN << 1];
int main() {
	freopen("c.in", "r", stdin);
	scanf("%d %d", &n, &k);
	int x;
	memset(dist, 0x3f, sizeof(dist));
	queue<int> q;
	bool f = 0;
	int mi = 0x3f3f3f3f;
	int mx = -0x3f3f3f3f;
	for (int i = 0; i < k; i++) {
		scanf("%d", &x);
		if (!vis[x - n + 1001]) {
			vis[x - n + 1001] = 1;
			q.push(x - n);
		}
		dist[x - n + 1001] = 1;
		if (x == n) {
			f = 1;
			break;
		}
		mi = min(mi, x);
		mx = max(mx, x);
	}
	if (f) {
		cout << 1 << endl;
		return 0;
	}
	if (n < mi || n > mx) {
		cout << -1 << endl;
		return 0;
	}
	int ans = -1;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i <= 2002; i++) {
			if (!vis[i]) continue;
			int nx = cur + i - 1001;
			if (nx >= -1001 && nx <= 1001) {
				if (!nx) {
					ans = dist[cur + 1001] + 1;
					while (!q.empty()) q.pop();
					break;
				}
				if (dist[nx + 1001] == 0x3f3f3f3f) {
					dist[nx + 1001] = dist[cur + 1001] + 1;
					q.push(nx);
				}
				
			}
		}
	}
	cout << ans << endl;


	return 0;
}
