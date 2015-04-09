#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

const int INF = 0x3f3f3f3f;
const int MAXV = 10000;

/**
	储存弧的结构
	代表从from到to，容量为cap， 流量为flow
*/
struct Edge{
	int from, to;
	long long cap, flow;
};

int V, E, S, T;
vector<Edge> edges; // 边 edges[e]和edges[e ^ 1]互为反向弧
vector<int> G[MAXV]; // 邻接表 G[i][j]表示节点i的第j条边在edges中的序号
int layer[MAXV];	// 节点i的层
int cur[MAXV];		// 当前弧下标

/**
	插入弧
	将插入两条弧，一条是它本身，一条是它的反向弧
	edges[i]与edges[i ^ 1]互为反向弧
*/
void addEdge(int from, int to, long long cap) {
	edges.push_back((Edge){from, to, cap, 0});
	edges.push_back((Edge){to, from, 0, 0});
	E = edges.size();
	G[from].push_back(E - 2);
	G[to].push_back(E - 1);
}

/**
	建立层次图
	@return：是否存在s-t路径
*/
bool build() {
	memset(layer, -1, sizeof(layer));
	queue<int> q;
	q.push(S);
	layer[S] = 0;
	while(!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < G[x].size(); i++) {
			Edge& e = edges[G[x][i]];
			if (layer[e.to] == -1 && e.cap > e.flow) { // 只考虑残量网络中的弧
				layer[e.to] = layer[x] + 1;
				q.push(e.to);
			}
		}
	}
	return layer[T] != -1;
}

/**
	寻找增广路
	@param x：当前节点
	@param a：目前为止所有弧的最小残量
	@return：流量
*/
long long find(int x, long long a) {
	if (x == T || a == 0) return a;
	long long flow = 0, f;
	for (int& i = cur[x]; i < G[x].size(); i++) {
		Edge& e = edges[G[x][i]];
		if (layer[x] + 1 == layer[e.to]
			&& (f = find(e.to, min(a, e.cap - e.flow))) != 0) {
			e.flow += f;
			edges[G[x][i] ^ 1].flow -= f;
			flow += f;
			a -= f;
			if (!a) break;
		}
	}
	return flow;
}

long long dinic(int s, int t) {
	S = s, T = t;
	long long flow = 0;
	while(build()) {
		memset(cur, 0, sizeof(cur));
		flow += find(s, INF);
	}
	return flow;
}

long long gcd(long long a, long long b) {
	while (b ^= a ^= b ^= a %= b);
	return a;
}
long long arr[3005];
bool vis1[3005], vis2[3005];
int main( void ) {
	freopen("3275.in", "r", stdin);
	scanf("%d", &V);
	long long tot = 0;
	for (int i = 1; i <= V; i++) {
		scanf("%lld", &arr[i]);
		if (arr[i] & 1) addEdge(i, V + 1, arr[i]);
		else addEdge(0, i, arr[i]);
		tot += arr[i];
	}
	for (int i = 1; i <= V; i++) {
		if (arr[i] & 1) continue;
		for (int j = 1; j <= V; j++) {
			if (gcd(arr[i], arr[j]) == 1) {
				long long t = arr[i] * arr[i] + arr[j] * arr[j];
				long long k = sqrt(t);
				if (k * k != t) continue;
				addEdge(i, j, INF);

			}
		}
	}
	long long ans = dinic(0, V + 1);

	printf("%lld\n", tot - ans);
	return 0;
}
