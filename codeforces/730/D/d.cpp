#include <bits/stdc++.h>

using namespace std;

const int MAXN = 200005;

int n;
long long m;
long long len[MAXN], tim[MAXN];
vector<long long> ans;
int main() {
	freopen("d.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> len[i];
	for (int i = 1; i <= n; i++)
		cin >> tim[i];
	long long tot = 0;
	long long left = 0;
	long long now = 0;
	for (int i = 1; i <= n; i++) {
		if (len[i] > tim[i]) {
			cout << -1 << endl;
			return 0;
		}
		if (left >= len[i]) {
			now += len[i];
			left -= len[i];
			continue;
		}
		len[i] -= left;
		tim[i] -= left;
		now += left;
		left = 0;
		if ((len[i] << 1ll) <= tim[i]) {
			now += len[i] << 1ll;
			continue;
		}
		long long t = tim[i] - len[i];
		len[i] -= t;
		tim[i] -= (t << 1ll);
		now += (t << 1ll);
		long long tmp = now;
		while (ans.size() < 100005 && tmp < now + tim[i]) {
			ans.push_back(tmp);
			tmp += m;
		}
		tot += len[i] / m;
		left = len[i] % m;
		now += len[i];
		if (left) {
			tot++;
			left = m - left;
		}
	}
	cout << tot << endl;
	if (tot <= 100000) {
		sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)
			cout << ans[i] << " \n"[i == ans.size() - 1];
	}

	return 0;
}
