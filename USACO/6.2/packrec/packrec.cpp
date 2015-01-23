/*
ID:shijiey1
LANG:C++
PROG:packrec
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <set>

using namespace std;

struct Rect{
	int x, y;
}rect[4], r;

int ans = 0x3f3f3f3f;
set<int> res;
void record() {
	if (r.x * r.y < ans) {
		ans = r.x * r.y;
		res.clear();
	}
	if (r.x * r.y == ans) {
		res.insert(min(r.x, r.y));
	}
}

void calc() {
	r.x = r.y = 0;
	// case 1
	for (int i = 0; i < 4; i++) {
		r.x += rect[i].x;
		r.y = max(r.y, rect[i].y);
	}
	record();
	// case 2
	r.x = r.y = 0;
	for (int i = 1; i <= 4; i++) {
		r.x += rect[i].x;
		r.y = max(r.y, rect[i].y);
	}
	r.x = max(r.x, rect[0].x);
	r.y += rect[0].y;
	record();
	// case 3
	r.x = max(rect[0].x + rect[1].x, rect[2].x) + rect[3].x;
	r.y = max(max(rect[0].y, rect[1].y) + rect[2].y, rect[3].y);
	record();
	// case 4, 5
	r.x = rect[0].x+max(rect[1].x, rect[2].x)+rect[3].x;
	r.y = max(max(rect[0].y, rect[1].y+rect[2].y), rect[3].y);
	record();
	// case 6
	r.x = rect[0].x + rect[1].x;
	r.y = max(rect[0].y + rect[2].y, rect[1].y + rect[3].y);
	if (rect[0].y < rect[1].y)
		r.x = max(r.x, rect[2].x + rect[1].x);
	if (rect[0].y + rect[2].y > rect[1].y)
		r.x = max(r.x, rect[2].x + rect[3].x);
	if (rect[1].y < rect[0].y)
		r.x = max(r.x, rect[0].x + rect[3].x);
	r.x = max(r.x, rect[2].x);
	r.x = max(r.x, rect[3].x);
	record();
}

void rotate(int step) {
	if (step == 4) {
		calc();
		return;
	}
	rotate(step + 1);
	swap(rect[step].x, rect[step].y);
	rotate(step + 1);
	swap(rect[step].x, rect[step].y);
}

void dfs(int step) {
	if (step == 4) {
		rotate(0);
		return;
	}
	for (int i = step; i < 4; i++) {
		swap(rect[step], rect[i]);
		dfs(step + 1);
		swap(rect[step], rect[i]);
	}
}

int main() {
	freopen("packrec.in", "r", stdin);
	freopen("packrec.out", "w", stdout);
	for (int i = 0; i < 4; i++)
		scanf("%d %d", &rect[i].x, &rect[i].y);
	dfs(0);
	printf("%d\n", ans);
	for (set<int>::iterator it = res.begin(); it != res.end(); it++) {
		printf("%d %d\n", *it, ans / (*it));
	}
	return 0;
}
