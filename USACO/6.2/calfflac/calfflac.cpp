/*
ID:shijiey1
LANG:C++
PROG:calfflac
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

char str[20005];
int len = 0;
int main() {
	freopen("calfflac.in", "r", stdin);
	freopen("calfflac.out", "w", stdout);
	while (~scanf("%c", &str[len++]));
	int idx1, idx2, ans = 0, maxnum = 0;
	int a, b;
	for (int i = 0; i < len; i++) {
		if (!isalpha(str[i])) continue;
		a = i, b = i + 1;
		int cnt = 0, n = 0;
		while (a >= 0 && b < len) {
			if (!isalpha(str[a])) {
				a--;
				continue;
			}
			if (!isalpha(str[b])) {
				b++;
				continue;
			}
			char l = tolower(str[a]);
			char r = tolower(str[b]);
			if (l == r) {
				cnt += 2;
				n++;
				if (cnt > ans || n > maxnum) {
					ans = cnt;
					maxnum = n;
					idx1 = a, idx2 = b;
				}
				a--, b++;
			} else break;
		}
	}
	for (int i = 1; i < len - 1; i++) {
		if (!isalpha(str[i])) continue;
		a = i - 1, b = i + 1;
		int cnt = 0, n = 1;
		while (a >= 0 && b < len) {
			if (!isalpha(str[a])) {
				a--;
				continue;
			}
			if (!isalpha(str[b])) {
				b++;
				continue;
			}
			char l = tolower(str[a]);
			char r = tolower(str[b]);
			if (l == r) {
				cnt += 2;
				n++;
				if (cnt > ans || n > maxnum) {
					ans = cnt;
					maxnum = n;
					idx1 = a, idx2 = b;
				}
				a--, b++;
			} else break;
		}
	}
	ans = 0;
	for (int i = idx1; i <= idx2; i++)
		if (isalpha(str[i])) ans++;
	cout << ans << endl;
	for (int i = idx1; i <= idx2; i++)
		cout << str[i];
	cout << endl;
	return 0;
}
