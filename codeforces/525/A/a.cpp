#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int n;
char str[200005];
int cnt[128];
int main() {
	// freopen("a.in", "r", stdin);
	cin >> n;
	n = n * 2 - 2;
	cin >> str + 1;
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')
			cnt[str[i]]++;
		else {
			if (!cnt[str[i] - 'A' + 'a']) ans++;
			else cnt[str[i] - 'A' + 'a']--;
		}
	}
	cout << ans << endl;


	return 0;
}
