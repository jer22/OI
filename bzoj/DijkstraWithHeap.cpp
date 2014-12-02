#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>
#include <algorithm>

#define MAXV 10000000
#define INF 0x7FFFFFFF

using namespace std;

struct Edge {
	int v;
	int to;
};

inline int parent(int i) {
	return i >> 1;
}

inline int left(int i) {
	return i << 1;
}

inline int right(int i) {
	return (i << 1) + 1;
}

int V, E;
int dist[MAXV];
vector<Edge> e[MAXV];
Edge heap[MAXV];
int map[MAXV];
int size;

void heapify(int i) {
	int min = i;
	if (i <= size >> 1) {
		if (heap[left(i)].v < heap[min].v) {
			min = left(i);
		}
		if (heap[right(i)].v < heap[min].v) {
			min = right(i);
		}
		if (min != i) {
			map[heap[min].to] = i;
			map[heap[i].to] = min;
			Edge temp;
			temp = heap[min];
			heap[min] = heap[i];
			heap[i] = temp;
			heapify(min);
		}
	}
}

void update(int i, int value) {
	heap[i].v = value;
	while (i > 0 && heap[i].v < heap[parent(i)].v) {
		map[heap[i].to] = parent(i);
		map[heap[parent(i)].to] = i;
		Edge temp;
		temp = heap[i];
		heap[i] = heap[parent(i)];
		heap[parent(i)] = temp;
		i = parent(i);
	}
	/*if (i < 1) {
		return;
	}
	if (heap[i].v < heap[parent(i)].v) {
		map[heap[i].to] = parent(i);
		map[heap[parent(i)].to] = i;
		Edge temp;
		temp = heap[i];
		heap[i] = heap[parent(i)];
		heap[parent(i)] = temp;
		update(parent(i));
	}*/
}

void dijkstra(const int st) {
	for (int i = 0; i < V; i++) {
		map[i] = i + 1;
		dist[i] = INF;
	}
	dist[st] = 0;
	for (int i = 1; i <= V; i++) {
		heap[i].to = i - 1;
		heap[i].v = INF;
	}
	heap[1].v = 0;

	for (int i = 0; i < V; i++) {
		Edge current;
		current = heap[1];
		heap[1] = heap[--size];
		map[heap[1].to] = 1;
		heapify(1);

		Edge* t;
		for (int j = 0; j < (int)e[current.to].size(); j++) {
			t = &e[current.to][j];
			if (dist[current.to] + t -> v < dist[t -> to]) {
				dist[t -> to] = dist[current.to] + t -> v;
				update(map[t -> to], dist[current.to] + t -> v);
			}
		}
	}
}

int main( void ) {
	scanf("%d %d", &V, &E);
	size = V;
	int x, y, l;
	for (int i = 0; i < E; i++) {
		scanf("%d %d %d", &x, &y, &l);
		Edge temp;
		temp.v = l;
		temp.to = y;
		e[x].push_back(temp);
	}
	dijkstra(0);
	printf("Node 0 to node %d : %d", V-1, dist[V-1]);
	return 0;
}
