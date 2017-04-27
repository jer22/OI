#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 100005;

int T, lens, lent;
char s[MAXN << 1], t[MAXN << 1];
int nex[MAXN], ext[MAXN];

void extend_kmp() {
	int p, r = nex[0] = lent;
	for (int i = 1, j = -1; i < lent; ++i, --j) {
		if (j == -1 || i + nex[i - p] >= r) {
			if (j == -1) r = i, j = 0;
			while (r < lent && t[r] == t[j]) ++r, ++j;
			nex[i] = j;
			p = i;
		} else nex[i] = nex[i - p];
	}
	for (int i = 0, j = -1; i < lens; ++i, --j) {
		if (j == -1 || i + nex[i - p] >= r) {
			if (j == -1) r = i, j = 0;
			while (r < lens && j < lent && s[r] == t[j]) ++r, ++j;
			ext[i] = j;
			p = i;
		} else ext[i] = nex[i - p];
	}
}

int main() {
	freopen("4333.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%s", s);
		lens = lent = strlen(s);
		strcpy(t, s);
		strcpy(s + lens, s);
		lens <<= 1;
		extend_kmp();
		int k = lens >> 1;
		for (int i = 1; i < lent; i++) {
			if (ext[i] >= lent) {
				k = i;
				break;
			}
		}
		int a = 0, b = 0, c = 0;
		for (int i = 0; i < k; i++) {
			if (ext[i] >= lent) b++;
			else {
				if (t[ext[i]] > s[i + ext[i]]) a++;
				else c++;
			}
		}
		printf("Case %d: %d %d %d\n", cas, a, b, c);
	}

	return 0;
}
