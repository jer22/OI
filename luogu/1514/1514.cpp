#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAXN 510
#define INF 0x3f3f3f3f

using namespace std;

struct Block {
	int start;
	int end;
	bool operator < (const Block & b) const {
		if (b.start == start) {
			return end > b.end;
		}
		return start < b.start;
	}
} blocks[MAXN][MAXN];

int n, m;
int arr[MAXN][MAXN];
int done[MAXN][MAXN];

void water(int x, int y) {
	if (done[x][y]) {
		return;
	}
	done[x][y] = 1;
	if (x < n && arr[x + 1][y] < arr[x][y]) {
		water(x + 1, y);
	}
	if (x > 1 && arr[x - 1][y] < arr[x][y]) {
		water(x - 1, y);
	}
	if (y < m && arr[x][y + 1] < arr[x][y]) {
		water(x, y + 1);
	}
	if (y > 1 && arr[x][y - 1] < arr[x][y]) {
		water(x, y - 1);
	}
}

Block getBlock(int x, int y) {
	if (done[x][y]) {
		return blocks[x][y];
	}
	done[x][y] = 1;
	Block b;
	int start = MAXN;
	int end = -1;
	if (x == n) {
		start = y;
		end = y;
	}

	if (arr[x + 1][y] >= arr[x][y]
		&&arr[x - 1][y] >= arr[x][y]
		&& arr[x][y + 1] >= arr[x][y]
		&& arr[x][y - 1] >= arr[x][y]) {
		if (x == n) {
			b.start = y;
			b.end = y;
		} else {
			b.start = MAXN;
			b.end = -1;
		}
		blocks[x][y] = b;

		return b;
	}

	if (x < n && arr[x + 1][y] < arr[x][y]) {
		b = getBlock(x + 1, y);
		start = min(start, b.start);
		end = max(end, b.end);
	}
	if (x > 1 && arr[x - 1][y] < arr[x][y]) {
		b = getBlock(x - 1, y);
		start = min(start, b.start);
		end = max(end, b.end);
	}
	if (y < m && arr[x][y + 1] < arr[x][y]) {
		b = getBlock(x, y + 1);
		start = min(start, b.start);
		end = max(end, b.end);
	}
	if (y > 1 && arr[x][y - 1] < arr[x][y]) {
		b = getBlock(x, y - 1);
		start = min(start, b.start);
		end = max(end, b.end);
	}

	b.start = start;
	b.end = end;
	blocks[x][y] = b;
	return b;
}

int main( void ) {
	freopen("1514.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 0; i <= m; i++) {
		arr[0][i] = INF;
		arr[n + 1][i] = INF;
	}
	for (int i = 0; i <= n; i++) {
		arr[i][0] = INF;
		arr[i][m + 1] = INF;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	for (int i = 1; i <= m; i++) {
		water(1, i);
	}
	int cnt = 0;
	bool flag = false;
	for (int i = 1; i <= m; i++) {
		if (!done[n][i]) {
			flag = true;
			cnt++;
		}
	}
	if (flag) {
		printf("0\n%d\n", cnt);
		return 0;
	}
	memset(done, 0, sizeof(done));
	for (int i = 1; i <= m; i++) {
		blocks[1][i] = getBlock(1, i);
		// printf("%d %d\n", blocks[1][i].start, blocks[1][i].end);
	}
	/*Block b = getBlock(1, 4);
	printf("------------\n%d %d\n", b.start, b.end);*/
	sort(blocks[1] + 1, blocks[1] + m + 1);
	Block block[MAXN];
	int l = 0;
	for (int i = 1; i <= m; i++) {
		if (blocks[1][i].start == MAXN) {
			continue;
		}
		block[l++] = blocks[1][i];
	}

	cnt = 1;
	int idx = 0;
	int s = block[0].end;
	int maxnum = 0;
	// for (int i = 0; i < l; i++) {
	// 	printf("%d %d\n", block[i].start, block[i].end);
	// }
	while (s < m) {
        // printf("%d %d\n", s, idx);
		while (block[idx + 1].start <= s + 1 && idx + 1 < l) {
			maxnum = max(maxnum, block[++idx].end);
		}
		cnt++;
		s = maxnum;
	}
	printf("1\n%d\n", cnt);
	return 0;
}
