#include <bits/stdc++.h>

using namespace std;

int n;
int arr[3005];
int tot = 0;
int root[3005];
int tr[3005][2];
int l[3005], r[3005], dist[3005], siz[3005];
int v[3005];

int merge(int x, int y) {
	if (!x || !y) return x + y;
	if (v[x] < v[y]) swap(x, y);
	tr[x][1] = merge(tr[x][1], y);
	siz[x] = siz[tr[x][0]] + siz[tr[x][1]] + 1;
	if (dist[tr[x][1]] > dist[tr[x][0]]) swap(tr[x][0], tr[x][1]);
	dist[x] = dist[tr[x][1]] + 1;
	return x;
}
void pop(int &x) { x = merge(tr[x][0], tr[x][1]); }
int newNode(int x) {
	v[++tot] = x;
	siz[tot] = 1;
	dist[tot] = 0;
	tr[tot][0] = tr[tot][1] = 0;
	return tot;
}

int main() {
	freopen("e.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];
		arr[i] -= i;
	}
	int cnt = 0;
	for (int i = 1; i <= n; i++) {
		cnt++;
		root[cnt] = newNode(arr[i]);
		l[cnt] = r[cnt] = i;
		while (cnt > 1 && v[root[cnt]] < v[root[cnt - 1]]) {
			cnt--;
			root[cnt] = merge(root[cnt], root[cnt + 1]);
			r[cnt] = r[cnt + 1];
			while (siz[root[cnt]] * 2 > r[cnt] - l[cnt] + 2)
				pop(root[cnt]);
		}
	}
	long long ans = 0;
	for (int i = 1; i <= cnt; i++) {
		int t = v[root[i]];
		for (int j = l[i]; j <= r[i]; j++) {
			ans += abs(arr[j] - t);
		}
	}
	cout << ans << endl;
	return 0;
}
