#include <bits/stdc++.h>

using namespace std;

int n, t;
stack<int> cnt[200005];
int main() {
	// freopen("d.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> t;
		cnt[t].push(i);
	}
	vector<int> ans;
	int j = 0;
	for (int i = 1; i <= n; i++) {
		while (cnt[j].empty() && j >= 3) j -= 3;
		if (cnt[j].empty()) {
			cout << "Impossible" << endl;
			return 0;
		}
		ans.push_back(cnt[j].top());
		cnt[j++].pop();
	}
	cout << "Possible" << endl;
	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << " \n"[i == ans.size() - 1];
	return 0;
}
