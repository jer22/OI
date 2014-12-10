/*
ID:shijiey1
PROG:lamps
LANG:C++
*/

/*
首先可以发现，灯i和灯i+6是一样的，所以对于所有的n，都可以看作是n=6的情况，输出时反复输出即可（n<6也可以）。
一开始给出最后灯的开关情况，把编号模6存起来。如果一个位置既是开的又是关的，就可以直接输出IMPOSSIBLE。
每个灯按两次等于不按，所以其实只有按与不按两种状态，所以当c＞４就可以一直-2直到c<=4。
所以每个灯按与不安一共2^4=16种情况。
用一个6位的二进制数表示灯的状态，从右向左数第1位表示第1盏灯，依次类推。所以4种操作分别是：
操作1：异或63
操作2：异或21
操作3：异或42
操作4：异或9
用一个二进制数isOn表示最后是开着的灯，如果灯"开着"则对应位是1，其余是0。
同样用二进制数isOff表示最后是关着的灯，灯"关着"则对应位是0，其余是1。
当前状态用state表示。
若(state & isOn) == isOn && (state | isOff) == isOff则满足要求。
还有如果细心可以发现，对于操作1，2，3，12=3，13=2，23=1。所以其实16种状态可以简化为8种：
0（不按），1，2，3，4，14，24，34。
然后枚举即可。
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <set>
#include <iostream>

using namespace std;

int n, c;
int start[8];
int on[8];
int off[8];
int isOn;
int isOff = 63;;
set<string> ans;

bool ok(int state) {
	return (state & isOn) == isOn && (state | isOff) == isOff;
}

void add(int state) {
	string s = "";
	for (int i = 0; i < min(n, 6); i++) {
		char c = ((state & 1) + '0');
		s = s + c;
		state >>= 1;
	}
	ans.insert(s);
}

void addState(int state) { if (ok(state)) add(state); }

void print() {
	set<string> :: iterator it;
	for (it = ans.begin(); it != ans.end(); it++) {
		for (int i = 0; i < n; i++) {
			printf("%c", (*it)[i % 6]);
		}
		printf("\n");
	}
}

void solve() {
	int bit = 63;
	for (int i = 0; i < 6; i++) {
		if (on[i] == 1) {
			isOn = isOn | (1 << i);
		} else if (!off[i]) {
			
			isOff = isOff ^ (1 << i);
		}
	}
	addState(bit);
	if (c) {
		addState(bit ^ 63);
		addState(bit ^ 21);
		addState(bit ^ 42);
		addState(bit ^ 9);	
		addState((bit ^ 63) ^ 9);
		addState((bit ^ 21) ^ 9);
		addState((bit ^ 42) ^ 9);
	}
	if (!ans.size()) {
		printf("IMPOSSIBLE\n");
		return;
	}
	print();
}

int main() {
	freopen("lamps.in", "r", stdin);
	freopen("lamps.out", "w", stdout);
	scanf("%d %d", &n, &c);
	int t;
	while (~scanf("%d", &t)) {
		if (t == -1) break;
		on[(t - 1) % 6] = 1;
	}
	for (int i = 0; i < 6; i++) off[i] = 1;
	while (~scanf("%d", &t)) {
		if (t == -1) break;
		if (on[(t - 1) % 6] == 1) {
			printf("IMPOSSIBLE\n");
			return 0;
		}
		off[(t - 1) % 6] = 0;
	}
	while (c > 4) c -= 2;
	solve();

	return 0;
}
