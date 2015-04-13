/*
* this code is made by team006
* Problem: 1694
* Verdict: Wrong Answer
* Submission Date: 2015-04-11 15:43:05
* Time: 108MS
* Memory: 1684KB
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <map>
#include <utility>
 
#define pii pair<long long, long long>
#define mp(x, y) make_pair(x, y)
 
using namespace std;
 
struct Point{
    long long x, y;
};
 
int T, n;
Point p[105];
long long dir[8][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {-1, -1}, {1, -1}, {-1, 1}, {1, 1}};
map<pii, bool> vis;
long long sx, sy, ex, ey;
int st;
 
bool dfs(long long x, long long y) {
    vis[mp(x, y)] = 1;
    if (x == ex && y == ey) return true;
    if (x == sx + 100 || x == sx - 100 || y == sy + 100 || y == sy - 100) return true;
    for (int i = 0; i < 8; i++) {
        long long nx = x + dir[i][0], ny = y + dir[i][1];
        if (vis[mp(nx, ny)]) continue;
        bool flag = true;
        for (int j = st + 1; j <= n; j++) {
            if (nx == p[j].x && ny == p[j].y) {
                flag = false;
                break;
            }
        }
        if (!flag) continue;
        if (dfs(nx, ny)) return true;
    }
    return false;
}
 
bool check(Point a, Point b, int s) {
    vis.clear();
    sx = a.x, sy = a.y;
    ex = b.x, ey = b.y;
    st = s;
    bool f1 = dfs(a.x, a.y);
    swap(sx, ex);
    swap(sy, ey);
    vis.clear();
    bool f2 = dfs(b.x, b.y);
    return (f1 & f2);
}
 
int solve() {
    for (int i = 1; i <= n; i++)
        if (!check(p[i - 1], p[i], i)) return i - 1;
    return n;
}
 
int main() {
	freopen("h.in", "r", stdin);
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> p[i].x >> p[i].y;
        cin >> p[0].x >> p[0].y;
        int ans = solve();
        printf("Case #%d: %d\n", cas, ans);
    }
 
 
    return 0;
}