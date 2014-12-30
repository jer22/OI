#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node{
	int weight, speed, idx;
	bool operator < (const Node &n) const {
		if (weight != n.weight) return weight < n.weight;
		return speed > n.speed;
	}
}arr[1005];

int n = 1;
int cnt = 0, idx = -1;
int dp[1005];
int pre[1005];

void print(int i) {
	if (pre[i] != -1) {
		print(pre[i]);
	}
	printf("%d\n", arr[i].idx);
}

int main() {
	freopen("1160.in", "r", stdin);
	while (~scanf("%d %d", &arr[n].weight, &arr[n].speed))
		arr[n].idx = n++;
	n--;
	sort(arr + 1, arr + n + 1);
	memset(pre, -1, sizeof(pre));
	dp[1] = 1;
	// for (int i = 1; i <= n; i++)
	// 	printf("%d %d\n", arr[i].weight, arr[i].speed);
	
	for (int i = 2; i <= n; i++) {
		dp[i] = 1;
		for (int j = i - 1; j >= 1; j--) {
			if (arr[j].weight < arr[i].weight && arr[j].speed > arr[i].speed && dp[j] + 1 > dp[i]) {
				dp[i] = dp[j] + 1;
				pre[i] = j;
			}
		}
		if (dp[i] > cnt) {
			cnt = dp[i];
			idx = i;
		}
	}
	printf("%d\n", cnt);
	print(idx);

	return 0;
}
