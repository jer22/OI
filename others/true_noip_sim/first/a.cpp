#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int arr[7];
int brr[7];

int change(string s) {
	if (s[0] == 'A') return 1;
	if (s[0] == 'J') return 11;
	if (s[0] == 'Q') return 12;
	if (s[0] == 'K') return 13;
	if (s.size() == 1) return s[0] - '0';
	return 10;
}

bool vis[7];
int ans[7];
int mxsc = -1;
int tt = 0;

void solve() {
	int sco = 0;
	int t = 0;
	for (int i = 1; i <= 5; i++) {
		if (arr[i] < brr[ans[i]]) sco++;
		else if (arr[i] > brr[ans[i]]) sco--;
		else t++;
	}
	if (sco > mxsc) {
		mxsc = sco;
		tt = t;
	} else if (sco == mxsc) {
		tt = max(tt, t);
	}
}

void dfs(int step) {
	if (step == 6) {
		solve();
	}
	for (int i = 1; i <= 5; i++) {
		if (!vis[i]) {
			vis[i] = 1;
			ans[step] = i;
			dfs(step + 1);
			vis[i] = 0;
		}
	}

}

int main() {
	freopen("a.in", "r", stdin);
	string s;
	for (int i = 1; i <= 5; i++) {
		cin >> s;
		arr[i] = change(s);
	}
	for (int i = 1; i <= 5; i++) {
		cin >> s;
		brr[i] = change(s);
	}
	memset(vis, 0, sizeof(vis));
	dfs(1);
	cout << mxsc << ' ' << tt << endl;
	return 0;
}
