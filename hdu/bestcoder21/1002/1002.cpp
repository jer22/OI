#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>

#define MOD 1000000007

using namespace std;

struct Que{
	long long num;
	int pos;
};

Que query[100010];
Que res[100010];
int cnt = 0;

int cmp1(Que a, Que b) {
	return a.num < b.num;
}

int cmp2(Que a, Que b) {
	return a.pos < b.pos;
}

int main() {
	freopen("1002.in", "r", stdin);
	int n;
	while (~scanf("%d", &n)) {
		query[cnt].num = n;
		query[cnt].pos = cnt++;
	}
	sort(query, query + cnt, cmp1);
	long long base = 1;
	long long ans = 1;
	int idx = 0;
	for (int i = 1; i <= 10000000; i++) {
		base *= i;
		base %= MOD;
		ans *= base;
		ans %= MOD;
		while (i == query[idx].num) {
			query[idx++].num = ans;
			// query[idx].pos = query[idx++].pos;
		}
	}
	sort(query, query + idx, cmp2);
	for (int i = 0; i < idx; i++) {
		cout << query[i].num << endl;
	}
	return 0;
}
