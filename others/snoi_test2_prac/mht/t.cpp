#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <set>

#define INF 0x7fffffff

using namespace std;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
	bool operator < (const Point &p) const {
		return x < p.x;
	}
};

int d, n, m;
set<int> p;
int main() {
	freopen("t.in", "r", stdin);
	int data;
	scanf("%d", &data);
	cin >> d >> n >> m;
	int x, y, z;
	long long cnt = 0;
	for (int k = 0; k < n; k++) {
		cin >> x >> y;
		int a = x - y;
		int b = x + y;
		a = max(a, -m);
		b = min(b, m);
		for (int i = a; i <= b; i++)
			p.insert(i);
	}
	cout << p.size();
	return 0;
}
