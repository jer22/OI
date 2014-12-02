/*
ID:shijiey1
PROG:race3
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

int V = 0;
vector<int> edges[55];
vector<int> t_edges[55];
void addEdge(int a, int b) {
	edges[a].push_back(b);
	t_edges[a].push_back(b);
	t_edges[b].push_back(a);
}

int done[55];
int dist[55];
bool spfa(int k) {
	for (int i = 0; i <= V; i++) {
		dist[i] = INF;
	}
	dist[0] = 0;
	memset(done, 0, sizeof(done));
	queue<int> q;
	done[0] = 1;
	q.push(0);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			int v = edges[current][i];
			if (v == k) continue;
			if (dist[v] > dist[current] + 1) {
				dist[v] = dist[current] + 1;
				if (!done[v]) {
					done[v] = 1;
					q.push(v);
				}
			}
		}
		done[current] = 0;
	}
	return dist[V - 1] == INF;
}

bool spfa2(int s) {
	for (int i = 0; i <= V; i++) {
		dist[i] = INF;
	}
	dist[s] = 0;
	memset(done, 0, sizeof(done));
	queue<int> q;
	done[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			int v = edges[current][i];
			if (v == s && current < s) return false;
			if (dist[v] > dist[current] + 1) {
				dist[v] = dist[current] + 1;
				if (!done[v]) {
					done[v] = 1;
					q.push(v);
				}
			}
		}
		done[current] = 0;
	}
	return true;
}

vector<int> ans1;
vector<int> ans2;
int main() {
	freopen("race3.in", "r", stdin);
	freopen("race3.out", "w", stdout);
	while (true) {
		int t;
		while (scanf("%d", &t)) {
			if (t < 0) break;
			addEdge(V, t);
		}
		if (t == -1) break;
		V++;
	}

	for (int k = 1; k <= V - 2; k++) {
		if (spfa(k)) {
			ans1.push_back(k);
		}
	}
	int size = ans1.size();
	printf("%d", size);
	for (int i = 0; i < size; i++) {
		int t = ans1[i];
		printf(" %d", t);
		if (spfa2(t)) {
			ans2.push_back(t);
		}
	}
	size = ans2.size();
	printf("\n%d", size);
	for (int i = 0; i < size; i++) {
		printf(" %d", ans2[i]);
	}
	printf("\n");
	return 0;
}
