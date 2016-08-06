#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

#define pii pair<int, int>

using namespace std;

struct Edge{
	int x, y, c;
	double rank;
	Edge() {}
	Edge(int a, int b, int d) : x(a), y(b), c(d) {}
	bool operator < (const Edge & e) const {
		return rank < e.rank;
	}
};


struct Node{
	int siz;
	
	
};

Edge edges[505 * 505];
int n, m;
int g[505][505];


long long countmincut(Node s) {
	long long ans = 0;
	for (int i = 0; i < m; i++) {
		if (s.find(edges[i].x) != s.find(edges[i].y))
			ans += edges[i].c;
	}
	return ans;
}

Node contract(Node s, int t) {
	Node ans = Node();
	// for (int i = 1; i <= n; i++)
	// 	ans.pa[i] = s.pa[i];
	// int siz = s.siz;
	// while (siz > t) {
	// 	int c;
	// 	do {
	// 		c = rand() % tot;
	// 	} while (ans.find(edges[c].x) == ans.find(edges[c].y));
	// 	ans.un(edges[c].x, edges[c].y);

	// 	siz--;
	// }
	// ans.siz = t;
	return ans;
}

long long mincut(Node s) {
	// long long ans = 0;
	// if (s.siz <= 2) return countmincut(s);
	// int t = ceil((double)s.siz / sqrt(2) + 1);
	// if (s.siz <= 6) t = s.siz - 1;
	// Node g1 = contract(s, t);
	// Node g2 = contract(s, t);
	// return min(mincut(g1), mincut(g2));
}

long long solve() {
	for (int i = 0; i < m; i++) {
		edges[i].rank = (double)rand() / RAND_MAX;
	}
	sort(edges, edges + m);
	Node s = Node(n);
	int k = 0;
	while (s.siz > 2) {
		while (s.find(edges[k].x) == s.find(edges[k].y)) k++;
		s.siz--;
		s.un(edges[k].x, edges[k].y);
	}
	return countmincut(s);
}

int main() {
	freopen("e.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		srand(5521687);
		int a, b, c;
		int tot = 0;
		memset(g, 0, sizeof(g));
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			g[a + 1][b + 1] += c;
			g[b + 1][a + 1] += c;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				if (g[i][j]) edges[tot++] = Edge(i, j, g[i][j]);
			}
		}
		m = tot;

		long long ans = 100000000000000000;
		// long long ans = ;
		for (int i = 0; i < 100; i++) {
			ans = min(ans, solve());
			// Node s = Node(n);
			// ans = min(ans, mincut(s));
		}
		// cout << ans << endl;
		// for (int i = 0; i < 100; i++) {
		// 	for (int j = 1; j <= n; j++)
		// 		fa[j] = j;
		// 	for (int j = 0; j < n - 2; j++)
		// 		solve();
		// 	ans = min(ans, getans());
		// }
		cout << ans << endl;
	}


	return 0;
}
