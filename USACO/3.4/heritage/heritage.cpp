/*
ID:shijiey1
PROG:heritage
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
int cnt = 0;
int pre[29];
int in[29];
int post[29];
int n = 0;

void dfs(int in1, int in2, int pre1, int pre2, int post1, int post2) {
	// printf("%d %d %d %d %d %d\n", in1, in2, pre1, pre2, post1, post2);
	post[post2] = pre[pre1];
	int w1,w2,w3;
	for (int i = in1; i <= in2; i++) {
		if (in[i] == pre[pre1]) {
			w1=i;
			break;
		}
	}

	// while(true);
	int len=w1-in1;
	// have left child
	if (len!=0) {
		dfs(in1,in1+len-1,pre1+1,pre1 + len, post1, post1 + len - 1);
	}
	if (len != in2 - in1) {
		dfs(w1 + 1, in2, pre1 + len + 1, pre2, post1 + len, post2 - 1);
	}

}

int main() {
	freopen("heritage.in", "r", stdin);
	freopen("heritage.out", "w", stdout);
	char c;
	while ((c = getchar()) != '\n') {
		in[n++] = c - 'A' + 1;
	}
	n = 0;
	while ((c = getchar()) != '\n') {
		pre[n++] = c - 'A' + 1;
	}
	dfs(0, n - 1, 0, n - 1, 0, n - 1);
	for (int i = 0; i < n; i++) {
		printf("%c", post[i] + 'A' - 1);
	}
	printf("\n");
	return 0;
}
