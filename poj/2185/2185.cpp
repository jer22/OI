#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int n, m;
char s[10005][77];
char tmp[77];
int Next[10005];
int cnt[77];
int w;

bool equals(int x, int y) {
	for (int i = 0; i < w; i++)
		if (s[x][i] != s[y][i]) return false;
	return true;
}

void getNext() {
	memset(Next, 0, sizeof(Next));
	int i = 0, j = -1;
	Next[0] = -1;
	while (i < n) {
		if (j == -1 || equals(i, j))
			Next[++i] = ++j;
		else j = Next[j];
	}
}

int main() {
	freopen("2185.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; i++) {
			scanf("%s", s[i]);
			strcpy(tmp, s[i]);
			for (int j = m - 2; j >= 0; j--) {
				tmp[j + 1] = 0;
				bool flag = true;
				for (int x = 0, y = 0; s[i][y]; x++, y++) {
					if (!tmp[x]) x = 0;
					if (tmp[x] != s[i][y]) {
						flag = false;
						break;
					}
				}
				if (flag) cnt[j]++;
			}
		}
		w = m;
		for (int i = 0; i < m; i++) {
			if (cnt[i] == n) {
				w = i + 1;
				break;
			}
		}
		getNext();
		printf("%d\n", w * (n - Next[n]));
	}
	return 0;
}
