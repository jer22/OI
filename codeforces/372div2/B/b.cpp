#include <bits/stdc++.h>

using namespace std;

string s;
int cnt[255];

int main() {
	freopen("b.in", "r", stdin);
	cin >> s;
	if (s.size() < 26) {
		printf("-1\n");
		return 0;
	}
	int idx1 = -1, idx2 = 24;
	int flag = 0;
	for (int i = 0; i <= 24; i++) {
		cnt[s[i]]++;
		if (s[i] != '?' && cnt[s[i]] == 2) flag++;
	}

	bool has = false;
	for (idx2 = 25; idx2 < s.size(); idx2++) {
		if (idx1 != -1) {
			cnt[s[idx1]]--;
			if (s[idx1] != '?' && cnt[s[idx1]] == 1) flag--;
		}
		idx1++;
		cnt[s[idx2]]++;
		if (s[idx2] != '?' && cnt[s[idx2]] == 2) flag++;
		if (!flag) {
			has = true;
			break;
		}
	}
	if (!has) {
		cout << -1 << endl;
		return 0;
	}
	queue<char> q;
	for (char c = 'A'; c <= 'Z'; c++) {
		if (!cnt[c]) q.push(c);
	}
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '?') {
			if (i >= idx1 && i <= idx2) {
				s[i] = q.front();
				q.pop();
			} else {
				s[i] = 'A';
			}
			
		}
	}
	cout << s << endl;

	return 0;
}
