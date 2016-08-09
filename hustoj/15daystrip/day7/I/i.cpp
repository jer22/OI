#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node{
	int arr[5][5];
	int step;
};

int T;
Node start;

bool check(Node s) {
	if (s.arr[0][0] == s.arr[0][1]) {
		if ((s.arr[0][1] != s.arr[0][2]) || (s.arr[0][2] != s.arr[0][3])) return false;
		if ((s.arr[1][0] != s.arr[1][1]) || (s.arr[1][1] != s.arr[1][2]) || (s.arr[1][2] != s.arr[1][3])) return false;
		if ((s.arr[2][0] != s.arr[2][1]) || (s.arr[2][1] != s.arr[2][2]) || (s.arr[2][2] != s.arr[2][3])) return false;
		if ((s.arr[3][0] != s.arr[3][1]) || (s.arr[3][1] != s.arr[3][2]) || (s.arr[3][2] != s.arr[3][3])) return false;
		return true;
	}
	if (s.arr[0][0] != s.arr[1][0])
		return false;
	if ((s.arr[1][0] != s.arr[2][0]) || (s.arr[2][0] != s.arr[3][0])) return false;
	if ((s.arr[0][1] != s.arr[1][1]) || (s.arr[1][1] != s.arr[2][1]) || (s.arr[2][1] != s.arr[3][1])) return false;
	if ((s.arr[0][2] != s.arr[1][2]) || (s.arr[1][2] != s.arr[2][2]) || (s.arr[2][2] != s.arr[3][2])) return false;
	if ((s.arr[0][3] != s.arr[1][3]) || (s.arr[1][3] != s.arr[2][3]) || (s.arr[2][3] != s.arr[3][3])) return false;
	return true;

}

int bfs() {
	if (check(start)) return 0;
	queue<Node> q;
	q.push(start);
	while (!q.empty()) {
		Node cur = q.front();
		q.pop();
		if (cur.step > 5) return -1;
		Node nex = cur;
		nex.step++;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				nex.arr[i][j] = cur.arr[i][(j + 1) % 4];
			if (check(nex)) return nex.step;
			if (nex.step < 5) q.push(nex);

			for (int j = 0; j < 4; j++)
				nex.arr[i][j] = cur.arr[i][(j + 3) % 4];
			if (check(nex)) return nex.step;
			if (nex.step < 5) q.push(nex);
			
			for (int j = 0; j < 4; j++) nex.arr[i][j] = cur.arr[i][j];

			for (int j = 0; j < 4; j++)
				nex.arr[j][i] = cur.arr[(j + 1) % 4][i];
			if (check(nex)) return nex.step;
			if (nex.step < 5) q.push(nex);

			for (int j = 0; j < 4; j++)
				nex.arr[j][i] = cur.arr[(j + 3) % 4][i];
			if (check(nex)) return nex.step;
			if (nex.step < 5) q.push(nex);

			for (int j = 0; j < 4; j++) nex.arr[j][i] = cur.arr[j][i];
		}

	}
	return -1;
}

int main() {
	// freopen("i.in", "r", stdin);
	scanf("%d", &T);

	while (T--) {
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				scanf("%d", &start.arr[i][j]);
		start.step = 0;
		int ans = bfs();
		printf("%d\n", ans);
	}


	return 0;
}
