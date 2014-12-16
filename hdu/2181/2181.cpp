#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> edges[22];
bool vis[22];
int pre[22];
int m;
int cnt = 0;
int cas = 1;

void print() {
	printf("%d:  %d", cas++, m);
	for (int i = 0; i < cnt; i++) {
		printf(" %d", pre[i]);
	}
	printf(" %d\n", m);
}

void dfs(int i, int step) {
	if (step == 20) {
		for (int j = 0; j < 3; j++) {
			if (edges[i][j] == m) {
				print();
				return;
			}	
		}
		return;
	}
	for (int j = 0; j < 3; j++) {
		int to = edges[i][j];
		if ((!vis[to])) {
			vis[to] = 1;
			pre[cnt++] = to;
			dfs(to, step + 1);
			pre[--cnt] = 0;
			vis[to] = 0;
		}
	}
}

int main() {
	freopen("2181.in", "r", stdin);
	int a, b, c;
	for (int i = 1; i <= 20; i++) {
		scanf("%d %d %d", &a, &b, &c);
		edges[i].push_back(a);
		edges[i].push_back(b);
		edges[i].push_back(c);
	}
	while (~scanf("%d", &m) && m) {
		memset(vis, 0, sizeof(vis));
		memset(pre, 0, sizeof(pre));
		vis[m] = 1;
		cas = 1;
		dfs(m, 1);
	}

	return 0;
}
