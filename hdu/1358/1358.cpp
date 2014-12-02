#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int len;
char p[1000111];
int next[1000111];
void getNext() {
	memset(next, 0, sizeof(next));
	int i = 0, j = -1;  
	next[0] = -1;  
	while(i < len) {  
		if (p[i] == p[j] || j == -1) {
			next[++i] = ++j;
		} else {
			j = next[j];
		}
	}
}

void solve() {
	for (int i = 2; i <= len; i++) {
		int t = i - next[i];
		if (i % t == 0 && i / t > 1) printf("%d %d\n", i, i / t);
	}
}

int main() {
	freopen("1358.in", "r", stdin);
	int T = 1;
	while (scanf("%d", &len) && len) {
		scanf("%s", &p);
		printf("Test case #%d\n", T++);
		getNext();
		solve();
		printf("\n");
	}

	return 0;
}
