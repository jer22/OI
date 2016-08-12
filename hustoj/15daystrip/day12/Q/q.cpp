#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MOD = 20090717;
const int MAXLEN = 100005;
const int INF = 0x3f3f3f3f;

struct Edge{
	int to, v;
	Edge() {}
	Edge(int a, int b) : to(a), v(b) {}
};

int n, m, tot, root;
int nex[MAXLEN][2], fail[MAXLEN], tag[MAXLEN], id[MAXLEN];
int position[15];

vector<Edge> edges[MAXLEN];

void addEdge(int x, int y, int c) {
	edges[x].push_back(Edge(y, c));
}

int dist[MAXLEN];
int distan[15][15];
bool vis[MAXLEN];
void spfa(int s) {
	queue<int> q;
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	q.push(position[s]);
	dist[position[s]] = 0;
	vis[position[s]] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < 2/*edges[current].size()*/; i++) {
			int e = nex[current][i];
			// Edge e = edges[current][i];
			// if (current == 4) cout << e << endl;
			if (tag[e] == 2) {
				continue;
			}
			if (dist[current] + 1 < dist[e]) {
				dist[e] = dist[current] + 1;
				if (tag[e] == 1) {
					distan[s][id[e]] = dist[e];
				}
				if (!vis[e]) {
					vis[e] = 1;
				}
				q.push(e);
			}
		}
		vis[current] = false; // current已经出队
	}
}

void insert(char str[], int idd, int k) {
	int len = strlen(str);
	int pos = root;
	for (int i = 0; i < len; i++) {
		int t = str[i] - '0';
		if (!nex[pos][t]) {
			nex[pos][t] = ++tot;
			addEdge(pos, nex[pos][t], 1);
		}
		pos = nex[pos][t];
	}
	tag[pos] = k;
	if (k == 1) {
		id[pos] = idd;
		position[idd] = pos;
	}
}

void build() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int p = q.front();
		q.pop();
		if (tag[fail[p]] == 2) tag[p] = 2;
		int t;
		for (int i = 0; i < 2; i++) {
			if (!(t = nex[p][i]))
				nex[p][i] = nex[fail[p]][i];
			else {
				fail[t] = p ? nex[fail[p]][i] : 0;
				addEdge(t, fail[t], 0);
				q.push(t);
			}
		}
	}
}

int dp[1050][15];
char sour[15][1005];
int main() {
	freopen("q.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		if (!n && !m) break;
		memset(distan, 0x3f, sizeof(distan));
		for (int i = 0; i <= MAXLEN - 2; i++)
			edges[i].clear();
		char str[MAXLEN];
		tot = root = 0;
		memset(id, 0, sizeof(id));
		memset(tag, 0, sizeof(tag));
		memset(nex, 0, sizeof(nex));
		
		for (int i = 0; i < n; i++) {
			scanf("%s", sour[i]);
			insert(sour[i], i, 1);
		}
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			insert(str, i, 2);
		}
		build();
		for (int i = 0; i < n; i++) {
			spfa(i);
		}
		memset(dp, 0x3f, sizeof(dp));
		for (int i = 0; i < n; i++) dp[1 << i][i] = strlen(sour[i]);
		for (int i = 1; i < (1 << n); i++) {
			for (int j = 0; j < n; j++) {
				if (dp[i][j] == INF) continue;
				for (int k = 0; k < n; k++) {
					dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + distan[j][k]);
				}
			}
		}
		int ans = INF;
		for (int i = 0; i < n; i++) {
			ans = min(ans, dp[(1 << n) - 1][i]);
			// cout << dp[(1 << n) - 1][i] << endl;
		}
		printf("%d\n", ans);

	}
	return 0;
}
