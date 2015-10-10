#include <bits/stdc++.h>

using namespace std;

int n;
int arr[2005], t[2005];
int v[2005], siz[2005], dist[2005], tr[2005][2];
int root[2005];
int l[2005], r[2005];
int tot;

int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (v[x] < v[y]) swap(x, y);
	tr[x][1] = merge(tr[x][1], y);
	siz[x] = siz[tr[x][0]] + siz[tr[x][1]] + 1;
	if (dist[tr[x][1]] > dist[tr[x][0]]) swap(tr[x][0], tr[x][1]);
	dist[x] = dist[tr[x][1]] + 1;
	return x;
}

int top(int x) {
	return v[x];
}

int size(int x) {
	return siz[x];
}

int newNode(int x) {
	v[++tot] = x;
	siz[tot] = 1;
	tr[tot][0] = tr[tot][1] = dist[tot] = 0;
	return tot;
}

void pop(int &x) {
	x = merge(tr[x][0], tr[x][1]);
}

int solve() {
	tot = 0;
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		root[++cnt] = newNode(t[i]);
		l[cnt] = r[cnt] = i;
		while (cnt > 1 && top(root[cnt]) < top(root[cnt - 1])) {
			cnt--;
			root[cnt] = merge(root[cnt], root[cnt + 1]);
			r[cnt] = r[cnt + 1];
			while (size(root[cnt]) * 2 > r[cnt] - l[cnt] + 2)
				pop(root[cnt]);
		}
	}
	int ans = 0;
	for (int i = 1; i <= cnt; i++) {
		int tt = top(root[i]);
		for (int j = l[i]; j <= r[i]; j++)
			ans += abs(tt - t[j]);
	}
	return ans;
}

int main() {
	freopen("1592.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &arr[i]);
	for (int i = 1; i <= n; i++) {
		t[i] = arr[i];
	}
	int ans = solve();
	for (int i = 1; i <= n; i++)
		t[i] = arr[n - i + 1];
	ans = min(ans, solve());
	cout << ans << endl;
	return 0;
}
