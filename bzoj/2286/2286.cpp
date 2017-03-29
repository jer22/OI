#include <bits/stdc++.h>

using namespace std;

const int MAXN = 250005;
const long long INF = LLONG_MAX;

struct Edge{
	int to;
	long long v;
	Edge() {}
	Edge(int a, long long b) : to(a), v(b) {}
};

int n, q;
vector<Edge> edges[MAXN];
long long val[MAXN];
int fa[MAXN][20], deep[MAXN];
int pos[MAXN], tot = 0;

int getlca(int x, int y) {
	if (deep[x] < deep[y]) swap(x, y);
	int tmp = deep[x] - deep[y];
	for (int i = 0; i <= 18; i++)
		if ((1 << i) & tmp) x = fa[x][i];
	for (int i = 18; i >= 0; i--)
		if (fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	if (x == y) return x;
	return fa[x][0];
}

void dfs(int x, int pre) {
	fa[x][0] = pre;
	pos[x] = ++tot;
	deep[x] = deep[pre] + 1;
	for (int i = 1; i <= 18; i++)
		fa[x][i] = fa[fa[x][i - 1]][i - 1];
	for (int i = 0; i < edges[x].size(); i++) {
		Edge e = edges[x][i];
		if (e.to == pre) continue;
		val[e.to] = min(val[x], e.v);
		dfs(e.to, x);
	}
}

int arr[MAXN];
inline bool cmp(int a, int b) { return pos[a] < pos[b]; }
vector<int> vedges[MAXN];
vector<int> p;
int stk[MAXN];
bool vis[MAXN];
bool po[MAXN];

long long dfsdfs(int x) {
	if (po[x]) return val[x];
	long long sum = 0;
	for (int i = 0; i < vedges[x].size(); i++) {
		int nex = vedges[x][i];
		sum += dfsdfs(nex);
	}
	return min(val[x], sum);
}

int main() {
	freopen("2286.in", "r", stdin);
	scanf("%d", &n);
	int a, b;
	long long c;
	for (int i = 1; i < n; i++) {
		scanf("%d %d %lld", &a, &b, &c);
		edges[a].push_back(Edge(b, c));
		edges[b].push_back(Edge(a, c));
	}
	val[1] = INF;
	dfs(1, 0);
	int k, x;
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &k);
		for (int i = 1; i <= k; i++) {
			scanf("%d", &arr[i]);
			po[arr[i]] = 1;
		}
		sort(arr + 1, arr + k + 1, cmp);
		vedges[0].clear();
		for (int i = 0; i < p.size(); i++) {
			vedges[p[i]].clear();
			vis[p[i]] = 0;
		}
		p.clear();
		int cnt = 1, top = 1;
		for (int i = 2; i <= k; i++)
			if (getlca(arr[i], arr[cnt]) != arr[cnt]) arr[++cnt] = arr[i];
		stk[1] = 1;
		for (int i = 1; i <= cnt; i++){
			int tmp = getlca(arr[i], stk[top]);
			while (1) {
				if (deep[stk[top - 1]] <= deep[tmp]){
					if (top > 1) {
						vedges[tmp].push_back(stk[top]);
						if (!vis[tmp]) {
							vis[tmp] = 1;
							p.push_back(tmp);
						}
					}
					top--;
					if (stk[top] != tmp) stk[++top] = tmp;
					break;
				}
				vedges[stk[top - 1]].push_back(stk[top]);
				if (!vis[stk[top - 1]]) {
					vis[stk[top - 1]] = 1;
					p.push_back(stk[top - 1]);
				}
				top--;
			}
			if (stk[top] != arr[i]) stk[++top] = arr[i];
		}
		while (top > 1){
			vedges[stk[top - 1]].push_back(stk[top]);
			if (!vis[stk[top - 1]]) {
				vis[stk[top - 1]] = 1;
				p.push_back(stk[top - 1]);
			}
			top--;
		}
		long long ans = dfsdfs(1);
		for (int i = 1; i <= k; i++)
			po[arr[i]] = 0;
		printf("%lld\n", ans);
		// for (int i = 1; i <= n; i++) {
		// 	for (int j = 0; j < vedges[i].size(); j++)
		// 		cout << i << ' ' << vedges[i][j] << endl;
		// }
	}

	return 0;
}
