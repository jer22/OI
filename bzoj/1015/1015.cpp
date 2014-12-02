#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAXE 200010

using namespace std;

int V, E;
int K;
vector<int> e[MAXE << 1];
int edges[MAXE][2];
int stars[MAXE << 1];
int parent[MAXE << 1];
int now[MAXE << 1];
int block[MAXE << 1];
int result[MAXE << 1];
int nowStars = 0;
int num;

int find(int p)
{
	if (parent[p]==p) return p;
	return parent[p]=find(parent[p]);
}

int un(int x,int y)
{
	int tx=find(x);
	int ty=find(y);
	if (tx==ty) return 0;
	parent[tx]=y;
	return 1;
}

int main( void ) {
	freopen("1015.in", "r", stdin);
	scanf("%d %d", &V, &E);
	// 输入通讯通道
	for (int i = 0; i < E; i++) {
		scanf("%d %d", &edges[i][0], &edges[i][1]);
		e[edges[i][0]].push_back(edges[i][1]);
		e[edges[i][1]].push_back(edges[i][0]);
	}
	scanf("%d", &K);
	num = V - K;
	for (int i = 0; i < V; i++) {
		now[i] = 1;
	}
	// 顺序输入打击顺序
	for (int i = 0; i < K; i++) {
		scanf("%d", &stars[i]);
		now[stars[i]] = 0;
	}
	for (int i = 0; i < V; i++) {
		parent[i] = i;
	}
	// 合并打击所有星球后存留的通讯通道
	for (int i = 0; i < E; i++) {
		if (now[edges[i][0]] && now[edges[i][1]]) {
			if (un(edges[i][0], edges[i][1])) {
				num--;
			}
		}
	}
	int r = K;
	result[r--] = num;
	// 将被打击的星球倒序还原，并统计联通块个数
	for (int i = K - 1; i >= 0; i--) {
		num++;
		for (int j = 0; j < e[stars[i]].size(); j++) {
			if (now[e[stars[i]][j]]) {
				if (un(stars[i], e[stars[i]][j])) {
					num--;
				}
			}
		}
		now[stars[i]] = 1;
		result[r--] = num;
	}
	for (int i = 0; i <= K; i++) {
		printf("%d\n", result[i]);
	}
	return 0;
}
