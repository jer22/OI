#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <set>

using namespace std;

int n, m;
char arr[111][111];
set<int> ans;
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", arr[i]);
	}
	int pre = -1;
	int flag = false;
	for (int j = 0; j < m; j++) {
		flag = false;
		for (int i = 0; i < n - 1; i++) {
			if ((pre == -1 || arr[i + 1][pre] == arr[i][pre]) && arr[i + 1][j] < arr[i][j]) {
				flag = true;
				break;
			}
		}
		if (!flag) pre = j;
		if (pre != -1) ans.insert(pre);
	}
	int siz = ans.size();
	printf("%d\n", m - siz);
	return 0;
}
