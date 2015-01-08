#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int T;
int n;
char s[11][66];
char p[66];
char ans[66];
map<string, bool> vis;
int nex[66];
void getNext() {
	int i = 0, j = -1;
	nex[0] = -1;
	int lenp = strlen(p);
	while (i < lenp) {
		if (j == -1 || p[i] == p[j])
			nex[++i] = ++j;
		else j = nex[j];
	}
}

bool kmp(int k) {
	int i = 0, j = 0;
	int lens = 60, lenp = strlen(p);
	while (i != lens && j != lenp) {
		if (j == -1 || s[k][i] == p[j]) {
			i++;
			j++;
		} else j = nex[j];
		if (j == lenp) return true;
	}
	return false;
}

int main() {
	freopen("3080.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
		vis.clear();
		memset(ans, 0, sizeof(ans));
		bool flag = false;
		for (int i = 60; i >= 3; i--) {
			for (int j = 0; j <= 60 - i; j++) {
				strncpy(p, s[0] + j, i);
				p[i] = '\0';
				string str = p;
				if (vis[str]) continue;
				vis[str] = 1;
				getNext();
				bool f = true;
				for (int k = 1; k < n; k++) {
					if (!kmp(k)) f = false;
				}
				if (f) {
					int lenans = strlen(ans);
					if (!lenans) strcpy(ans, p);
					else if (strcmp(ans, p) > 0) {
						strcpy(ans, p);
					}
					flag = true;
				}
			}
			if (flag) break;
		}
		if (!flag) printf("no significant commonalities\n");
		else printf("%s\n", ans);
	}

	return 0;
}
