#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct Point{
	int x, y;
};

int n;
Point ori[5][5];
Point home[5];

long long dist(Point p1, Point p2) {
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

bool check(int i, int j, int k, int l) {
	Point p1 = ori[1][i];
	Point p2 = ori[2][j];
	Point p3 = ori[3][k];
	Point p4 = ori[4][l];
	if (dist(p1, p2) && dist(p1, p3) && dist(p1, p4) && dist(p2, p3) && dist(p2, p4) && dist(p3, p4)) {
		if (dist(p1, p2) == dist(p3, p4) && dist(p1, p4) == dist(p2, p3) && dist(p1, p3) == dist(p2, p4) && dist(p1, p2) == dist(p2, p3))
			return true;
		if (dist(p1, p3) == dist(p2, p4) && dist(p1, p4) == dist(p2, p3) && dist(p1, p2) == dist(p3, p4) && dist(p1, p3) == dist(p3, p2))
			return true;
		if (dist(p1, p2) == dist(p3, p4) && dist(p1, p3) == dist(p2, p4) && dist(p1, p4) == dist(p2, p3) && dist(p1, p2) == dist(p2, p4))
			return true;
	}
	return false;

}

int main() {
	// freopen("c.in", "r", stdin);
	scanf("%d", &n);
	while (n--) {
		for (int i = 1; i <= 4; i++)
			scanf("%d %d %d %d", &ori[i][0].x, &ori[i][0].y, &home[i].x, &home[i].y);
		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 3; j++) {
				ori[i][j].x = home[i].x + home[i].y - ori[i][j - 1].y;
				ori[i][j].y = home[i].y - home[i].x + ori[i][j - 1].x;
			}
		}
		int ans = 0x3f3f3f3f;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {
						if (i + j + k + l > ans) break;
						if (check(i, j, k, l))
							ans = min(ans, i + j + k + l);
					}
				}
			}
		}
		if (ans == 0x3f3f3f3f) cout << -1 << endl;
		else cout << ans << endl;
	}


	return 0;
}
