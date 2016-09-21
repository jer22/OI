#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5005;
const long long INF = 1e18;

int n, st, ed;
long long x[MAXN];
long long a[MAXN], b[MAXN], c[MAXN], d[MAXN];

long long go(int i, int j) {
	long long ans = abs(x[i] - x[j]);
	if (i < j) ans += d[i] + a[j];
	else ans += c[i] + b[j];
	return ans;
}

int nex[MAXN];
int main() {
	freopen("b.in", "r", stdin);
	cin >> n >> st >> ed;
	for (int i = 1; i <= n; i++)
		cin >> x[i];
	for (int i = 1; i <= n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	for (int i = 1; i <= n; i++)
		cin >> d[i];

	long long ans = go(st, ed);
	nex[st] = ed;
	for (int i = 1; i <= n; i++) {
		if (i == st || i == ed) continue;
		long long best = INF;
		int pre = st;
		for (int j = st; j != ed; j = nex[j]) {
			long long t = go(j, i) + go(i, nex[j]) - go(j, nex[j]);
			if (t < best) best = t, pre = j;
		}
		nex[i] = nex[pre];
		nex[pre] = i;
		ans += best;
	}
	cout << ans << endl;



	return 0;
}
