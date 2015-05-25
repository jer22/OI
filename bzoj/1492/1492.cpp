#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

const double INF = 1e20;
const double eps = 1e-9;

struct Node{
	double x, y, a, b, k, rate;
	int id;
	bool operator < (const Node &n) const {
		return k > n.k;
	}
} p[100005], t[100005];

int n;
double s;
double dp[100005];
int stack[100005];

double getk(int a, int b) {
	if (!b) return -INF;
	if (fabs(p[a].x - p[b].x) < eps) return INF;
	return (p[b].y - p[a].y) / (p[b].x - p[a].x);
}

void solve(int l, int r) {
	if (l == r) {
		dp[l] = max(dp[l], dp[l - 1]);
		p[l].y = dp[l] / (p[l].a * p[l].rate + p[l].b);
		p[l].x = p[l].y * p[l].rate;
		return;
	}
	int mid = l + r >> 1;
	int j = 1;
	int l1 = l, l2 = mid + 1;
	for (int i = l; i <= r; i++)
		if (p[i].id <= mid) t[l1++] = p[i];
		else t[l2++] = p[i];
	for (int i = l; i <= r; i++)
		p[i] = t[i];
	solve(l, mid);
	int top = 0;
	for (int i = l; i <= mid; i++) {
		while (top > 1 && getk(stack[top - 1], stack[top]) < getk(stack[top - 1], i) + eps)
			top--;
		stack[++top] = i;
	}
	stack[++top] = 0;
	for (int i = mid + 1; i <= r; i++) {
		while (top > 1 && getk(stack[j], stack[j + 1]) + eps > p[i].k) j++;
		dp[p[i].id] = max(dp[p[i].id], p[stack[j]].x * p[i].a + p[stack[j]].y * p[i].b);
	}
	solve(mid + 1, r);
	l1 = l, l2 = mid + 1;
	for (int i = l; i <= r; i++) {
		if (((p[l1].x < p[l2].x || (fabs(p[l1].x - p[l2].x) < eps && p[l1].y < p[l2].y)) || l2 > r) && l1 <= mid) t[i] = p[l1++];
		else t[i] = p[l2++];
	}
	for (int i = l; i <= r; i++)
		p[i] = t[i];
}

int main() {
	freopen("1492.in", "r", stdin);
	scanf("%d %lf", &n, &dp[0]);
	for (int i = 1; i <= n; i++) {
		scanf("%lf %lf %lf", &p[i].a, &p[i].b, &p[i].rate);
		p[i].k = -p[i].a / p[i].b;
		p[i].id = i;
	}
	sort(p + 1, p + n + 1);
	solve(1, n);
	printf("%.3lf\n", dp[n]);
	return 0;
}
