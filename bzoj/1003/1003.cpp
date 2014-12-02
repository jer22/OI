#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define MAXN 110

using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
	int v;
	int to;
};

int n, m, k;
bool flag[MAXN][MAXN];
bool done[MAXN];
int dist[MAXN];
int dp[MAXN];
vector<Edge> e[22];

int spfa(int s, int t) {
	memset(dist, INF, sizeof(dist));
	memset(done, false, sizeof(done));
	queue<int> buff;
	for (int i = 1; i <= m; i++) {
		for (int j = s; j <= t; j++) {
			if (!flag[i][j]) {
				done[i] = true;
				break;
			}
		}
	}
	dist[1] = 0;
	buff.push(1);
	done[1] = true;
	Edge* temp;
	while (!buff.empty()) {
		int current = buff.front();
		for (int i = 0; i < (int)e[current].size(); i++) {
			temp = &e[current][i];
			/*if (done[temp -> to]) continue;*/
			if (dist[current] + temp -> v < dist[temp -> to]) {
				dist[temp -> to] = dist[current] + temp -> v;
				if (!done[temp -> to]) {
					buff.push(temp -> to);
					done[temp -> to] = 1;
				}
			}
		}
		done[current] = false;
		buff.pop();
	}
	if (dist[m] == INF) return dist[m];
	else return dist[m] * (t - s + 1);
}

int main( void ) {
	memset(flag, true, sizeof(flag));
	int tt, d;
	int x, y, z;
	scanf("%d %d %d %d", &n, &m, &k, &tt);
	Edge temp;
	for (int i = 1; i <= tt; i++) {
		scanf("%d %d %d", &x, &y, &z);
		temp.v = z;
		temp.to = y;
		e[x].push_back(temp);
		temp.to = x;
		e[y].push_back(temp);
	}
	scanf("%d", &d);
	int p, a, b;
	for (int i = 1; i <= d; i++) {
		scanf("%d %d %d", &p, &a, &b);
		for (int j = a; j <= b; j++) {
			flag[p][j] = false;
		}
	}

	for (int i = 1; i <= n; i++) {
		dp[i] = spfa(1, i);
		for (int j = 2; j < i; j++) {
			dp[i] = min(dp[i], dp[j] + spfa(j + 1, i) + k);
		}
	}
	printf("%d", dp[n]);
	return 0;
}
