/*
ID:shijiey1
PROG:fracdec
LANG:C++
*/

/*
这道题有三个特点：恶心。
当然如果有点耐心的话还是挺水的，就是模拟模拟模拟。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int a, b;
vector<int> num;
map<pair<int, int>, int> done;
int main() {
	freopen("fracdec.in", "r", stdin);
	freopen("fracdec.out", "w", stdout);
	scanf("%d %d", &a, &b);
	if (!(a % b)) {
		printf("%d.0\n", a / b);
		return 0;
	}
	printf("%d.", a / b);
	int cnt = 0;
	int t = a / b;
	while (t) {
		cnt++;
		t /= 10;
	}
	if (!cnt) {
		cnt = 2;
	} else cnt++;
	a %= b;
	int step = 1;
	int idx = 0;
	while (a) {
		a *= 10;
		int now = a / b;
		pair<int, int> p = pair<int, int>(a, b);
		if (!done[p]) {
			num.push_back(now);
			done[p] = step;
		} else {
			idx = done[p];
			num.push_back(now);
			break;
		}

		a %= b;
		step++;
	}
	step--;
	if (!idx) {
		for (int i = 0; i < num.size(); i++) {
			printf("%d", num[i]);
		}
	} else {
		idx--;
		for (int i = 0; i < num.size(); i++) {
			if (!(cnt % 76)) {
				printf("\n");
			}
			cnt++;
			if (i == idx) {
				printf("(");
				if (!(cnt % 76)) {
					printf("\n");
				}
				cnt++;
				printf("%d", num[i]);
			} else if (i == step) {
				printf(")");
				break;
			} else {
				printf("%d", num[i]);
			}
			
		}
	}
	printf("\n");

	return 0;
}
