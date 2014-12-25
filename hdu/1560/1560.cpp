#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n;
char str[11][7];
char dna[4] = {'A', 'C', 'G', 'T'};
int depth;
int pos[11];
bool done() {
	for (int i = 0; i < n; i++)
		if (pos[i]) return false;
	return true;
}

int H() {
	int res = 0;
	for (int i = 0; i < n; i++)
		res = max(res, pos[i]);
	return res;
}

bool dfs(int step) {
	if (step == depth) return done();
	if (step + H() > depth) return false;
	int tmp[11];
	for (int i = 0; i < 4; i++) {
		bool flag = false;
		memcpy(tmp, pos, sizeof(tmp));
		for (int j = 0; j < n; j++) {
			if (!pos[j]) continue;
			if (str[j][pos[j] - 1] == dna[i]) {
				pos[j]--;
				flag = true;
			}
		}
		if (flag && dfs(step + 1)) return true;
		memcpy(pos, tmp, sizeof(pos));
	}
	return false;
}

int main() {
	scanf("%d", &T);
	while (T--) {
		memset(pos, 0, sizeof(pos));
		scanf("%d", &n);
		depth = 0;
		for (int i = 0; i < n; i++) {
			scanf("%s", str[i]);
			pos[i] = strlen(str[i]);
			depth = max(depth, pos[i]);
		}
		while (!dfs(0)) depth++;
		cout << depth << endl;
	}
	return 0;
}
