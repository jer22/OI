#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Node {
	char cube[6][3][3];
	int step;
	int dir[6];
	int side[6];
	Node() {
		memset(side, 0, sizeof(side));
		memset(dir, 0, sizeof(dir));
		memset(cube, 0, sizeof(cube));
		step = 0;
	}
};

int T;
bool check(char cube[6][3][3]) {
	char c;
	for (int k = 0; k < 6; k++) {
		c = cube[k][0][0];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (cube[k][i][j] != c) return false;
	}
	return true;
}

Node rotate(Node ori, int side, int dir) {
	Node nex = ori;
	nex.side[nex.step] = side;
	nex.dir[nex.step++] = dir;
	
	if (dir == 1) {
		nex.cube[side][0][0] = ori.cube[side][2][0];
		nex.cube[side][2][0] = ori.cube[side][2][2];
		nex.cube[side][2][2] = ori.cube[side][0][2];
		nex.cube[side][0][2] = ori.cube[side][0][0];

		nex.cube[side][0][1] = ori.cube[side][1][0];
		nex.cube[side][1][0] = ori.cube[side][2][1];
		nex.cube[side][2][1] = ori.cube[side][1][2];
		nex.cube[side][1][2] = ori.cube[side][0][1];
		if (side == 0) {
			for (int i = 0; i < 3; i++) {
				nex.cube[1][i][0] = ori.cube[4][i][0];
				nex.cube[5][i][0] = ori.cube[1][i][0];
				nex.cube[4][i][0] = ori.cube[3][3 - i - 1][2];
				nex.cube[3][i][2] = ori.cube[5][3 - i - 1][0];
			}
		} else if (side == 1) {
			for (int i = 0; i < 3; i++) {
				nex.cube[4][2][i] = ori.cube[0][3 - i - 1][2];
				nex.cube[0][i][2] = ori.cube[5][0][i];
				nex.cube[5][0][i] = ori.cube[2][3 - i - 1][0];
				nex.cube[2][i][0] = ori.cube[4][2][i];
			}
		} else if (side == 2) {
			for (int i = 0; i < 3; i++) {
				nex.cube[4][i][2] = ori.cube[1][i][2];
				nex.cube[1][i][2] = ori.cube[5][i][2];
				nex.cube[5][i][2] = ori.cube[3][3 - i - 1][0];
				nex.cube[3][i][0] = ori.cube[4][3 - i - 1][2];
			}
		} else if (side == 3) {
			for (int i = 0; i < 3; i++) {
				nex.cube[4][0][i] = ori.cube[2][i][2];
				nex.cube[2][i][2] = ori.cube[5][2][3 - i - 1];
				nex.cube[5][2][i] = ori.cube[0][i][0];
				nex.cube[0][i][0] = ori.cube[4][0][3 - i - 1];
			}
		} else if (side == 4) {
			for (int i = 0; i < 3; i++) {
				nex.cube[0][0][i] = ori.cube[1][0][i];
				nex.cube[1][0][i] = ori.cube[2][0][i];
				nex.cube[2][0][i] = ori.cube[3][0][i];
				nex.cube[3][0][i] = ori.cube[0][0][i];
			}
		} else if (side == 5) {
			for (int i = 0; i < 3; i++) {
				nex.cube[3][2][i] = ori.cube[2][2][i];
				nex.cube[2][2][i] = ori.cube[1][2][i];
				nex.cube[1][2][i] = ori.cube[0][2][i];
				nex.cube[0][2][i] = ori.cube[3][2][i];
			}
		}
	} else {
		nex.cube[side][2][0] = ori.cube[side][0][0];
		nex.cube[side][2][2] = ori.cube[side][2][0];
		nex.cube[side][0][2] = ori.cube[side][2][2];
		nex.cube[side][0][0] = ori.cube[side][0][2];

		nex.cube[side][1][0] = ori.cube[side][0][1];
		nex.cube[side][2][1] = ori.cube[side][1][0];
		nex.cube[side][1][2] = ori.cube[side][2][1];
		nex.cube[side][0][1] = ori.cube[side][1][2];
		if (side == 0) {
			for (int i = 0; i < 3; i++) {
				nex.cube[4][i][0] = ori.cube[1][i][0];
				nex.cube[1][i][0] = ori.cube[5][i][0];
				nex.cube[3][3 - i - 1][2] = ori.cube[4][i][0];
				nex.cube[5][3 - i - 1][0] = ori.cube[3][i][2];
			}
		} else if (side == 1) {
			for (int i = 0; i < 3; i++) {
				nex.cube[0][3 - i - 1][2] = ori.cube[4][2][i];
				nex.cube[5][0][i] = ori.cube[0][i][2];
				nex.cube[2][3 - i - 1][0] = ori.cube[5][0][i];
				nex.cube[4][2][i] = ori.cube[2][i][0];
			}
		} else if (side == 2) {
			for (int i = 0; i < 3; i++) {
				nex.cube[1][i][2] = ori.cube[4][i][2];
				nex.cube[5][i][2] = ori.cube[1][i][2];
				nex.cube[3][3 - i - 1][0] = ori.cube[5][i][2];
				nex.cube[4][3 - i - 1][2] = ori.cube[3][i][0];
			}
		} else if (side == 3) {
			for (int i = 0; i < 3; i++) {
				nex.cube[2][i][2] = ori.cube[4][0][i];
				nex.cube[5][2][3 - i - 1] = ori.cube[2][i][2];
				nex.cube[0][i][0] = ori.cube[5][2][i];
				nex.cube[4][0][3 - i - 1] = ori.cube[0][i][0];
			}
		} else if (side == 4) {
			for (int i = 0; i < 3; i++) {
				nex.cube[1][0][i] = ori.cube[0][0][i];
				nex.cube[2][0][i] = ori.cube[1][0][i];
				nex.cube[3][0][i] = ori.cube[2][0][i];
				nex.cube[0][0][i] = ori.cube[3][0][i];
			}
		} else if (side == 5) {
			for (int i = 0; i < 3; i++) {
				nex.cube[2][2][i] = ori.cube[3][2][i];
				nex.cube[1][2][i] = ori.cube[2][2][i];
				nex.cube[0][2][i] = ori.cube[1][2][i];
				nex.cube[3][2][i] = ori.cube[0][2][i];
			}
		}
	}
	return nex;
}

Node ans;
int bfs(Node st) {
	queue<Node> q;
	q.push(st);
	Node nex;
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		for (int i = 0; i < 6; i++) {
			nex = rotate(cur, i, 1);
			if (check(nex.cube)) {
				ans = nex;
				return nex.step;
			} else if (nex.step < 5) q.push(nex);
			nex = rotate(cur, i, -1);
			if (check(nex.cube)) {
				ans = nex;
				return nex.step;
			} else if (nex.step < 5) q.push(nex);
		}
	}
	return -1;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		Node start = Node();
		ans = Node();
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cin >> start.cube[4][i][j];
		for (int i = 0; i < 3; i++)
			for (int k = 0; k < 4; k++)
				for (int j = 0; j < 3; j++)
					cin >> start.cube[k][i][j];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				cin >> start.cube[5][i][j];
		if (check(start.cube)) {
			printf("0\n");
			continue;
		}
		int cnt = bfs(start);
		cout << cnt << endl;
		for (int i = 0; i < ans.step; i++)
			cout << ans.side[i] << ' ' << ans.dir[i] << endl;
	}
	return 0;
}
