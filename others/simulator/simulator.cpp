#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

struct liquid {
	int v;
	double c;
};

int v0;
double c0;
int n;
stack<liquid> q;
int main() {
	freopen("simulator.in", "r", stdin);
	freopen("simulator.out", "w", stdout);
	scanf("%d %lf", &v0, &c0);
	scanf("%d\n", &n);
	liquid l;
	l.v = v0;
	l.c = c0;
	q.push(l);
	char query;
	int v;
	double c;
	for (int i = 0; i < n; i++) {
		scanf("%c", &query);
		if (query == 'P') {
			scanf("%d %lf\n", &v, &c);
			int vn = q.top().v + v;
			double mn = q.top().v * q.top().c / 100 + v * c / 100;
			double cn = mn / vn * 100;
			l.v = vn;
			l.c = cn;
			q.push(l);
			printf("%d %0.5lf\n", vn, cn);
		} else {
			getchar();
			if (q.size() != 1) {
				q.pop();
			}
			printf("%d %0.5lf\n", q.top().v, q.top().c);
		}
	}

	return 0;
}
