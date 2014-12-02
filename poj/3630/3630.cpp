#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_NODE 2000
#define SIGMA_SIZE 10

using namespace std;

struct Trie{
	int ch[MAX_NODE][SIGMA_SIZE];
	int end[MAX_NODE];
	// int cnt[MAX_NODE];
	int size;
	Trie() {
		size = 1;
		memset(ch, 0, sizeof(ch));
		memset(end, 0, sizeof(end));
		// memset(cnt, 0, sizeof(cnt));
	}

	int idx(char c) {
		return c - '0';
	}

	void insert(char *s) {
		int cur = 0;
		int lens = strlen(s);
		for (int i = 0; i < lens; i++) {
			int c = idx(s[i]);
			if (!ch[cur][c]) {
				//memset(ch[size], 0, sizeof(ch[size]));
				end[size] = 0;
				ch[cur][c] = size++;
			}
			cur = ch[cur][c];
			// cnt[cur]++;
		}
		end[cur]++;
	}
};

int n;
Trie t;
// void dfs(int i) {
// 	if (t.end[i] && t.cnt[i] > 1) {
// 		flag = true;
// 		return;
// 	}
// 	for (int j = 0; j <= 9; j++) {
// 		if (t.ch[i][j]) {
// 			dfs(t.ch[i][j]);
// 			if (flag) return;
// 		}
// 	}
// }

int main() {
	freopen("3630.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		t = Trie();
		char s[12];
		bool flag = false;
		for (int i = 0; i < n; i++) {
			scanf("%s", &s);
			t.insert(s);
		}
		for (int i = 0; i < t.size; i++) {
			if (t.end[i]) {
				if (t.end[i] > 1) {
					flag = true;
					break;
				}
				for (int j = 0; j <= 9; j++) {
					if (t.ch[i][j]) {
						flag = true;
						break;
					}
				}
				if (flag) break;
			}
		}

		if (flag) printf("NO\n");
		else printf("YES\n");
	}
	return 0;
}
