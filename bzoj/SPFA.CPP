#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <cstdio>

#define MAXV 1000000
#define INF 0x7FFFFFFF

using namespace std;

struct Edge {
	int v;	// 边权
	int to;	// 连接的点
};

vector<Edge> e[MAXV];
int V;
int E;

int main( void ) {
	scanf("%d %d", &V, &E);
	int i, x, y, l;
	for (int i = 0; i < E; i++) {
		scanf("%d%d%d", &x, &y, &l);
		Edge temp;
		temp.v=l; //设置边权
		temp.to=y; //设置连接节点
		e[x].push_back(temp); //将这条边压入x的表中
	}
	if(!spfa(0)){ //出现负环
		printf("no answer\n");
	}else{ //存在最短路
		printf("Node 0 to node %d : %d", V-1, dist[V-1]);
	}
	return 0;
}
