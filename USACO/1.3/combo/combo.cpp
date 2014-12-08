/*
ID:shijiey1
PROG:combo
LANG:C++
*/

/*
数据范围超小，所以枚举枚举枚举。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>

using namespace std;

int n;
int john[3];
int lock[3];
map<int, int> done;
int main() {
	freopen("combo.in", "r", stdin);
	freopen("combo.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < 3; i++) {
		scanf("%d", &john[i]);
	}
	for (int i = 0; i < 3; i++) {
		scanf("%d", &lock[i]);
	}
	int a, b, c;
	int cnt = 0;
	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			for (int k = -2; k <= 2; k++) {
				a = (john[0] + i + n - 1) % n + 1;
				b = (john[1] + j + n - 1) % n + 1;
				c = (john[2] + k + n - 1) % n + 1;
				if (!done[a * 100 + b * 10 + c]) {
					cnt++;
					done[a * 100 + b * 10 + c] = 1;
				}
				a = (lock[0] + i + n - 1) % n + 1;
				b = (lock[1] + j + n - 1) % n + 1;
				c = (lock[2] + k + n - 1) % n + 1;
				if (!done[a * 100 + b * 10 + c]) {
					cnt++;
					done[a * 100 + b * 10 + c] = 1;
				}
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}
