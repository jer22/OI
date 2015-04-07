#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

int n;
int height[250005];
stack<int> s;
int main() {
	freopen("1113.in", "r", stdin);
	scanf("%d", &n);
	int a;
	int ans = 0;
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &a, &height[i]);
	for (int i = 1; i <= n; i++) {
		while (!s.empty() && height[i] <= s.top()) {
			if (s.top() == height[i]) ans++;
			s.pop();
		}
		s.push(height[i]);
	}

	printf("%d\n", n - ans);
	return 0;
}
