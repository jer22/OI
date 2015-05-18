/* I will wait for you*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <deque>
#include <map>
#include <set>
#include <string>
#include <ext/rope>
#define make make_pair
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;

const int maxn = 5000010;
const int maxm = 1010;
const int maxs = 26;
const int inf = 0x3f3f3f3f;
const int P = 1000000007;
const double error = 1e-9;

inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (ch <= 47 || ch >= 58)
		f = (ch == 45 ? -1 : 1), ch = getchar();
	while (ch >= 48 && ch <= 57)
		x = x * 10 + ch - 48, ch = getchar();
	return x * f;
}

__gnu_cxx :: rope<char> str;

char s[maxn], t[maxn];

int main()
{
	int n = read(), len, now = 0;

	while (n--) {
		scanf("%s", s);

		if (s[0] == 'M')
			now = read();
		if (s[0] == 'P')
			now--;
		if (s[0] == 'N')
			now++;
		if (s[0] == 'I') {
			len = read();
			for (int i = 0; i < len; i++)
				t[i] = getchar(), i -= (t[i] == 10);
			t[len] = 0, str.insert(now, t);
		}
		if (s[0] == 'D')
			len = read(), str.erase(now, len);
		if (s[0] == 'G') {
			len = read(), str.copy(now, len, t);
			t[len] = 0, printf("%s\n", t);
		}
	}

	return 0;
}
