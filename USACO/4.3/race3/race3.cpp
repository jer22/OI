/*
ID:shijiey1
PROG:race3
LANG:C++
*/

/*
第一问n-2次spfa，枚举每一个不可避免的路口k，spfa时遇到k时continue，如果从起点无法走到终点则k为不可避免的路口。
第二问，显然中间路口一定是一个不可避免路口，所以先枚举每一个不可避免路口k，以k为起点spfa，如果从比k编号小的节点回到了k，则k一定不是中间路口。否则k一定是中间路口。
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
