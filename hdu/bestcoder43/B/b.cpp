/**
*　　　　　　　　┏┓　　　┏┓+ +
*　　　　　　　┏┛┻━━━┛┻┓ + +
*　　　　　　　┃　　　　　　　┃ 　
*　　　　　　　┃　　　━　　　┃ ++ + + +
*　　　　　　 ████━████ ┃+
*　　　　　　　┃　　　　　　　┃ +
*　　　　　　　┃　　　┻　　　┃
*　　　　　　　┃　　　　　　　┃ + +
*　　　　　　　┗━┓　　　┏━┛
*　　　　　　　　　┃　　　┃　　　　　　　　　　　
*　　　　　　　　　┃　　　┃ + + + +
*　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting　　　　　　　
*　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug　　
*　　　　　　　　　┃　　　┃
*　　　　　　　　　┃　　　┃　　+　　　　　　　　　
*　　　　　　　　　┃　 　　┗━━━┓ + +
*　　　　　　　　　┃ 　　　　　　　┣┓
*　　　　　　　　　┃ 　　　　　　　┏┛
*　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
*　　　　　　　　　　┃┫┫　┃┫┫
*　　　　　　　　　　┗┻┛　┗┻┛+ + + +
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>

using namespace std;

int T;
int n;
long long p;
multiset<long long> s;
long long arr[100005];

int main() {
	freopen("b.in", "r", stdin);
	while (~scanf("%d %lld", &n, &p)) {
		s.clear();
		long long x;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			arr[i] = x;
			s.insert(x);
		}
		long long ans = 0;
		for (int i = 0; i < n; i++) {
			long long now = arr[i];
			set<long long>::iterator it = s.lower_bound(now);

			s.erase(it);
			it = s.lower_bound(p - now);
			if (it != s.begin()) it--;
			ans = max(ans, (now + *it) % p);
			it = s.lower_bound(p + p - now);
			if (it != s.begin()) it--;
			ans = max(ans, (now + *it) % p);

			s.insert(now);
		}


		cout << ans << endl;
	}
	


	return 0;
}
