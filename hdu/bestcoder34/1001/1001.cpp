#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <climits>
#include <vector>
#include <map>

#define INF 0x3f3f3f3f

using namespace std;

struct Node{
	int a, b;

};

int n, m;
Node arr[105];
int dp[205];

int main() {
	freopen("1001.in", "r", stdin);
	while (~scanf("%d %d", &n, &m)) {
		for (int i = 1; i <= m; i++)
			scanf("%d %d", &arr[i].a, &arr[i].b);
		int cost = INF;
		int idx;
		for (int i = 1; i <= m; i++) {
			int t = (n / arr[i].a) * arr[i].b;
			if ((n % arr[i].a)) t += arr[i].b;
			if (t < cost) {
				cost = t;

			}
		}
		cout << cost << endl;
	}

	

	return 0;
}
