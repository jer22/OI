#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

int s, t;
int primeTable[10050];
int vis[10050];

void initPrimeTable() {
	memset(primeTable, 0, sizeof(primeTable));
	for (int i = 2; i < 10000; i++) {
		if (!primeTable[i]) {
			for (int j = i << 1; j < 10000; j += i) {
				primeTable[j] = 1;
			}
		}
	}
}

int step[10050];
void bfs(int start) {
	queue<int> q;
	q.push(start);
	while (!q.empty()) {
		int now = q.front();
		if (now == t) {
			printf("%d\n", step[t]);
			return;
		}
		q.pop();
		int a = now % 1000;
		for (int i = 1; i <= 9; i++) {
			int next = i * 1000 + a;
			if (!vis[next] && !primeTable[next]) {
				vis[next] = 1;
				step[next] = step[now] + 1;
				q.push(next);
			}
		}
		int b = now - (a / 100 * 100);
		for (int i = 0; i <= 9; i++) {
			int next = i * 100 + b;
			if (!vis[next] && !primeTable[next]) {
				vis[next] = 1;
				step[next] = step[now] + 1;
				q.push(next);
			}
		}
		int c = now - (now % 100) / 10 * 10;
		for (int i = 0; i <= 9; i++) {
			int next = i * 10 + c;
			if (!vis[next] && !primeTable[next]) {
				vis[next] = 1;
				step[next] = step[now] + 1;
				q.push(next);
			}
		}
		int d = now - (now % 10);
		for (int i = 0; i <= 9; i++) {
			int next = i + d;
			if (!vis[next] && !primeTable[next]) {
				vis[next] = 1;
				step[next] = step[now] + 1;
				q.push(next);
			}
		}
	}
}

int main() {
	freopen("prime.in", "r", stdin);
	// freopen("prime.out", "w", stdout);
	scanf("%d %d", &s, &t);
	initPrimeTable();
	vis[s] = 1;
	bfs(s);

	return 0;
}
