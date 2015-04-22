#include <bits/stdc++.h>

#define MAXN 2005
#define S 0
#define T 2003
#define p(i, j) (i - 1) * m + j

using namespace std;

const long long INF = (1ll << 50);

struct Edge{
	int to;
	long long cap;
	Edge() {}
	Edge(int a, long long b) : to(a), cap(b) {}
};

int n, m;
vector<Edge> edges;
vector<int> G[MAXN];
int layer[MAXN];
int cur[MAXN];

inline void addEdge(int from, int to, long long cap) {
	edges.push_back(Edge(to, cap));
	edges.push_back(Edge(from, 0));
	int e = edges.size();
	G[from].push_back(e - 2);
	G[to].push_back(e - 1);
}

inline bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(S);
	layer[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > 0) {
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

inline long long find(int x, long long a) {
	if (x == T || a == 0) return a;
	long long flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap))) != 0) {
			e.cap -= f;
			edges[G[x][i] ^ 1].cap += f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

long long ans;
inline long long dinic() {
	ans = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		ans += find(S, INF);
	}
	return ans;
}

long long arr[45][45];
int dir[4][2] = {{0, 1}, {0, -1}, {-1, 0}, {1, 0}};
inline bool check(long long x) {
	edges.clear();
	memset(G, 0, sizeof(G));
	long long tot = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if ((i + j) & 1) {
				addEdge(0, p(i, j), x - arr[i][j]);
				tot += x - arr[i][j];
				for (int k = 0; k < 4; k++) {
					int nx = i + dir[k][0];
					int ny = j + dir[k][1];
					if (nx >= 1 && nx <= n && ny >= 1 && ny <= m)
						addEdge(p(i, j), p(nx, ny), INF);
				}
			} else addEdge(p(i, j), T, x - arr[i][j]);
		}
	}
	dinic();
	return ans == tot;
}

int main() {
	freopen("2756.in", "r", stdin);
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d %d", &n, &m);
		int cnt1 = 0, cnt2 = 0;
		long long sum1 = 0, sum2 = 0;
		long long mx = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%lld", &arr[i][j]);
				mx = max(arr[i][j], mx);
				if ((i + j) & 1) cnt1++, sum1 += arr[i][j];
				else cnt2++, sum2 += arr[i][j];
			}
		}
		if (cnt1 != cnt2) {
			long long x = (sum1 - sum2) / (cnt1 - cnt2);
			if (x >= mx && check(x)) printf("%lld\n", ans);
			else printf("-1\n");
		} else {
			if (sum1 != sum2) {
				printf("-1\n");
				continue;
			}
			long long l = mx, r = 2000000000;
			long long res = INF;;
			while (l <= r) {
				long long mid = l + r >> 1;
				if (check(mid)) {
					res = min(res, ans);
					r = mid - 1;
				}
				else l = mid + 1;
			}
			printf("%lld\n", res);
		}
	}
	return 0;
}
