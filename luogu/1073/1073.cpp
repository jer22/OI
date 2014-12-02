#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>

#define MAXV 100010
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
	int to;
};

int V, E;
int price[MAXV];
vector<Edge> edge[MAXV];
vector<Edge> reverseEdge[MAXV];

int buy[MAXV];
int sell[MAXV];

int done[MAXV];
void spfa_buy() {
	buy[1] = price[1];
	for (int i = 2; i <= V; i++) {
		buy[i] = INF;
	}
	queue<int> buff;
	memset(done, 0, sizeof(done));
	buff.push(1);
	done[1] = 1;
	while (!buff.empty()) {
		int current = buff.front();
		for (int i = 0; i < edge[current].size(); i++) {
			Edge t = edge[current][i];
			if (buy[current] < buy[t.to]) {
				buy[t.to] = min(buy[current], price[t.to]);
				buff.push(t.to);
				done[t.to] = 1;
			}
		}
		buff.pop();
		done[current] = 0;
	}
}

void spfa_sell() {
	sell[V] = price[V];
	for (int i = 1; i < V; i++) {
		sell[i] = -1;
	}
	queue<int> buff;
	memset(done, 0, sizeof(done));
	buff.push(V);
	done[V] = 1;
	while (!buff.empty()) {
		int current = buff.front();
		for (int i = 0; i < reverseEdge[current].size(); i++) {
			Edge t = reverseEdge[current][i];
			if (sell[current] > sell[t.to]) {
				sell[t.to] = max(sell[current], price[t.to]);
				buff.push(t.to);
				done[t.to] = 1;
			}
		}
		buff.pop();
		done[current] = 0;
	}
}

int main() {
	freopen("1073.in", "r", stdin);
	scanf("%d %d", &V, &E);
	for (int i = 1; i <= V; i++) {
		scanf("%d", &price[i]);
	}
	int u, v, t;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &u, &v, &t);
		Edge e1, e2;
		e1.to = v;
		e2.to = u;
		edge[u].push_back(e1);
		reverseEdge[v].push_back(e2);
		if (t == 2) {
			edge[v].push_back(e2);
			reverseEdge[u].push_back(e1);
		}
	}
	spfa_buy();
	spfa_sell();
	// for (int i = 1; i <= V; i++) {
	// 	printf("%d %d\n", buy[i], sell[i]);
	// }
	int re = -1;
	for (int i = 1; i <= V; i++) {
		if (buy[i] != INF && sell[i] != -1) {
			re = max(re, sell[i] - buy[i]);
		}
	}
	printf("%d\n", re);
	return 0;
}
