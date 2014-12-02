#include <cstdio>
#include <cstring>
#include <algorithm>
#include <deque>

#define MAXN 102

using namespace std;

int n, m;
deque<int> mem;

bool exist(int a) {
	deque<int>::iterator it;
	for (it = mem.begin(); it != mem.end(); it++) {
		if (*(it) == a)
			return true;
	}
	return false;
}

int main() {
	freopen("1540.in", "r", stdin);
	scanf("%d %d", &m, &n);
	int t;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		if (mem.size() < m) {
			if (!exist(t)) {
				mem.push_back(t);
				cnt++;
			}
		} else {
			if (!exist(t)) {
				mem.pop_front();
				mem.push_back(t);
				cnt++;
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}
