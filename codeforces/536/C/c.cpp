#include <bits/stdc++.h>

#define pii pair<int, int>
#define mp(x, y) make_pair(x, y)

using namespace std;

struct Line{
	int k, b, id;
	Line() {}
	Line(int c, int d) : k(c), b(d) {}
	bool operator < (const Line &l) const {
		if (k != l.k) return k < l.k;
		return b < l.b;
	}
};

int n;
Line l[200005], tmp[200005];
bool cmp(Line a, Line b) {
	return a.id < b.id;
}
struct Stack{
	Line elements[200005];
	int siz;
	Stack() {
		memset(elements, 0, sizeof(elements));
		siz = 0;
	}
	bool empty() { return !siz; }
	Line top() {
		return elements[siz];
	}
	Line sec() {
		return elements[siz - 1];
	}
	void pop() { if (siz > 0) siz--; }
	void push(Line e) {
		elements[++siz] = e;
	}
	int size() { return siz; }
	
	void print() {
		sort(elements + 1, elements + siz + 1, cmp);
		for (int i = 1; i <= siz; i++)
			cout << elements[i].id << " \n"[i == siz];
	}
};

pii cross(Line a, Line b) {
	int dk = (a.b - b.b) * a.k * b.k;
	int db = (b.k - a.k) * a.b * b.b;
	return mp(dk, db);
}

bool fuck(pii a, pii b) {
	return a.first * b.second < a.second * b.first;
}

int main() {
	// freopen("c.in", "r", stdin);
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> tmp[i].k >> tmp[i].b;
		tmp[i].id = i;
	}
	sort(tmp + 1, tmp + n + 1);
	int m = 0;


	for (int i = 1; i <= n; i++) {
		l[++m] = tmp[i];
	}
	// for (int i = 1; i <= m; i++)
	// 	cout << l[i].k << ' ' << l[i].b << endl;
	Stack s = Stack();
	for (int i = 1; i <= m; i++) {
		// cout << l[i].k << ' ' << l[i].b << endl;
		while (!s.empty()) {
			if (l[i].b > s.top().b) s.pop();
			else if (l[i].k != s.top().k && l[i].b == s.top().b) s.pop();
			else break;
		}
		while (s.size() >= 2) {
			pii x1 = cross(l[i], s.top());
			pii x2 = cross(s.top(), s.sec());
			if (fuck(x1, x2)) {
				s.pop();
			}
			else break;
		}
		s.push(l[i]);
	}

	s.print();
	return 0;
}
