#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <set>

using namespace std;

const double INF = 1e20;
const int eps = 1e-8;

struct Node{
	double x, y;
	Node() {}
	Node(int a, int b) : x(a), y(b) {}
};

int n;
Node p[205];
double arr[40005];
int main() {
	freopen("1610.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
	int tot = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (p[i].x != p[j].x) arr[tot++] = (p[i].y - p[j].y) / (p[i].x - p[j].x);
			else arr[tot++] = INF;
		}
	}
	sort(arr, arr + tot);
	int ans = 1;
	for (int i = 1; i < tot; i++)
		if (fabs(arr[i] - arr[i - 1]) > eps) ans++;
	printf("%d\n", ans);
	return 0;
}
