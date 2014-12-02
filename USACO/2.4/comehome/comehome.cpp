/*
ID:shijiey1
PROG:comehome
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

#define INF 0x3f3f3f3f

using namespace std;

struct Edge{
	int v, to;
};

int m, n = 0;
vector<Edge> edges[65];
int dist[65];
int done[65];
queue<int> buff;
void spfa(int s) {
	for (int i = 0; i < n; i++) {
		dist[i] = INF;
	}
	dist[s] = 0;
	done[s] = 1;
	buff.push(s);
	while (!buff.empty()) {
		int current = buff.front();
		buff.pop();
		for (int i = 0; i < edges[current].size(); i++) {
			Edge e = edges[current][i];
			if (dist[e.to] > dist[current] + e.v) {
				dist[e.to] = dist[current] + e.v;
				if (!done[e.to]) {
					buff.push(e.to);
					done[e.to] = 1;
				}
			}
		}
		done[current] = 0;
	}

}

int main() {
	freopen("comehome.in", "r", stdin);
	freopen("comehome.out", "w", stdout);
	scanf("%d\n", &m);
	char a, b;
	int c;
	for (int i = 0; i < m; i++) {
		scanf("%c %c %d\n", &a, &b, &c);
		n = max(n, max(a - 'A', b - 'A'));
		Edge e;
		e.to = b - 'A';
		e.v = c;
		edges[a - 'A'].push_back(e);
		e.to = a - 'A';
		edges[b - 'A'].push_back(e);
	}
	n++;
	spfa('Z' - 'A');
	int idx = -1;
	int minn = INF;
	for (int i = 0; i <= 'Y' - 'A'; i++) {
		if (dist[i] < minn) {
			minn = dist[i];
			idx = i;
		}
	}
	printf("%c %d\n", idx + 'A', dist[idx]);
	return 0;
}
