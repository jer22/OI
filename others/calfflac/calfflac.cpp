#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define MAXN 20005

using namespace std;

int len = 0;
char str[MAXN];
char ss[20005];
int hash[20005];

bool isLetter(char c) {
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z') return 1;
	return 0;
}

bool equal(char a, char b) {
	if (a == b) return true;
	if (a + 'a' - 'A' == b) return true;
	if (a + 'A' - 'a' == b) return true;
	return false;
}

bool ispalin(int s, int e) {
	int mid = s + e >> 1;
	for (int i = s; i <= mid; i++) {
		if (!equal(ss[i], ss[e - i + s])) return false;
	}
	return true;
}

int main() {
	freopen("calfflac.in", "r", stdin);
	int t = 0;
	char c;
	while (~scanf("%c", &c)) {
		str[t++] = c;
	}
	for (int i = 0; i < strlen(str); i++) {
		if (!isLetter(str[i])) continue;
		hash[len] = i;
		ss[len++] = str[i];
	}
	int ans, s, e;
	bool flag;
	for (ans = len; ans > 0; ans--) {
		for (int i = 0; i <= len - ans; i++) {
			if (ispalin(i, i + ans - 1)) {
				flag = true;
				s = i;
				e = i + ans - 1;
				break;
			}
		}
		if (flag) break;
	}
	cout << ans << endl;
	for (int i = hash[s]; i <= hash[e]; i++)
		cout << str[i];
	cout << endl;
	return 0;
}
