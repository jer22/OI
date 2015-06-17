
/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <bits/stdc++.h>

using namespace std;

struct Node{
	int a, b;
	Node() {}
	Node(int c, int d) : a(c), b(d) {}
};

int n;
int tot = 2;
vector<Node> ans;

void dfs(int step, int l, int r) {
	if (step == n) return;
	int newnode = ++tot;
	for (int i = l; i <= r; i++) {
		ans.push_back(Node(newnode, i));
	}
	dfs(step + 1, l, r + 1);
}

void solve(int x) {
	int k = n / 2;
	for (int i = 0; i < k; i++) {
		ans.push_back(Node(x, ++tot));
		ans.push_back(Node(x, ++tot));
		dfs(1, tot - 1, tot);
	}
}

int main() {
	// freopen("d.in", "r", stdin);
	cin >> n;
	if (!(n & 1)) {
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	ans.push_back(Node(1, 2));
	solve(1);
	solve(2);
	cout << tot << ' ' << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++) {
		cout << ans[i].a << ' ' << ans[i].b << endl;
	}

	return 0;
}
