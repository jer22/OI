#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

using namespace std;

stack<int> s;
int ans = 0;
int main() {
	freopen("1981.in", "r", stdin);
	int t;
	char c;
	scanf("%d", &t);
	t %= 10000;
	s.push(t);
	while ((c = getchar()) != '\n') {
		scanf("%d", &t);
		t %= 10000;
		if (c == '+') {
			s.push(t);
		} else {
			int top = s.top();
			s.pop();
			t *= top;
			t %= 10000;
			s.push(t);
		}
	}
	while (!s.empty()) {
		t = s.top();
		s.pop();
		ans += t;
		ans %= 10000;
	}
	ans %= 10000;
	printf("%d\n", ans);
	return 0;
}
