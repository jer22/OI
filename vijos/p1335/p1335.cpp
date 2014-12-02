#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
int vertical[15][15];
int horizontal[15][15];
int block[15][15];
int main() {
	freopen("p1335.in", "r", stdin);
	scanf("%d", &n);
	while (n--) {
		int t;
		memset(block, 0, sizeof(block));
		memset(horizontal, 0, sizeof(horizontal));
		memset(vertical, 0, sizeof(vertical));
		bool flag = true;
		for (int i = 1; i <= 9; i++) {
			for (int j = 1; j <= 9; j++) {
				scanf("%d", &t);
				if (!flag) continue;
				vertical[i][t]++;
				horizontal[j][t]++;
				block[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][t]++;
				if (vertical[i][t] > 1 || horizontal[j][t] > 1 || block[(i - 1) / 3 * 3 + (j - 1) / 3 + 1][t] > 1) {
					flag = false;
				}
			}
		}
		if (flag) printf("Right\n");
		else printf("Wrong\n");
	}

	return 0;
}
