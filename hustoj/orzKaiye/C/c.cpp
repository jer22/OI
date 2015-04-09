#include <bits/stdc++.h>

using namespace std;

struct Event{ char op; int pos; };

int n, m, q;
stack<Event> events;
multiset<int> hor, ver;
multiset<int> hh, vv;
stack<long long> res;
multiset<int>::iterator it1, it2, it;
int init(multiset<int> s) {
	int ans = -1;
	for (it1 = s.begin(); it1 != s.end(); ) {
		it2 = it1++;
		if (it1 == s.end()) break;
		ans = max(ans, *it1 - *it2);
	}
	return ans;
}

int query(multiset<int> &s, multiset<int> &ss, int pos) {
	s.erase(s.find(pos));
	ss.erase(ss.find(-pos));
	it1 = s.lower_bound(pos);
	it2 = ss.lower_bound(-pos);
	return *it1 + *it2;
}

int main() {
	cin >> n >> m >> q;
	char op[2];
	int pos;
	for (int i = 0; i < q; i++) {
		cin >> op >> pos;
		events.push((Event){op[0], pos});
		if (op[0] == 'H') hor.insert(pos), hh.insert(-pos);
		else ver.insert(pos), vv.insert(-pos);
	}
	hor.insert(0), hh.insert(0);
	hor.insert(m), hh.insert(-m);
	ver.insert(0), vv.insert(0);
	ver.insert(n), vv.insert(-n);
	int maxh = init(hor), maxv = init(ver);
	long long ans = (long long)maxh * (long long)maxv;
	res.push(ans);
	while (!events.empty()) {
		Event e = events.top();
		events.pop();
		if (e.op == 'H')
			maxh = max(maxh, query(hor, hh, e.pos));
		else maxv = max(maxv, query(ver, vv, e.pos));
		ans = (long long)maxh * (long long)maxv;
		res.push(ans);
	}
	res.pop();
	while (!res.empty()) {
		cout << res.top() << endl;
		res.pop();
	}
	return 0;
}
