#include <iostream>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <cstring>

#define MAXN 50000 + 10

using namespace std;

struct line {
	int index;
	int a, b;
} lines[MAXN];

bool cmp (const struct line &x, const struct line &y) {
	return (x.a < y.a || (x.a == y.a && x.b > y.b));
}

int n;
stack<line> s;

void push(int x) {
	while (s.size() >= 2) {
		line temp = s.top();
		s.pop();
		double x1, x2;
		double a1, b1, a2, b2, a3, b3;
		a1 = lines[x].a;
		b1 = lines[x].b;
		a2 = temp.a;
		b2 = temp.b;
		a3 = s.top().a;
		b3 = s.top().b;
		x1 = (b2 - b1) / (a1 - a2);
		x2 = (b3 - b2) / (a2 - a3);
		if (x1 > x2) {
			s.push(temp);
			break;
		}
	}
	s.push(lines[x]);
}

int main( void ) {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &lines[i].a, &lines[i].b);
		lines[i].index = i;
	}
	sort(lines + 1, lines + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		if (lines[i].a != lines[i - 1].a) {
			push(i);
		}
	}
	int arr[MAXN];
	memset(arr, 0, sizeof(arr));
	line temp;
	while (!s.empty()) {
		temp = s.top();
		s.pop();
		arr[temp.index] = 1;
	}
	for (int i = 1; i <= n; i++) {
		if (arr[i])
			printf("%d ", i);
	}

	return 0;
}
