#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

struct Node{
	int idx, height;
};

int n, m;
int arr[2010][2010];
int up0[2010][2010];
int up1[2010][2010];
int right0[2010];
int right1[2010];
int left0[2010];
int left1[2010];

void initUp() {
	memset(up0, 0, sizeof(up0));
	memset(up1, 0, sizeof(up1));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			// up0[i][j] : 点(i, j)向上最多能扩展多少0
			// 若arr[i][j]==1, up0[i][j]=0
			if (arr[i][j]) {
				up0[i][j] = 0;
				up1[i][j] = up1[i - 1][j] + 1;
			} else {
				up0[i][j] = up0[i - 1][j] + 1;
				up1[i][j] = 0;
			}
		}
	}
}

int getMaxSquare() {
	// 最大正方矩阵
	int ans0 = 0;
	int ans1 = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (arr[i][j]) {
				up0[i][j] = 0;
				up1[i][j] = min(up1[i - 1][j - 1], min(up1[i][j - 1], up1[i - 1][j])) + 1;
			}
			else {
				up1[i][j] = 0;
				up0[i][j] = min(up0[i - 1][j - 1], min(up0[i][j - 1], up0[i - 1][j])) + 1;
			}
			ans0 = max(ans0, up0[i][j]);
			ans1 = max(ans1, up1[i][j]);
		}
	}
	return max(ans0, ans1);
}

int main() {
	freopen("1057.in", "r", stdin);
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			scanf("%d", &arr[i][j]);
			if (!((i + j) % 2)) {
				arr[i][j] = arr[i][j] ^ 1;
			}
		}
	}
	int ans = getMaxSquare();
	printf("%d\n", ans * ans);
	initUp();

	int maxans0 = 0;
	int maxans1 = 0;
	for (int i = 1; i <= n; i++) {
		stack<Node> s0r;
		stack<Node> s1r;
		stack<Node> s0l;
		stack<Node> s1l;
		for (int j = 1; j <= m; j++) {
			Node t0, t1;
			t0.idx = t1.idx = j;
			t0.height = up0[i][j];
			t1.height = up1[i][j];
			if (s0r.empty() || t0.height >= s0r.top().height) {
				s0r.push(t0);
			} else {
				while (!s0r.empty() && s0r.top().height > t0.height) {
					Node t = s0r.top();
					s0r.pop();
					right0[t.idx] = (t0.idx - t.idx) * t.height;
				}
				s0r.push(t0);
			}
			if (s1r.empty() || t1.height >= s1r.top().height) {
				s1r.push(t1);
			} else {
				while (!s1r.empty() && s1r.top().height > t1.height) {
					Node t = s1r.top();
					s1r.pop();
					right1[t.idx] = (t1.idx - t.idx) * t.height;
				}
				s1r.push(t1);
			}

		}
		while (!s0r.empty()) {
			Node t = s0r.top();
			s0r.pop();
			right0[t.idx] = t.height * (m - t.idx + 1);
		}
		while (!s1r.empty()) {
			Node t = s1r.top();
			s1r.pop();
			right1[t.idx] = t.height * (m - t.idx + 1);
		}
		for (int j = m; j >= 1; j--) {
			Node t0, t1;
			t0.idx = t1.idx = j;
			t0.height = up0[i][j];
			t1.height = up1[i][j];
			if (s0l.empty() || t0.height >= s0l.top().height) {
				s0l.push(t0);
			} else {
				while (!s0l.empty() && s0l.top().height > t0.height) {
					Node t = s0l.top();
					s0l.pop();
					left0[t.idx] = (t.idx - t0.idx) * t.height;
				}
				s0l.push(t0);
			}
			if (s1l.empty() || t1.height >= s1l.top().height) {
				s1l.push(t1);
			} else {
				while (!s1l.empty() && s1l.top().height > t1.height) {
					Node t = s1l.top();
					s1l.pop();
					left1[t.idx] = (t.idx - t0.idx) * t.height;
				}
				s1l.push(t1);
			}

		}
		while (!s0l.empty()) {
			Node t = s0l.top();
			s0l.pop();
			left0[t.idx] = t.height * (t.idx);
		}
		while (!s1l.empty()) {
			Node t = s1l.top();
			s1l.pop();
			left1[t.idx] = t.height * (t.idx);
		}
		for (int j = 1; j <= m; j++) {
			maxans0 = max(maxans0, left0[j] + right0[j] - up0[i][j]);
			maxans1 = max(maxans1, left1[j] + right1[j] - up1[i][j]);
		}

	}



	printf("%d\n", max(maxans0, maxans1));
	return 0;
}
