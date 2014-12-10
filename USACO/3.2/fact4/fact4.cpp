/*
ID:shijiey1
PROG:fact4
LANG:C++
*/

/*
一边乘一边模，末尾有0就去掉。
也有更好的做法就是遇到2和5continue。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n;
int s = 1;
int main() {
	freopen("fact4.in", "r", stdin);
	freopen("fact4.out", "w", stdout);
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) {
		s *= i;
		while (!(s % 10)) {
			s/= 10;
		}
		s %= 10000;
		// cout << i << ' ' << s << endl;
	}
	printf("%d\n", s % 10);
	return 0;
}
