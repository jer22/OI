#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

int n, a, b;
int main() {
	// freopen("a.in", "r", stdin);
	cin >>  n;
	int cnt1 = 0, cnt2 = 0;
	while (n--) {
		cin >> a >> b;
		if (a > b) cnt1++;
		else if (a < b) cnt2++;
	}
	if (cnt1 > cnt2) cout << "Mishka" << endl;
	else if (cnt1 == cnt2) cout << "Friendship is magic!^^" << endl;
	else cout << "Chris" << endl;

	return 0;
}
