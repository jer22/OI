#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define INF 0x3f3f3f3f

using namespace std;

struct Point{
	int a, b;
	Point() {}
	Point(int x, int y) : a(x), b(y) {}
	bool operator == (const Point &p) const {
		return a == p.a && b == p.b;
	}
};

int T, n, d;
int A[75][75], B[75][75];
int edges[75][75];
int L[75], R[75];
int visl[75], visr[75];
int mat[75];

bool dfs(int i) {
	visl[i] = 1;
	for (int j = 1; j <= n; j++) {
		if (!visr[j]) {
			int t = edges[i][j] - L[i] - R[j];
			if (!t) {
				visr[j] = 1;
				if (!mat[j] || dfs(mat[j])) {
					mat[j] = i;
					return true;
				}
			} else d = min(d, t);
		}
	}
	return false;
}

Point KM() {
	memset(R, 0, sizeof(R));
	memset(L, 0x3f, sizeof(L));
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			L[i] = min(L[i], edges[i][j]);
	memset(mat, 0, sizeof(mat));
	for (int i = 1; i <= n; i++) {
		while (true) {
			memset(visl, 0, sizeof(visl));
			memset(visr, 0, sizeof(visr));
			d = INF;
			if (dfs(i)) break;
			for (int j = 1; j <= n; j++)
				if (visl[j]) L[j] += d;
			for (int j = 1; j <= n; j++)
				if (visr[j]) R[j] -= d;
		}
	}
	int t1 = 0, t2 = 0;
	for (int i = 1; i <= n; i++) {
		if (mat[i]) t1 += A[mat[i]][i], t2 += B[mat[i]][i];
	}
	return Point(t1, t2);
}

int dfs(Point a, Point b) {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			edges[i][j] = (a.b - b.b) * A[i][j] + (b.a - a.a) * B[i][j];
	Point m = KM();
	if (m == a || m == b) return min(a.a * a.b, b.a * b.b);
	return min(dfs(a, m), dfs(m, b));
}

int main() {
	freopen("3571.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &A[i][j]), edges[i][j] = A[i][j];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				scanf("%d", &B[i][j]);
		Point t1 = KM();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				edges[i][j] = B[i][j];
		Point t2 = KM();
		printf("%d\n", dfs(t1, t2));
	}
	return 0;
}
