/*
ID:shijiey1
PROG:picture
LANG:C++
*/

/*
先处理所有的横线，竖线同理。
横边记录一个pos值，每个矩形有两条横边，下面的pos记为1，上面的pos记为-1。
将所有横边按y坐标由小到大排好序，然后枚举，横坐标上的每个点记录一个值layer。每遇到一条边i，对于边i上的每一个点x，layer[x]+=i.pos。
如果layer[j]从0变为1，周长ans++，如果layer从1变为0，同样ans++。
注意矩形的顶点只能算一次，在横边算过了竖边就不算了。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

struct Line{
	int a, b;
	int h, pos;
	void init(int aa, int bb, int hh, int ppos) {
		a = aa;
		b = bb;
		h = hh;
		pos = ppos;
	}
	bool operator < (const Line &l) const {
		if (h != l.h) return h < l.h;
		return pos > l.pos;
	}
};

int n;
Line hor[10010];
Line ver[10010];
int layer[20010];
int main() {
	freopen("picture.in", "r", stdin);
	freopen("picture.out", "w", stdout);
	scanf("%d", &n);
	int a, b, c, d;
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		hor[i << 1].init(a + 10000, c + 10000, b, 1);
		hor[(i << 1) + 1].init(a + 10000, c + 10000, d, -1);
		ver[i << 1].init(b + 10000, d + 10000, a, 1);
		ver[(i << 1) + 1].init(b + 10000, d + 10000, c, -1);
	}
	n <<= 1;
	sort(hor, hor + n);
	sort(ver, ver + n);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		Line l = hor[i];
		for (int j = l.a; j < l.b; j++) {
			if (!layer[j] && layer[j] + l.pos == 1) ans++;
			if (layer[j] == 1 && layer[j] + l.pos == 0) ans++;
			layer[j] += l.pos;
		}
	}
	memset(layer, 0, sizeof(layer));
	for (int i = 0; i < n; i++) {
		Line l = ver[i];
		for (int j = l.a; j < l.b; j++) {
			if (!layer[j] && layer[j] + l.pos == 1) ans++;
			if (layer[j] == 1 && layer[j] + l.pos == 0) ans++;
			layer[j] += l.pos;
		}
	}
	cout << ans << endl;
	return 0;
}
