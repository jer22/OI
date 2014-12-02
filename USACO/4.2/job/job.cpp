/*
ID:shijiey1
PROG:job
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

struct machine{
	int tim;
	int delay;
	bool operator < (const machine & m) const {
		return delay > m.delay;
	}
};

int n, m1, m2;
int cost[1010];
priority_queue<machine> q1;
priority_queue<machine> q2;
int main() {
	freopen("job.in", "r", stdin);
	freopen("job.out", "w", stdout);
	scanf("%d %d %d", &n, &m1, &m2);
	int t;
	machine mm;
	for (int i = 0; i < m1; i++) {
		scanf("%d", &t);
		mm.tim = mm.delay = t;
		q1.push(mm);
	}
	for (int i = 0; i < m2; i++) {
		scanf("%d", &t);
		mm.tim = mm.delay = t;
		q2.push(mm);
	}
	for (int i = 0; i < n; i++) {
		machine m = q1.top();
		q1.pop();
		cost[i] = m.delay;
		m.delay += m.tim;
		q1.push(m);
	}
	printf("%d ", cost[n - 1]);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		machine m = q2.top();
		q2.pop();
		cost[n - i - 1] += m.delay;
		ans = max(ans, cost[n - i - 1]);
		m.delay += m.tim;
		q2.push(m);
	}
	printf("%d\n", ans);
	return 0;
}
