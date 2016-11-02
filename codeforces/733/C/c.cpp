#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 505;

int n, m;
int arr[MAXN], brr[MAXN];
int tot = 0;
vector<pii> ans;

void getans(int l, int r, int idx) {
	if (l == r) return;
	if (idx < r && arr[idx] > arr[idx + 1]) {
		for (int i = idx + 1; i <= r; i++)
			ans.push_back(mp(idx - tot, 1));
		for (int i = idx; i > l; i--)
			ans.push_back(mp(i - tot, 0));
	}
	else {
		for (int i = idx; i > l; i--)
			ans.push_back(mp(i - tot, 0));
		for (int i = idx + 1; i <= r; i++)
			ans.push_back(mp(l - tot, 1));
	}
	tot += r - l;
}

int main() {
	// freopen("c.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];
	cin >> m;
	for (int i = 1; i <= m; i++)
		cin >> brr[i];

	int l = 1, r;
	for (int i = 1; i <= m; i++) {
		int now = brr[i];
		int t = 0;

		r = l;
		for (; r <= n; r++) {
			t += arr[r];
			if (t >= now) break;
		}
		int idx = 0, mx = 0;
		for (int j = l; j <= r; j++) {
			if (arr[j] >= mx) {
				mx = arr[j];
				if ((j != l && arr[j] > arr[j - 1]) || (j != r && arr[j] > arr[j + 1]))
					idx = j;
			}
		}
		if (t != now || (r - l > 0 && !idx)) {
			cout << "NO" << endl;
			return 0;
		}
		getans(l, r, idx);
		l = r + 1;
	}
	if (r < n) {
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i].first << ' ' << "LR"[ans[i].second] << endl;
	return 0;
} 
