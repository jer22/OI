#include <bits/stdc++.h>

using namespace std;

const int INF = 0x3f3f3f3f;
const int T = 100003;

int n, m;
int w[45][105];
int tot, c[45];

int dist[100005], pre[100005], f[100005];
bool vis[100005];
int q[1000005], head[100005];
int cnt = 1;
struct Edge{ int from, to, next, c, v;} e[3000005];
void ins(int u, int v, int w, int c) {
    cnt++;
    e[cnt].from = u; e[cnt].to = v;
    e[cnt].next = head[u]; head[u] = cnt;
    e[cnt].c = c; e[cnt].v = w;
}
void addEdge(int u,int v,int w,int c) {
	ins(u, v, w, c);
	ins(v, u, 0, -c);
}

bool spfa(int &flow, int &cost) {
	for (int i = 0; i <= T; i++)
		dist[i] = INF;
	dist[0] = 0;
	vis[0] = 1;
	pre[0] = 0;
	f[0] = INF;
	int h = 1, t = 1;
	q[t++] = 0;
	while (h < t) {
		int cur = q[h++];
		for (int i = head[cur]; i; i = e[i].next) {
			if (e[i].v && dist[cur] + e[i].c < dist[e[i].to]) {
				dist[e[i].to] = dist[cur] + e[i].c;
				pre[e[i].to] = i;
				f[e[i].to] = min(f[cur], e[i].v);
				if (!vis[e[i].to]) {
					vis[e[i].to] = 1;
					q[t++] = e[i].to;
				}
			}
		}
		vis[cur] = 0;
	}
	if (dist[T] == INF) return false;

	flow += f[T];
	cost += dist[T] * f[T];
	int a, b;
	for (int i = pre[T]; i; i = pre[e[i].from]) {
		e[i].v -= f[T];
		e[i ^ 1].v += f[T];
		if (!e[i].from) {
			int y = e[i].to;
			a = (y - 1) / tot + 1;
			b = y % tot + 1;
		}
	}
	for (int i = 1; i <= m; i++)
		addEdge((a - 1) * tot + b, n * tot + i, 1, b * w[i][a]);

	return true;
}

int main() {
	scanf("%d %d", &m, &n);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &c[i]);
		tot += c[i];
	}
	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &w[i][j]);
	for (int i = 1; i <= n * tot; i++)
		addEdge(0, i, 1, 0);
	for (int i = 1; i <= m; i++)
		addEdge(n * tot + i, T, c[i], 0);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			addEdge((i - 1) * tot + 1, n * tot + j, 1, w[j][i]);
	int flow = 0, cost = 0;
	while (spfa(flow, cost));
	printf("%d\n", cost);
	return 0;
}
