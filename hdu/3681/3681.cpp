#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

#define INF 0x3f3f3f3f

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

struct Node{
	int v, step;
	Node(int a, int b) : v(a), step(b) {}
};

int V;		// 所有的G和Y的总数
int swit;	// 所有开关的，压缩到一个int里
int n, m;
char arr[22][22];
Point points[22];	//第i个节点的坐标
int id[22][22];		// 坐标为(i,j)的节点的编号
vector<int> edges[333];

void addEdge(int from, int to) {
	edges[from].push_back(to);
}

// 根据离散化后的坐标返回节点的编号
int getID(int v) {
	return id[v / m][v % m];
}

int dist[22][22];
void spfa(int s) {
	int sid = getID(s);
	for (int i = 0; i <= V; i++)
			dist[sid][i] = INF;
	dist[sid][sid] = 0;
	Node now = Node(s, 0);
	int done[333];
	memset(done, 0, sizeof(done));
	done[s] = 1;
	queue<Node> q;
	q.push(now);
	while (!q.empty()) {
		Node current = q.front();
		q.pop();
		int cid = getID(current.v);
		if (cid != -1) dist[sid][cid] = current.step;
		for (int i = 0; i < edges[current.v].size(); i++) {
			int v = edges[current.v][i];
			if (!done[v]) {
				done[v] = 1;
				q.push(Node(v, current.step + 1));
			}
		}
	}
}

void createGraph() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (arr[i][j] == 'D') continue;
			if (arr[i][j] == 'F') {
				points[0] = Point(i, j);
				id[i][j] = 0;
			}
			if (arr[i][j] == 'G') {
				points[V] = Point(i, j);
				id[i][j] = V++;
			}
			if (arr[i][j] == 'Y') {
				points[V] = Point(i, j);
				id[i][j] = V;
				swit |= (1 << V++);
			}
			// 离散化坐标，每个点与四周能连的连边
			if (i > 0 && arr[i - 1][j] != 'D')
				addEdge(i * m + j, (i - 1) * m + j);
			if (i < n - 1 && arr[i + 1][j] != 'D')
				addEdge(i * m + j, (i + 1) * m + j);
			if (j > 0 && arr[i][j - 1] != 'D')
				addEdge(i * m + j, i * m + j - 1);
			if (j < m - 1 && arr[i][j + 1] != 'D')
				addEdge(i * m + j, i * m + j + 1);
		}
	}
}

int vis[22];
int mid;  // 二分的初始电量
bool dfs(int v, int energy, int stat) {
	if ((stat & swit) == swit) return true;		// 遍历了所有的开关
	for (int i = 0; i < V; i++) {
		if (vis[i] || dist[v][i] == -1 || energy < dist[v][i]) continue;
		vis[i] = 1;
		if (arr[points[i].x][points[i].y] == 'G') {
			// 有充电器的话下一次的电量就是初始电量
			if (dfs(i, mid, stat | (1 << i))) return true;
		} else {
			// 否则消耗一定的电
			if (dfs(i, energy - dist[v][i], stat | (1 << i))) return true;
		}
		vis[i] = 0;
	}
	return false;
}

int getAns() {
	int l = 0, r = 222222;
	int ans;
	// 二分答案
	while (l <= r) {
		mid = l + r >> 1;
		memset(vis, 0, sizeof(vis));
		vis[0] = 1;
		if (dfs(0, mid, 1)) {
			ans = mid;
			r = mid - 1;
		} else l = mid + 1;
	}
	return ans;
}

int main() {
	while (~scanf("%d %d", &n, &m) && n && m) {
		memset(arr, 0, sizeof(arr));
		memset(points, 0, sizeof(points));
		memset(id, -1, sizeof(id));
		for (int i = 0; i <= n * m; i++) edges[i].clear();
		V = 1;
		swit = 0;
		for (int i = 0; i < n; i++)
			scanf("%s", arr[i]);
		createGraph();
		// 球两两之间最短路
		for (int i = 0; i < V; i++) {
			spfa(points[i].x * m + points[i].y);
		}
		bool flag = false;
		for (int i = 1; i < V; i++) {
			// 如果有Y无法到达就输出-1
			if (arr[points[i].x][points[i].y] == 'Y' && dist[0][i] == INF) {
				printf("-1\n");
				flag = true;
				break;
			}
		}
		if (flag) continue;
		int ans = getAns();
		cout << ans << endl;
	}
	return 0;
}



