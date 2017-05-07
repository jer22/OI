#include <bits/stdc++.h>

using namespace std;

const int MAXN = 3005;

struct Point{
	int x, y, type;
	bool operator < (const Point &n) const {
		return y < n.y;
	}
};

struct Line{
	int height, l, r;
	bool operator < (const Line &n) const {
		return height < n.height;
	}
};

int v, st, n;
Line lines[MAXN];
Point arr[MAXN << 1];
int dp[MAXN << 1];
int pre[MAXN << 1];
double cal(double xa, double ya,double xb, double yb){
	return ((xa*xb+ya*yb)/sqrt(xa*xa+ya*ya)/sqrt(xb*xb+yb*yb));
}
int main() {
	freopen("input.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &v, &st, &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d %d", &lines[i].l, &lines[i].r, &lines[i].height);
		arr[i * 2 - 1] = {lines[i].l, lines[i].height, 1};
		arr[i * 2] = {lines[i].r, lines[i].height, -1};
	}
	sort(arr + 1, arr + n + 1);
	arr[0] = {st, 0, 0};
	dp[0] = 1;
	for (int i = 1; i <= n * 2; i++) {
		std::vector<pair<double,int> > temp;
		temp.clear();
		for (int j=0 ;j<i;j++){
			temp.push_back(make_pair(cal(1,0,arr[j].x-arr[i].x,arr[j].y-arr[i].y),j));
		}
		sort(temp.begin(),temp.end());
		for (auto now : temp) {
			
		}

		for (int j = 0; j < i; j++) {
			if (!dp[j]) continue;

		}
	}


	return 0;
}
