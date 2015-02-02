#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

#define lch rt << 1
#define rch rt << 1 | 1
#define lson l, mid, lch
#define rson mid + 1, r, rch

using namespace std;

const int MAXN = 100005;

struct Node{
	bool v[2], s[2], x[2];
}tree[MAXN << 2];

int n;
int r1, c1, r2, c2;
int dir[3][2] = {{-1, 0}, {0, 1}, {1, 0}};
bool a[MAXN][2][2];
void build(int l, int r, int rt) {
	if (l == r) {
		tree[rt].s[0] = tree[rt].s[1] = 1;
		return;
	}
	int mid = l + r >> 1;
	build(lson);
	build(rson);
}

void pack(Node &u, Node &ls, Node &rs, int mid) {
	u.x[0]=ls.x[0]||(ls.s[0]&&a[mid][0][0]&&rs.x[0]&&a[mid][1][0]&&ls.s[1]);//左上-右上 
	u.x[1]=rs.x[1]||(rs.s[0]&&a[mid][0][0]&&ls.x[1]&&a[mid][1][0]&&rs.s[1]);//左下-右下 
	u.s[0]=(ls.s[0]&&a[mid][0][0]&&rs.s[0])||(ls.v[0]&&a[mid][1][0]&&rs.v[1]);//左上-左下
	u.s[1]=(ls.s[1]&&a[mid][1][0]&&rs.s[1])||(ls.v[1]&&a[mid][0][0]&&rs.v[0]);//右上-右下
	u.v[0]=(ls.s[0]&&a[mid][0][0]&&rs.v[0])||(ls.v[0]&&a[mid][1][0]&&rs.s[1]);//左上-右下
	u.v[1]=(ls.s[1]&&a[mid][1][0]&&rs.v[1])||(ls.v[1]&&a[mid][0][0]&&rs.s[0]);//右上-左下 
}

void getpack(Node &p,int l, int r, int rt, int L, int R) {
	if(l >= L && r <= R) {
		p = tree[rt];
		return;
	}
	int mid = (l + r) >> 1;
	if(R <= mid) getpack(p, lson, L, R);
	else if(L > mid) getpack(p, rson, L, R);
	else {
		Node tmp1,tmp2;
		getpack(tmp1, lson, L, mid);
		getpack(tmp2, rson, mid + 1,R);
		pack(p, tmp1, tmp2, mid);
	}
}

void getAns() {
	if (c1 > c2) swap(c1, c2), swap(r1, r2);
	Node pa, pb, pc;
	getpack(pa, 1, n, 1, 1, c1);
	getpack(pb, 1, n, 1, c1, c2);
	getpack(pc, 1, n, 1, c2, n);
	if(r1==r2) {
		if(r1==0) {
			if(pb.s[0]||(pa.x[1]&&pb.v[1])||(pc.x[0]&&pb.v[0])||(pa.x[1]&&pb.s[1]&&pc.x[0])) puts("Y");
			else puts("N");
		} else {
			if(pb.s[1]||(pa.x[1]&&pb.v[0])||(pc.x[0]&&pb.v[1])||(pa.x[1]&&pb.s[0]&&pc.x[0])) puts("Y");
			else puts("N");
		}
	} else {
		if(r1==0) {
			if(pb.v[0]||(pa.x[1]&&pb.s[1])||(pc.x[0]&&pb.s[0])) puts("Y");
			else puts("N");
			} else {
			if(pb.v[1]||(pa.x[1]&&pb.s[0])||(pc.x[0]&&pb.s[1])) puts("Y");
			else puts("N");
		}
	}
}

void update(int l, int r, int rt, int p) {
	if (l == r) {
		tree[rt].x[0] = tree[rt].x[1] = tree[rt].v[1] = tree[rt].v[0] = a[p][0][1];
		tree[rt].s[0] = tree[rt].s[1] = 1;
		return;
	}
	int mid = l + r >> 1;
	if (p <= mid) update(lson, p);
	else update(rson, p);
	pack(tree[rt], tree[lch], tree[rch], mid);
}

void change(int c) {
	if (r1 > r2) swap(r1, r2), swap(c1, c2);
	int direction = 10000;
	for (int i = 0; i < 3; i++)
		if (c1 + dir[i][0] == c2 && r1 + dir[i][1] == r2)
			 direction = i;
	if (!direction) a[c2][r2][0] = c, update(1, n, 1, c2);
	else if (direction == 1) a[c1][0][1] = c, update(1, n, 1, c1);
	else a[c1][r1][0] = c, update(1, n, 1, c1);
}

int main() {
	freopen("1018.in", "r", stdin);
	scanf("%d", &n);
	build(1, n, 1);
	char op[10];
	while (~scanf("%s", op) && op[0] != 'E') {
		scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
		r1--, r2--;
		if (op[0] == 'O') change(1);
		else if (op[0] == 'C') change(0);
		else getAns();
	}

	return 0;
}