/*
ID:shijiey1
PROG:butter
LANG:C++
*/

/*
枚举每一个集合点，n次spfa。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
	int to, v;
};

int n, V, E;
int arr[505];
vector<Edge> edges[805];
void addEdge(int from, int to, int value) {
	Edge e;
	e.to = to;
	e.v = value;
	edges[from].push_back(e);
}

int dist[805];
int done[805];
void spfa(int s) {
	memset(dist, 0, sizeof(dist));
	memset(done, 0, sizeof(done));
	queue<int> q;
	for (int i = 0; i <= V; i++) {
		dist[i] = INF;
	}
	dist[s] = 0;
	done[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[current] + e.v < dist[e.to]) {
				dist[e.to] = dist[current] + e.v;
				if (!done[e.to]) {
					q.push(e.to);
					done[e.to] = 1;
				}
			}
		}
		done[current] = 0;
	}
}

int main() {
	freopen("butter.in", "r", stdin);
	freopen("butter.out", "w", stdout);
	scanf("%d %d %d", &n, &V, &E);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	int a, b, c;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &a, &b, &c);
		addEdge(a, b, c);
		addEdge(b, a, c);
	}
	int minans = INF;
	for (int i = 1; i <= V; i++) {
		spfa(i);
		int ans = 0;
		for (int i = 1; i <= n; i++) {
			ans += dist[arr[i]];
		}
		minans = min(ans, minans);
	}
	printf("%d\n", minans);
	return 0;
}
