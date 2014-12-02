#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>

#define MAXN 22

using namespace std;

int n;
string str[MAXN];
char head;

string combine(string s1, string s2) {
	string s = s1;
	bool flag = false;
	int i, j;
	for (/*i = 0; i < s.size(); i++*/i = s.size() - 1; i >= 0; i--) {
		for (j = 0; j < s.size() - i; j++) {
			if (s[i + j] != s2[j]) {
				break;
			}
		}
		if (j == s.size() - i) {
			flag = true;
			break;
		}
	}
	if (flag) {
		s.replace(i, s.size() - i, s2);
		if (s.size() == s1.size() || s.size() == s2.size()) {
			flag = false;
		}
	}
	
	if (flag) {
		return s;
	} else {
		return "0";
	}
}

int cnt[MAXN];
int ans = 0;
void dfs(string now) {
	string s = now;
	int t = s.size();
	ans = max(t, ans);
	for (int i = 0; i < n; i++) {
		if (cnt[i]) {
			s = combine(now, str[i]);
			// cout << s << '\n';
			if (s != "0") {

				cnt[i]--;
				dfs(s);
				cnt[i]++;
			}
		}
	}
}

int main() {
	freopen("1019.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		cnt[i] = 2;
	}
	for (int i = 0; i < n; i++) {
		cin >> str[i];
	}
	cin >> head;
	for (int i = 0; i < n; i++) {
		if (str[i][0] == head) {
			cnt[i]--;
			dfs(str[i]);
			cnt[i]++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
