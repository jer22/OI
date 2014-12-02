#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>

#define MAXN 1010

using namespace std;

int n;
int number[MAXN];
char re[MAXN << 1];
int top = 0;
stack<int> s1;
stack<int> s2;

bool canPush(stack<int> s, int x) {
	stack<int> st = s;
	bool flag = true;
	while (!st.empty()) {
		if (st.top() < x) {
			flag = false;
			break;
		}
		st.pop();
	}
	return flag;
}

int main() {
	freopen("pid401.in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &number[i]);
	}
	int now = 1;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		while (true) {
			if (!s1.empty() && s1.top() == now) {
				s1.pop();
				re[top++] = 'b';
				now++;
			}else if (!s2.empty() && s2.top() == now) {
				s2.pop();
				re[top++] = 'd';
				now++;
			} else {
				break;
			}
		}
		if (canPush(s1, number[i])) {
			s1.push(number[i]);
			re[top++] = 'a';
			continue;
		} else if (canPush(s2, number[i])) {
			s2.push(number[i]);
			re[top++] = 'c';
			continue;
		}
		
		if (canPush(s1, number[i])) {
			s1.push(number[i]);
			re[top++] = 'a';
			continue;
		} else if (canPush(s2, number[i])) {
			s2.push(number[i]);
			re[top++] = 'c';
			continue;
		}
		flag = true;
		break;
	}
	while (true) {
		if (!s1.empty() && s1.top() == now) {
			s1.pop();
			re[top++] = 'b';
			now++;
		}else if (!s2.empty() && s2.top() == now) {
			s2.pop();
			re[top++] = 'd';
			now++;
		} else {
			flag = true;
			break;
		}
	}
	if (now != n + 1) {
		printf("0\n");
		return 0;
	}
	printf("%c",re[0]);
	for (int i = 1; i < top; i++) {
		printf(" %c", re[i]);
	}
	return 0;
}
