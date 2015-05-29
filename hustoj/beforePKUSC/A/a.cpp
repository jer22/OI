#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T, n;
int main() {
	freopen("a.in", "r", stdin);
	scanf("%d", &T);
	int cas = 1;
	while (T--) {
		scanf("%d", &n);
		int sum = 0, x;
		for (int i = 0; i < n; i++) {
			cin >> x;
			sum += x;
		}
		sum += n;
		cout << "Case #" << cas++ << ": ";
		if (sum & 1) cout << "Bob" << endl;
		else cout << "Alice" << endl;
	}


	return 0;
}
