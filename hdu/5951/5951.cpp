#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define pii pair<int, int>
#define mp(i, j) make_pair((i), (j))

using namespace std;

const int MAXN = 265;

struct Node{
	int n, a, b, id;
	Node() {}
	Node(int c, int d, int e, int f) : n(c), a(d), b(e), id(f) {}
	bool operator < (const Node &nn) const {
		if (n != nn.n) return n < nn.n;
		if (a != nn.a) return a < nn.a;
		return b < nn.b;
	}
};

int o[2][MAXN][MAXN];
int ofirhor[2][MAXN][MAXN];
int ofirver[2][MAXN][MAXN];

Node query[MAXN];
int T, now = 1;
pii ans[MAXN];

void solve() {
	// memset(ofirhor, 0x3f, sizeof(ofirhor));
	// memset(ofirver, 0x3f, sizeof(ofirver));
	for (int i = 0; i <= 260; i++) {
		for (int j = 0; j <= 260; j++) {
			o[1][i][j] = int(i >= j);
			// e[1][i][j] = int(i > j);
		}
		ofirhor[1][i][1] = 0;
		ofirhor[1][i][0] = i + 1;
		ofirver[1][i][1] = i;
		ofirver[1][i][0] = 0;

		// efirhor[1][i][1] = 0;
	}
	ofirver[1][0][0] = 0x3f3f3f3f;

	for (int i = 1; i <= 260; i++) {
		// if (i != 1) {
		// 	for (int a = 0; a <= 260; a++) {
		// 		for (int b = 0; b <= 260; b++) {
		// 			ofirhor[i & 1][a][b] = ofirver[i & 1][a][b] = 0x3f3f3f3f;
		// 		}
		// 	}
		// }
		for (int a = 0; a <= 260; a++) {
			for (int b = 0; b <= 260; b++) {
				if (i != 1) {
					int t = o[(i + 1) & 1][a][b];
					o[i & 1][a][b] = t;
					int numa = a - ofirver[(i + 1) & 1][b][t] + 1;
					int numb = b - ofirhor[(i + 1) & 1][a][t] + 1;
					if (i & 1) {
						if (numa >= numb) o[i & 1][a][b]++;
					} else {
						if (numa > numb) o[i & 1][a][b]++;
					}
					// if (ofirhor[i & 1][a][o[i & 1][a][b]] == 0x3f3f3f3f)
					// 	ofirhor[i & 1][a][o[i & 1][a][b]] = b;
					// if (ofirver[i & 1][b][o[i & 1][a][b]] == 0x3f3f3f3f)
					// 	ofirver[i & 1][b][o[i & 1][a][b]] = a;
					if (!b || o[i & 1][a][b] < o[i & 1][a][b - 1])
						ofirhor[i & 1][a][o[i & 1][a][b]] = b;
					if (!a || o[i & 1][a][b] > o[i & 1][a - 1][b])
						ofirver[i & 1][b][o[i & 1][a][b]] = a;
				}
				// cout<< T << endl;
				if ((now <= T) && (i == query[now].n) && (a == query[now].a) && (b == query[now].b)) {
					ans[query[now].id] = mp(o[i & 1][a][b], i - o[i & 1][a][b]);
					now++;
				}
			}
		}
		// if (i > 10) continue;
		// cout << i << endl;
		// cout << "================================" << endl;
		// for (int a = 0; a <= 10; a++) {
		// 	for (int b = 0; b <= 10; b++) {
		// 		cout << o[i & 1][a][b] << ' ';
		// 	}
		// 	cout << endl;
		// }
	}
}

int n, a, b;
int main() {
	freopen("5951.in", "r", stdin);
	scanf("%d", &T);
	for (int i = 1; i <= T; i++) {
		scanf("%d %d %d", &n, &a, &b);
		query[i] = Node(n, a, b, i);
	}
	sort(query + 1, query + T + 1);
	while (!query[now].n) now++;
	solve();
	for (int i = 1; i <= T; i++)
		printf("Alice %d Bob %d\n", ans[i].first, ans[i].second);

	return 0;
}
