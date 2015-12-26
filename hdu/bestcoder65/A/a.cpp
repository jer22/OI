#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int T;
int n;
string a, b;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		cin >> a >> b;
		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (a[i] == 'A' && b[i] != 'U') {
				flag = false;
				break;
			}
			if (a[i] == 'C' && b[i] != 'G') {
				flag = false;
				break;
			}
			if (a[i] == 'G' && b[i] != 'C') {
				flag = false;
				break;
			}
			if (a[i] == 'T' && b[i] != 'A') {
				flag = false;
				break;
			}
		}
		if (flag) printf("YES\n");
		else printf("NO\n");
	}


	return 0;
}
