#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

string name;
bool vis[256];
int main() {
	freopen("1001.in", "r", stdin);
	while (cin >> name) {
		int a = 0, b = 0, c = 0;
		int len = name.size();
		memset(vis, 0, sizeof(vis));
		if (len % 3) {
			printf("NO\n");
			continue;
		}
		int siz = len / 3;
		bool flag = true;
		char now = name[0];
		for (int i = 0; i < siz; i++) {
			if (name[i] != now) flag = false;
		}
		vis[now] = 1;
		if (!flag) {
			printf("NO\n");
			continue;
		}
		now = name[siz];
		for (int i = siz; i < siz + siz; i++) {
			if (vis[name[i]]) flag = false;
			if (name[i] != now) flag = false;
		}
		vis[now] = 1;
		if (!flag) {
			printf("NO\n");
			continue;
		}
		now = name[siz + siz];
		for (int i = siz + siz; i < len; i++) {
			if (vis[name[i]]) flag = false;
			if (name[i] != now) flag = false;
		}
		if (!flag) {
			printf("NO\n");
			continue;
		}
		printf("YES\n");
	}


	return 0;
}
