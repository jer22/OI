#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

struct Martix{
	int dim;
	int arr[12];
};

bool operator < (Martix a, Martix b) {
	for (int i = 0; i < a.dim; i++) {
		if (a.arr[i] >= b.arr[i]) {
			return false;
		}
	}
	return true;
}

int n, m;
Martix mar[35];
vector<int> edges[35];
int path[40];
int maxans = -1;

int dist[40];
int pre[40];
int vis[40];
int big[40][40];
int solve(int i) {
	if (path[i] > 0) return path[i];
	path[i] = 1;
	for (int j = 1; j <= n; j++) {
		if (big[i][j]) {
			path[i] = max(path[i], solve(j) + 1);
		}
	}
	return path[i];
}

void printAns(int i) {
	for (int j = 1; j <= n; j++) {
		if (big[i][j] && path[i] == path[j] + 1) {
			printf(" %d", j);
			printAns(j);
			break;
		}
	}
}

int main() {
	freopen("103.in", "r", stdin);
	freopen("103.out", "w", stdout);
	while (scanf("%d %d", &n, &m) != EOF) {
		maxans = 0;
		memset(path, 0, sizeof(path));
		for (int i = 0; i <= n; i++) {
			edges[i].clear();
		}
		memset(mar, 0, sizeof(mar));
		for (int i = 1; i <= n; i++) {
			mar[i].dim = m;
			for (int j = 0; j < m; j++) {
				scanf("%d", &mar[i].arr[j]);
			}
			sort(mar[i].arr, mar[i].arr + mar[i].dim);
			for (int j = 1; j < i; j++) {
				if (mar[i] < mar[j]) {
					edges[i].push_back(j);
				} else if (mar[j] < mar[i]) {
					edges[j].push_back(i);
				}
			}
		}
		memset(big, 0, sizeof(big));
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (i != j && mar[i] < mar[j]) {
					big[i][j] = 1;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			solve(i);
		}
		int t = 1;
		for (int i = 1; i <= n; i++) {
			if (path[i] > path[t])
				t = i;
		}
		printf("%d\n", path[t]);
		printf("%d", t);
		printAns(t);
		printf("\n");
	}


	return 0;
}
