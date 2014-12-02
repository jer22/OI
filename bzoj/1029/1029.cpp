#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

#define MAXN 150010

using namespace std;

struct interval {
	int t1, t2;
	bool operator < (const interval &t) const {
		return t2 < t.t2;
	}
}intervals[MAXN];

priority_queue<int> q;

int n;
int end = 0;
int re = 0;
int main( void ) {
	freopen("1029.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &intervals[i].t1, &intervals[i].t2);
	}
	sort(intervals, intervals + n);
	for (int i = 0; i < n; i++) {
		if (end + intervals[i].t1 <= intervals[i].t2) {
			end += intervals[i].t1;
			q.push(intervals[i].t1);
			re++;
		} else {
			if (q.top() > intervals[i].t1) {
				end = end - q.top() + intervals[i].t1;
				q.pop();
				q.push(intervals[i].t1);
			}
		}
	}
	
	printf("%d\n", re);
	return 0;
}
