/*
ID:shijiey1
PROG:ride
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

char s1[7], s2[7];
int main() {
	freopen("ride.in", "r", stdin);
	freopen("ride.out", "w", stdout);
	scanf("%s %s", s1, s2);
	int t1 = 1, t2 = 1;
	for (int i = 0; i < strlen(s1); i++) {
		t1 *= s1[i] - 'A' + 1;
		t1 %= 47;
	}
	for (int i = 0; i < strlen(s2); i++) {
		t2 *= s2[i] - 'A' + 1;
		t2 %= 47;
	}
	if (t1 == t2) printf("GO\n");
	else printf("STAY\n");
	return 0;
}
