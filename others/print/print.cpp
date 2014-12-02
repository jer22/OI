#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, m;
// 存放每个数的优先级
int arr[110];
// 优先级为i的数当前有几个
int num[15];
int main() {
	freopen("print.in", "r", stdin);
	freopen("print.out", "w", stdout);
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		num[arr[i]]++;
	}
	// 当前队列中最大的优先级
	int maxPriority = 9;
	// 出了几次队列
	int now = 0;
	while (maxPriority) {
		for (int i = 0; i < n; i++) {
			// arr[i] > 0即还未出列
			if (arr[i] > 0) {
				// 更新maxPriority
				while (maxPriority > 0 && !num[maxPriority]) maxPriority--;
				if (!maxPriority) break;
				// 找到当前队列优先级最高的
				if (arr[i] == maxPriority) {
					// 出队个数+1
					now++;
					// arr[i]标记为以出队
					arr[i] = -now;
					// 优先级为maxPriority的个数减一
					num[maxPriority]--;
				}
				// 更新maxPriority；
				while (maxPriority > 0 && !num[maxPriority]) maxPriority--;
			}
		}
	}
	printf("%d\n", -arr[m]);
	return 0;
}
