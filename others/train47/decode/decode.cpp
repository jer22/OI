#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int n, m, l, k;
bool key[205];
bool str[100005];
int main() {
	freopen("decode.in", "r", stdin);
	scanf("%d %d %d %d\n", &n, &m, &l, &k);
	char c;
	for (int i = 0; i < m; i++) {
		scanf("%c", &c);
		key[i] = c - '0';
	}
	c = getchar();
	for (int i = 0; i < n; i++) {
		scanf("%c", &c);
		str[i] = c - '0';
	}
	int p = n - m + l;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < m; j++) {
			str[(j + p) % n] ^= key[j];
		}
		p += l;
	}
	p = k * l;
	for (int i = 0; i < n; i++)
		cout << str[(i + p) % n];
	cout << endl;
	return 0;
}
