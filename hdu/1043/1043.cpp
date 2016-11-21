#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>

#define p(i, j) (((i) * 3) + (j))

using namespace std;

struct Node{
	char map[10];
	char pos;
	int stat;
	int h;
	int step;
	Node() {}
	Node(int a, long long b) : pos(a), stat(b) {}
	bool operator < (const Node &n) const {
		if (step + h != n.step + n.h) return step + h > n.step + n.h;
		return step < n.step;
	}
}s;

bool vis[363005];
int pre[363005];
char step[363005];
int fac[]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
char dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
char op[4] = {'d', 'u', 'r', 'l'};

int cantor(char s[]) {
	int sum = 0;
	for (int i = 0; i < 9; i++) {
		int num = 0;
		for (int j = i + 1; j < 9; j++)
		if (s[j] < s[i]) num++;
		sum += (num * fac[9 - i - 1]);
	}
	return sum + 1;
}

bool check(char s[]){
	int sum = 0;
	for (int i = 0; i < 9; i++)
		for (int j = i + 1; j < 9; j++)
			if (s[j] && s[i] && s[i] > s[j])
				sum++;
	return !(sum & 1);
}

int get_h(char s[]){
	int ans = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (s[p(i, j)])
				ans += abs(i - (s[p(i, j)] - 1) / 3) + abs(j - (s[p(i, j)] - 1) % 3);
	return ans;
}

Node nex;
bool bfs() {
	vis[s.stat] = 1;
	priority_queue<Node> q;
	q.push(s);
	int cnt = 0;
	while (!q.empty()) {
		Node cur = q.top();
		q.pop();
		cnt++;
		if (cnt > 200000) return false;
		char x = cur.pos / 3;
		char y = cur.pos % 3;
		for (int i = 0; i < 4; i++) {
			char nx = x + dir[i][0];
			char ny = y + dir[i][1];
			if (nx < 0 || nx > 2 || ny < 0 || ny > 2) continue;
			nex = cur;
			swap(nex.map[cur.pos], nex.map[p(nx, ny)]);
			nex.pos = p(nx, ny);
			nex.stat = cantor(nex.map);
			nex.h = get_h(nex.map);
			nex.step++;

			if (!vis[nex.stat]) {
				pre[nex.stat] = cur.stat;
				step[nex.stat] = op[i];
				vis[nex.stat] = 1;
				if (!nex.h) return true;
				q.push(nex);
			}
		}
	}
	return true;
}

char t[10];
vector<char> ans;
int main() {
	freopen("1043.in", "r", stdin);
	for (int i = 0; i < 9; i++)
		t[i] = (i + 1) % 9;
	char c;
	while (cin >> c) {
		memset(vis, 0, sizeof(vis));
		if (c == 'x') {
			c = '0';
			s.pos = 0;
		}

		s.map[0] = c - '0';
		for (int i = 1; i <= 8; i++) {
			cin >> c;
			if (c == 'x') {
				c = '0';
				s.pos = i;
			}
			s.map[i] = c - '0';
		}
		s.stat = cantor(s.map);
		s.step = 0;
		s.h = get_h(s.map);
		if (!check(s.map)) printf("unsolvable\n");
		else {
			if (!get_h(s.map)) printf("\n");
			else {
				if (!bfs()) {
					printf("unsolvable\n");
					continue;
				}
				int des = cantor(t);
				ans.clear();
				while (des != s.stat) {
					ans.push_back(step[des]);
					des = pre[des];
				}
				for (int i = ans.size() - 1; i >= 0; i--) {
					printf("%c", ans[i]);
				}
				printf("\n");
			}
		}
	}


	return 0;
}
