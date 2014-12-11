#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int hp1, atk1, df1;
int hp2, atk2, df2;
int c1, c2, c3;
int cost = 0x3f3f3f3f;
int main() {
	cin >> hp1 >> atk1 >> df1;
	cin >> hp2 >> atk2 >> df2;
	cin >> c1 >> c2 >> c3;
	for (int x2 = 0; x2 < 2000; x2++) {
		for (int x3 = 0; x3 < 2000; x3++) {
			int t = atk1 - df2 + x2;
			if (t <= 0) break;
			int tim1 = hp2 / t;
			if (hp2 % t) tim1++;
			t = atk2 - df1 - x3;
			if (t <= 0) {
				cost = min(cost, x2 * c2 + x3 * c3);
				continue;
			}
			// tim1 * t < hp1 + x1
			int x1 = tim1 * t - hp1 + 1;
			if (x1 < 0) x1 = 0;
			cost = min(cost, x1 * c1 + x2 * c2 + x3 * c3);
		}
	}
	cout << cost << endl;
	return 0;
}
