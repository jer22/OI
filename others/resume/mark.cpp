#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

struct score {
	int value;
	int pos;
	int rank;
	bool operator < (const score &s) const {
		return value > s.value;
	}
};

int n, m;
int q;
score s[1010];
int main() {
	freopen("mark.in", "r", stdin);
	freopen("mark.out", "w", stdout);
	scanf("%d %d", &n, &m);
	int t = n / m;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &s[i].value);
		s[i].pos = i;
	}
	scanf("%d", &q);
	sort(s + 1, s + n + 1);
	int k = 0;
	s[0].value = -1;
	s[0].rank = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i].value == s[i - 1].value) {
			s[i].rank = s[i - 1].rank;
		} else {
			s[i].rank = s[i - 1].rank + 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (s[i].pos == q) {
			if (s[i].rank % 2) {
				printf("%d\n", (s[i].rank - 1) / t + 1);
			} else {
				printf("%d\n", s[i].rank / t);
			}
		}
	}

	return 0;
}
