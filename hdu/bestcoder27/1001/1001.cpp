#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int T;
int n;
int first, second;
int fnum, snum;
int main() {
	freopen("1001.in", "r", stdin);
	scanf("%d", &T);
	while (T--) {
		first = second = 0;
		fnum = snum = 0;
		scanf("%d", &n);
		int a, b, c;
		for (int i = 1; i <= n; i++) {
			scanf("%d %d %d", &a, &b, &c);
			int num = max(max(a, b), c);
			if (num > fnum) {
				second = first;
				first = i;
				snum = fnum;
				fnum = num;
			} else if (num > snum) {
				snum = num;
				second = i;
			}
		}
		for (int i = 1; i <= n; i++) {
			if (i > 1) cout << ' ';
			if (first == i) cout << 1;
			else if (second == i) cout << 2;
			else cout << 3;
		}
		cout << endl;
	}



	return 0;
}
