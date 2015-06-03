#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <stack>

using namespace std;

const int MAXN = 1005;

struct Node{
	int sum, height, col, ans;
	Node() {}
	Node(int a, int b, int c, int d) : sum(a), height(b), col(c), ans(d) {}
};

int n, m;
int arr[MAXN][MAXN];
int up[MAXN][MAXN];
int main() {
	freopen("BOB.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == arr[i - 1][j]) up[i][j] = up[i - 1][j] + 1;
			else up[i][j] = 1;
		}
	}
	long long ans = 0;
	stack<Node> s;
	for (int i = 1; i <= n; i++) {
		while (!s.empty()) s.pop();
		s.push(Node(0, -1, 0, 0));
		for (int j = 1; j <= m; j++) {
			int sum = 1;
			while (s.top().height >= up[i][j] && s.top().col == arr[i][j]) {
				sum += s.top().sum;
				s.pop();
			}
			long long t = sum * up[i][j];
			if (arr[i][j] == s.top().col) t += s.top().ans;
			ans += t;
			s.push(Node(sum, up[i][j], arr[i][j], t));
		}

	}
	cout << ans << endl;
	return 0;
}
