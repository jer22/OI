#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

int cnt[26];
int main() {
    string s;
	cin >> s;
	for (int i = 0; i < s.size(); i++) {
		cnt[s[i] - 'a']++;
	}
	int maxnum = -1, minnum = 0x3f3f3f3f;
	for (int i = 0; i < 26; i++) {
		maxnum = max(maxnum, cnt[i]);
		if (cnt[i])
			minnum = min(minnum, cnt[i]);
	}
	int t = maxnum - minnum;
	bool flag = true;
	for (int i = 2; i * i <= t; i++) {
		if (!(t % i)) {
			flag = false;
			break;
		}
	}
	if (flag && t != 1 && t != 0) {
		printf("Lucky Word\n%d\n", t);
	} else {
		printf("No Answer\n0\n");
	}
	return 0;
}
