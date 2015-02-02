#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>

#define MAXV 1000000
#define INF 0x3f3f3f3f

using namespace std;

struct Edge {
	int v;	// 边权
	int to;	// 连接的点
	Edge() {}
	Edge(int a, int b) : v(a), to(b) {}
};

vector<Edge> edges[MAXV];
int V;
int E;
int dist[MAXV];
int vis[MAXV];
int cnt[MAXV];
queue<int> q;

bool spfa(int s) {
	while (!q.empty()) q.pop();
	memset(dist, 0x3f, sizeof(dist));
	memset(vis, 0, sizeof(vis));
	memset(cnt, 0, sizeof(cnt));
	q.push(s);
	dist[s] = 0;
	vis[s] = 1;
	cnt[s] = 1;
	while (!q.empty()) {
		int current = q.front();
		q.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[current] + e.v < dist[e.to]) {
				dist[e.to] = dist[current] + e.v;
				if (!vis[e.to]) {
					vis[e.to] = 1;
					cnt[e.to]++;
					if (cnt[e.to] > V) return false;
				}
			}
		}
		vis[current] = false; // current已经出队
	}
	return true;
}

int main( void ) {
	scanf("%d %d", &V, &E);
	int i, x, y, l;
	for (int i = 0; i < E; i++) {
		scanf("%d%d%d", &x, &y, &l);
		edges[x].push_back(Edge(y, l)); //将这条边压入x的表中
	}
	if(!spfa(0)){ //出现负环
		printf("no answer\n");
	}else{ //存在最短路
		printf("Node 0 to node %d : %d", V-1, dist[V-1]);
	}
	return 0;
}
