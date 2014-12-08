/*
ID:shijiey1
PROG:beads
LANG:C++
*/

/*
很恶心的模拟题。每个点向左向右分别扫一次，加起来的长度就是答案。如果长度＞l，那么答案就是l。
每次向左或者向右扫时，记录下第一个非'w'的颜色，然后遇到不同的非'w'的颜色就终止。
我把原来的数组扩大成了3倍，如果滚动着扫也可以，但要注意长度大于l的时候就要终止，否则像aaaa这种就会有死循环。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n;
char str[2000];
int maxans = 0;
int main() {
	freopen("beads.in", "r", stdin);
	freopen("beads.out", "w", stdout);
	scanf("%d\n", &n);
	scanf("%s", str);
	for (int i = 0; i < n; i++) {
		str[i + n] = str[i];
		str[i + n + n] = str[i];
	}
	for (int i = n; i < n * 2; i++) {
		int cnt1 = 0, cnt2 = 0;
		char temp;
		bool flag = false;
		for (int j = 1; j <= n; j++) {
			if (!flag) {
				if (str[i - j] != 'w') {
					temp = str[i - j];
					flag = true;
				}
			} else {
				if (str[i - j] != temp && str[i - j] != 'w') {
					break;
				}
			}
			cnt1++;
		}
		
		flag = false;
		for (int j = 0; j < n; j++) {
			if (!flag) {
				if (str[i + j] != 'w') {
					temp = str[i + j];
					flag = true;
				}
			} else {
				if (str[i + j] != temp && str[i + j] != 'w') {
					break;
				}
			}
			cnt2++;
		}
		int ans = min(n, cnt1 + cnt2);
		maxans = max(ans, maxans);
	}
	printf("%d\n", maxans);

	return 0;
}
