#include <bits/stdc++.h>

using namespace std;

const double INF = 1e10;
const double eps = 1e-8;

struct Point{
	int x, y;
	Point() {}
	Point(int a, int b) : x(a), y(b) {}
};

int n;
Point p[2005];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i].x >> p[i].y;
	if (n < 3) {
		cout << 0 << endl;
		return 0;
	}
	long long tot = (long long)n * (n - 1) * (n - 2) / 6;;
	long long sum = 0;
	vector<double> ans;
	for (int i = 0; i < n; i++) {
		ans.clear();
		for (int j = i + 1; j < n; j++) {
			int dx = p[j].x - p[i].x;
			int dy = p[j].y - p[i].y;
			double k;
			if (dx == 0) k = INF;
			else if (dy == 0) k = 0.0;
			else k = (double)dy / (double)dx;
			ans.push_back(k);
		}
		sort(ans.begin(), ans.end());
		double num = ans[0];
		int cnt = 0;
		for (int j = 0; j < ans.size(); j++) {
			if (fabs(ans[j] - num) < eps) {
				cnt++;
			} else {
				sum += (long long)cnt * ((long long)cnt - 1ll) / 2;;
				cnt = 1;
				num = ans[j];
			}
		}
		sum += (long long)cnt * ((long long)cnt - 1ll) / 2;
	}
	cout << tot - sum << endl;
	return 0;
}