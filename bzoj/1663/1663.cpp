#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
struct Node{
	int pos, tim;
	bool operator < (const Node &n) const {
		return tim < n.tim;
	}
}p[405];
int d[405][405];
vector<int> edges[405];
int dist[405];
bool vis[405];

int spfa() {
	queue<int> q;
	q.push(0);
	vis[0] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			if (dist[current] + 1 > dist[edges[current][i]]) {
				dist[edges[current][i]] = dist[current] + 1;
				if (!vis[edges[current][i]]) {
					vis[edges[current][i]] = 1;
					q.push(edges[current][i]);
				}
			}
		}
		vis[current] = 0;
	}
	int ans = 0;
	for (int i = 1; i <= n; i++)
		ans = max(ans, dist[i]);
	return ans;
}

int main() {
	freopen("1663.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &p[i].tim);
		p[i].pos = i;
	}
	sort(p + 1, p + n + 1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &d[i][j]);
	for (int i = 1; i <= n; i++)
		d[0][i] = d[1][i];
	p[0].pos = p[0].tim = 0;
	for (int i = 0; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			if (p[i].tim + d[p[i].pos][p[j].pos] <= p[j].tim)
				edges[i].push_back(j);
	int ans = spfa();
	printf("%d\n", ans);
	return 0;
}
