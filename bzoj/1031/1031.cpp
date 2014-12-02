#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Node {
	char c;
	int idx;
	bool operator < (const Node &n) const {
		return c < n.c;
	}
};

char str[100010];
Node ans[100010];
int main( void ) {
	freopen("1031.in", "r", stdin);
	scanf("%s", str);
	int l = strlen(str);
	for (int i = 0; i < l; i++) {
		ans[i].c = str[i];
		ans[i].idx = i;
	}
	sort(ans, ans + l);
	for (int i = 0; i < l; i++) {
		printf("%c", str[(l - 1 + ans[i].idx) % l]);
	}
	return 0;
}
