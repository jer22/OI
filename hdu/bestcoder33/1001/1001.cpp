#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, b;
int map[255];
char h[255];
int main() {
	freopen("1001.in", "r", stdin);
	for (int i = '0'; i <= '9'; i++)
		map[i] = i - '0';
	for (int i = 'a'; i <= 'z'; i++)
		map[i] = i - 'a' + 10;
	for (int i = 0; i <= 9; i++) {
		h[i] = i + '0';
	}
	for (int i = 'a'; i <= 'z'; i++) {
		h[i - 'a' + 10] = i;
	}
	while (~scanf("%d %d", &n, &b)) {
		char c;
		int t;
		getchar();
		int ans[205];
		memset(ans, 0, sizeof(ans));
		char str[205];
		int l = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			int len = strlen(str);
			l = max(l, len);
			for (int j = len - 1; j >= 0; j--) {
				t = map[str[j]];
				ans[len - j - 1] += t;
				ans[len - j - 1] %= b;
			}

		}
		bool flag = false;
		for (int i = l - 1; i >= 0; i--) {
			if (!flag && ans[i] == 0) continue;
			if (ans[i] != 0) flag = true;
			cout << h[ans[i]];
		}
		if (!flag) cout << 0;
		cout << endl;
	}


	return 0;
}
