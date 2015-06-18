#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int T;
string arr, brr;
int idx;

string dfs1() {
	if (idx >= arr.length()) return "";
	string ans = "(";
	vector<string> s;
	while (arr[idx] != '1') {
		idx++;
		s.push_back(dfs1());
	}
	// idx++;
	sort(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++)
		ans += s[i];
	ans += ")";
	idx++;
	return ans;
}

string dfs2() {
	if (idx >= brr.length()) return "";
	string ans = "(";
	vector<string> s;
	while (brr[idx] != '1') {
		idx++;
		s.push_back(dfs2());
	}
	sort(s.begin(), s.end());
	for (int i = 0; i < s.size(); i++)
		ans += s[i];
	ans += ")";
	idx++;
	return ans;
}

bool solve() {
	if (arr.length() != brr.length()) return false;
	idx = 0;
	string a = dfs1();
	idx = 0;
	string b = dfs2();
	return a == b;
}

int main() {
	freopen("1635.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		cin >> arr >> brr;
		bool flag = solve();
		if (flag) printf("same\n");
		else printf("different\n");
	}


	return 0;
}
