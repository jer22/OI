#include <bits/stdc++.h>

using namespace std;

string s;
int n;
int cnt[30], tmp[30];
int ans[1005];
bool check(int x) {
	memset(ans, 0, sizeof(ans));
	memcpy(tmp, cnt, sizeof(tmp));
	int idx = 0;
	for (int i = 0; i < n; i++) {
		while ((tmp[idx] <= 0) && idx < 26) idx++;
		if (idx >= 26) return true;
		ans[i] = idx;
		tmp[idx] -= x;
	}
	while ((tmp[idx] <= 0) && idx < 26) idx++;
	if (idx >= 26) return true;
	return false;
}

int main() {
	freopen("a.in", "r", stdin);
	cin >> s >> n;
	for (int i = 0; i < s.size(); i++)
		cnt[s[i] - 'a']++;
	for (int i = 1; i <= 1000; i++) {
		if (check(i)) {
			cout << i << endl;
			for (int i = 0; i < n; i++)
				printf("%c", 'a' + ans[i]);
			cout << endl;
			return 0;
		}
	}
	cout << "-1" << endl;


	return 0;
}
