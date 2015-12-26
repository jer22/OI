#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

int T, n;
int main() {
	freopen("b.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);

		if (n & 1) cout << 1 << endl;
		else cout << 0 << endl;
	}


	return 0;
}
