/*
ID:shijiey1
PROG:job
LANG:C++
*/

/*
先进行工序a。因为所有的产品都同时放在输入库中，所以这一步直接贪心，只要有空闲的机器，就从输入库中取出产品放进去。这样工序a完成的时间一定是最短的，如下图
 开始
1 | --------
2 | ------
3 | ----
4 | ---
5 | -

然后进行工序b。这是因为每件产品完成工序a的时间不同，所以不能像上一步一样做。那怎么办呢?
我们可以把工序b想象成用机器拆产品。每件产品从不同的时间开始拆，使它们有相同的结束时间，如下图
          结束
1        - |
2     ---- |
3    ----- |
4   ------ |
5 -------- |

一件产品一定是先进行完工序a，再进行工序b。所以对于产品5，它在工序b中要求的开始时间最早，所以在工序a中分给它了效率最高的机器，其它产品同理。这样总的时间如下图：
 开始          结束
1 | -------- - |
2 | ---------- |
3 | ---- ----- |
4 | --- ------ |
5 | - -------- |
如果按其他顺序分配，结束时间一定比这种方案晚。
所以只要把工序a最早结束的分给效率最低的b机器，第二结束的分给效率第二低的b机器，依次类推贪心即可。
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
