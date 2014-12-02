#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 1000010

using namespace std;

int n, m;
int room[MAXN];
int order[MAXN][3];
int usedRoom[MAXN];
int getResult(int c) {
	int ans = 0;
	memset(usedRoom, 0, sizeof(usedRoom));
	for (int i = 0; i < c; i++) {
		usedRoom[order[i][1]] += order[i][0];
		usedRoom[order[i][2] + 1] -= order[i][0];
	}
	int total = 0;
	for (int i = 1; i <= n; i++) {
		total += usedRoom[i];
		if (total > room[i]) {
			ans = i;
			break;
		}
	}
	return ans;
}

int main() {
	freopen("1083.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &room[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &order[i][0], &order[i][1], &order[i][2]);
	}
	int a = 1;
	int b = m;
	bool flag = false;
	while (a < b) {
		int c = (a + b) >> 1;
		if (getResult(c)) {
			flag = true;
			b = c;
		} else {
			a = c + 1;
		}
	}

	if (!flag) {
		printf("0\n");
	} else {
		printf("-1\n%d\n", a);
	}
	return 0;
}
