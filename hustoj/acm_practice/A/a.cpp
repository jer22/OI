#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct Node{
	double t, p;
	Node() {}
	Node(double a, double b) : t(a), p(b) {}
	bool operator < (const Node &n) const {
		return t < n.t;
	}
};

int T, n;
Node arr[10005];
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &arr[i].t, &arr[i].p);
		sort(arr, arr + n);
		double ans = 0;
		for (int i = 1; i < n; i++) {
			double dist = fabs(arr[i].p - arr[i - 1].p);
			double tt = arr[i].t - arr[i - 1].t;
			ans = max(ans, dist / tt);
		}
		printf("Case #%d: ", cas++);
		printf("%.2lf\n", ans);
	}


	return 0;
}
