#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct Hand {
	int left;
	int right;
	bool operator < (const Hand &h) const {
		return left * right < h.left * h.right;
	}
};

struct Num {
	int a[5050];
	int len;
	void print() {
		for (int i = len - 1; i >= 0; i--) {
			printf("%d", a[i]);
		}
		printf("\n");
	}
};

int n;
Hand hand[1010];

Num operator * (Num a, int b) {
	Num c;
	c.len = a.len;
	memset(c.a, 0, sizeof(c.a));
	for (int i = 0; i < a.len; i++) {
		c.a[i] += a.a[i] * b;
		c.a[i + 1] += c.a[i] / 10;
		c.a[i] %= 10;
	}
	c.len++;
	while (c.a[c.len - 1] >= 10) {
		c.a[c.len] += c.a[c.len - 1] / 10;
		c.a[c.len - 1] %= 10;
		c.len++;
	}
	while (c.len > 1 && !c.a[c.len - 1]) c.len--;
	return c;
}

Num operator / (Num a, int b) {
	Num c;
	memset(c.a, 0, sizeof(c.a));
	c.len = a.len;
	int d = 0;
	for (int i = c.len - 1; i >= 0; i--) {
		d = d * 10 + a.a[i];
		c.a[i] = d / b;
		d %= b;
	}
	while (c.len > 0 && !c.a[c.len - 1])c.len--;

	return c;
}

int main() {
	freopen("1080.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i <= n; i++) {
		scanf("%d %d", &hand[i].left, &hand[i].right);
	}
	sort(hand + 1, hand + n + 1);
	Num ans;
	ans.a[0] = 1;
	ans.len = 1;
	Num re;
	re.a[0] = 0;
	re.len = 0;
	for (int i = 0; i < n; i++) {
		ans = ans * hand[i].left;
		re = ans / hand[i + 1].right;
	}
	ans = ans / hand[n].right;
	/*if (!ans.len) {
		printf("1\n");
	} else {*/
		ans.print();
	/*}*/

	return 0;
}
