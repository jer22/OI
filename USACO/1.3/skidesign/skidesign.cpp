/*
ID:shijiey1
PROG:skidesign
LANG:C++
*/

/*
因为高度限制在1到100所以枚举每一个高度差i，i+17，然后计算费用。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

int n;
int arr[1010];
int main() {
	freopen("skidesign.in", "r", stdin);
	freopen("skidesign.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	int minans = 0x3f3f3f3f;
	for (int i = 0; i < 84; i++) {
		int ans = 0;
		int t = i + 17;
		for (int j = 0; j < n; j++) {
			if (arr[j] < i) {
				ans += abs(arr[j] - i) * abs(arr[j] - i);
			}
			if (arr[j] > t) {
				ans += abs(arr[j] - t) * abs(arr[j] - t);
			}
		}
		minans = min(ans, minans);
	}
	printf("%d\n", minans);
	return 0;
}
