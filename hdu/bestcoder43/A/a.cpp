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
set<long long> s;

int main() {
	freopen("b.in", "r", stdin);
	cin >> T;
	while (T--) {
		s.clear();
		scanf("%d %lld", &n, &p);
		long long x;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &x);
			s.insert(x);
		}
		for (set<long long>::iterator it = s.begin(); it != s.end(); it++) {
			long long now = *it;
			set<long long>::iterator idx = s.lower_bound(p - now);
			cout << *idx << endl;
		}
	}
	


	return 0;
}
