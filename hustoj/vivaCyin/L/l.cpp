#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

struct Node{
	int tim, pos;
	Node() {}
	Node(int a, int b) : tim(a), pos(b) {}
	bool operator < (const Node &n) const {
		return tim < n.tim;
	}
};

int T, n, m;
Node arr[20005];
int ans[20005];
int main() {
	freopen("l.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d", &n, &m);
		getchar();
		int a, b, c;
		char tmp;
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cin >> a >> tmp >> b >> tmp >> c;
			int tim = a * 3600 + b * 60 + c;

			arr[i] = Node(tim, i);
		}
		sort(arr, arr + n);
		int pre = -0x3f3f3f3f;
		memset(ans, 0, sizeof(ans));
		for (int i = 0; i < n; i++) {
			if (arr[i].tim >= pre + m) {
				ans[cnt++] = arr[i].pos;
				pre = arr[i].tim;
			}
		}
		printf("%d\n", cnt);
		sort(ans, ans + cnt);
		for (int i = 0; i < cnt; i++) {
			if (i) printf(" ");
			printf("%d", ans[i] + 1);
		}
		printf("\n");
	}


	return 0;
}
