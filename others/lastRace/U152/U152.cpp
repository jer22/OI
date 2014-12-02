#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

int m, q;
string str;
string letter[15];
int question[1000010][2];
int c[11][1000010];

int lowbit(int x) {
	return (x & (-x));
}

int insert(int i, int pos) {
	for (int j = pos; j < 1000010; j += lowbit(j)) {
		c[i][j]++;
	}
	return 0;
}

int getSum(int i, int pos) {
	int ans = 0;
	for (int j = pos; j > 0; j -= lowbit(j)) {
		ans += c[i][j];
	}
	return ans;
}

int main() {
	freopen("U152.in", "r", stdin);
	scanf("%d %d", &m, &q);
	cin >> str;
	for (int i = 0; i < m; i++) {
		cin >> letter[i];
	}
	for (int i = 0; i < q; i++) {
		scanf("%d %d", &question[i][0], &question[i][1]);
	}
	for (int i = 0; i < m; i++) {
		int pos = 0;
		while ((pos = (str.find(letter[i], pos))) != -1) {
			insert(i, pos + 1);
			pos++;
		}
	}
	for (int i = 0; i < q; i++) {
		int l = question[i][0];
		int r = question[i][1];
		int ans = 0;
		for (int j = 0; j < m; j++) {
			int len=letter[j].size();
			if (r - len + 1 >= l - 1)
				ans += getSum(j, r - len + 1) - getSum(j, l - 1);
		}
		printf("%d\n", ans);
	}

	return 0;
}
