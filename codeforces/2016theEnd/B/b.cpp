#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int n;
int main() {
	// freopen("b.in", "r", stdin);
	scanf("%d", &n);
	int dis;
	char op[10];
	bool flag = true;
	int now = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &dis);
		scanf("%s", op);
		if (!flag) continue;
		if (!now) {
			if (op[0] != 'S') {
				flag = false;
				continue;
			}
		}
		if (now == 20000) {
			if (op[0] != 'N') {
				flag = false;
				continue;
			}
		}
		if (op[0] == 'N') {
			now -= dis;
			if (now < 0) {
				flag = false;
				continue;
			}
		} else if (op[0] == 'S') {
			now += dis;
			if (now > 20000) {
				flag = false;
				continue;
			}
		}
	}
	if (now) flag = false;
	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
