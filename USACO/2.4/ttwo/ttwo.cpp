/*
ID:shijiey1
PROG:ttwo
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Point{
	int x, y;
};

int arr[12][12];
Point john;
Point cow;
Point posj;
Point posc;
Point sj;
Point sc;
int main() {
	freopen("ttwo.in", "r", stdin);
	freopen("ttwo.out", "w", stdout);
	char c;
	for (int i = 0; i <= 11; i++) {
		arr[0][i] = arr[i][0] = 1;
		arr[11][i] = arr[i][11] = 1;
	}
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++) {
			scanf("%c", &c);
			if (c == '*') arr[i][j] = 1;
			if (c == 'F') {
				john.x = sj.x = i;
				john.y = sj.y = j;
			}
			if (c == 'C') {
				cow.x = sc.x = i;
				cow.y = sc.y = j;
			}
		}
		getchar();
	}
	posj.x = posc.x = -1;
	posj.y = posc.y = 0;

	if (arr[john.x + 1][john.y] && arr[john.x - 1][john.y] && arr[john.x][john.y + 1] && arr[john.x][john.y - 1]
		|| arr[cow.x + 1][cow.y] && arr[cow.x - 1][cow.y] && arr[cow.x][cow.y + 1] && arr[cow.x][cow.y - 1]) {
		printf("0\n");
		return 0;
	}

	int cnt = 0;
	while (true) {
		// printf("%d %d | %d %d\n", john.x, john.y, cow.x, cow.y);
		if (cnt > 2000000) {
			printf("0\n");
			return 0;
		}
		if (arr[john.x + posj.x][john.y + posj.y] == 1) {
			int t = posj.y;
			if (!posj.x) posj.y = 0;
			else posj.y = posj.y - posj.x;
			posj.x = t;
		} else {
			john.x += posj.x;
			john.y += posj.y;
		}
		
		if (arr[cow.x + posc.x][cow.y + posc.y] == 1) {
			int t = posc.y;
			if (!posc.x) posc.y = 0;
			else posc.y = posc.y - posc.x;
			posc.x = t;
		} else {
			cow.x += posc.x;
			cow.y += posc.y;
		}
		
		if (john.x == cow.x && john.y == cow.y) {
			printf("%d\n", cnt + 1);
			return 0;
		}
		cnt++;
	}


	return 0;
}
