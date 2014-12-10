/*
ID:shijiey1
PROG:window
LANG:C++
*/

/*
矩形切割。
执行非查询操作时更新高度，创建窗体和置顶时时height[i]=top++，置底height[i]=bot--，删除窗体时vis[i]=false。
执行查询操作时dfs，每次用比窗口i高一层的窗体把i切割成最多4个矩形，然后递归。
这种方法叫上浮法，对于当前dfs的窗口i，想象它向上浮，遇上了第一个比它高的矩形，被它切成了最多4个矩形，然后4个小矩型再继续上浮，直到露出水面时剩下了许多很小的矩形，它们的面积之和就是窗口i的能看见的面积。
途中遇到vis[j]=false的矩形直接跳过。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Window{
	int x1, y1, x2, y2;
	void init(int a, int b, int c, int d) {
		x1 = a, y1 = b, x2 = c, y2 = d;
	}
};

int n = 0;
int name[150];
bool del[805];
Window windows[805];
int height[805];
int top = 1;
int bot = 0;
vector<int> higher;

int cmp(int a, int b) {
	return height[a] < height[b];
}

int dfs(int now, Window k) {
	if (now == higher.size()) {
		return (k.x2 - k.x1) * (k.y2 - k.y1);
	}
	int area = 0;
	Window cut = windows[higher[now]];
	Window base = k;
	// not intersected
	if (cut.x2 <= base.x1 || cut.x1 >= base.x2 || cut.y2 <= base.y1 || cut.y1 >= base.y2) {
		return dfs(now + 1, k);
	}
	Window t;
	if (cut.x1 > base.x1 && cut.x1 < base.x2) {
		t.init(base.x1, base.y1, cut.x1, base.y2);
		area += dfs(now + 1, t);
		base.x1 = cut.x1;
	}
	if (cut.x2 > base.x1 && cut.x2 < base.x2) {
		t.init(cut.x2, base.y1, base.x2, base.y2);
		area += dfs(now + 1, t);
		base.x2 = cut.x2;
	}
	if (cut.y1 > base.y1 && cut.y1 < base.y2) {
		t.init(base.x1, base.y1, base.x2, cut.y1);
		area += dfs(now + 1, t);
		base.y1 = cut.y1;
	}
	if (cut.y2 > base.y1 && cut.y2 < base.y2) {
		t.init(base.x1, cut.y2, base.x2, base.y2);
		area += dfs(now + 1, t);
	}
	return area;
}

void solve(int k) {
	higher.clear();
	for (int i = 0; i < n; i++) {
		if (height[i] <= height[k] || del[i]) continue;
		higher.push_back(i);
	}
	sort(higher.begin(), higher.end(), cmp);	
	int area = dfs(0, windows[k]);
	double ans = (double)area / ((windows[k].x2 - windows[k].x1) * (windows[k].y2 - windows[k].y1));
	printf("%.3lf\n", ans * 100);
}

int main() {
	freopen("window.in", "r", stdin);
	freopen("window.out", "w", stdout);
	char c;
	int x1, x2, y1, y2;
	Window win;
	while (cin >> c) {
		char w;
		char blank;
		cin >> blank >> w;
		if (c == 'w') {
			cin >> blank >> x1 >> blank >> y1 >> blank >> x2 >> blank >> y2;
			win.init(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
			name[w] = n;
			windows[n] = win;
			height[n++] = top++;
		} else if (c == 't') {
			int t = name[w];
			height[t] = top++;
		} else if (c == 'b') {
			int t = name[w];
			height[t] = bot--;
		} else if (c == 'd') {
			int t = name[w];
			del[t] = 1;
		} else if (c == 's') {
			int t = name[w];
			solve(t);
		}
		cin >> blank;
	}


	return 0;
}
