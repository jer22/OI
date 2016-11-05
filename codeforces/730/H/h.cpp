#include <bits/stdc++.h>

using namespace std;

const int MAXN = 105;

int n, m;
string s[MAXN];
int sel[MAXN];
bool seld[MAXN];

bool check(int idx) {
	for (int i = 2; i <= m; i++)
		if (s[sel[i]][idx] != s[sel[1]][idx]) return false;
	return true;
}

bool good(string str, string pat) {
	if (str.size() != pat.size()) return false;
	for (int i = 0; i < pat.size(); i++) {
		if (pat[i] == '?') continue;
		if (pat[i] != str[i]) return false;
	}
	return true;
}

int main() {
	// freopen("h.in", "r", stdin);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> s[i];
	for (int i = 1; i <= m; i++) {
		cin >> sel[i];
		seld[sel[i]] = 1;
	}
	int siz = s[sel[1]].size();
	for (int i = 2; i <= m; i++) {
		if ((int)s[sel[i]].size() != siz) {
			cout << "No" << endl;
			return 0;
		}
	}
	string pat = "";
	for (int i = 0; i < siz; i++) {
		if (check(i)) pat += s[sel[1]][i];
		else pat += '?';
	}
	for (int i = 1; i <= n; i++) {
		if (seld[i]) continue;
		if (good(s[i], pat)) {
			cout << "No" << endl;
			return 0;
		}
	}
	cout << "Yes" << endl << pat << endl;
	return 0;
}
