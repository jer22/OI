#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <map>

using namespace std;
const int maxn = 500000+10;

int n,m,dir;
deque<int> dqi,lft,rgt;
int Lp,Rp;
int num[maxn];

void init() {
	dqi.clear();
	lft.clear();
	rgt.clear();
	dir = 1;
}

void input() {
	scanf("%d",&n);
	for (int i = 1; i <= n; i++)
		scanf("%d",&num[i]);
	scanf("%d%d", &Lp, &Rp);
   	for (int i = 1; i < Lp; i++)
	   	lft.push_back(num[i]);
	for (int i = Lp; i <= Rp; i++)
		dqi.push_back(num[i]);
	for (int i = Rp + 1; i <= n; i++)
		rgt.push_back(num[i]);
	scanf("%d", &m);
}

void Reverse() {
	dir = 1 - dir;
}

void Insert() {
	char op[20];
	int x;
	scanf("%s %d", op, &x);
	if ((op[0] == 'R' && dir) || (op[0] =='L' && !dir)) {
		dqi.push_back(x);
	} else {
		dqi.push_front(x);
	}
}

void Delete() {
	char op[20];
	scanf("%s", op);
	if ((op[0] == 'R' && dir) || (op[0] =='L' && !dir)) {
		dqi.pop_back();
	} else {
		dqi.pop_front();
	}
}

void MoveLeft() {
	char op[20];
	scanf("%s", op);
	 if (op[0] == 'L' && dir ){
		int x = lft.back();
		lft.pop_back();
		dqi.push_front(x);
	} else if (op[0] == 'R' && !dir ){
		int x = dqi.front();
		dqi.pop_front();
		rgt.push_front(x);
	} else if (op[0] == 'R' && dir){
		int x = dqi.back();
		dqi.pop_back();
		rgt.push_front(x);
	} else {
		int x = lft.back();
		lft.pop_back();
		dqi.push_back(x);
	}
}
void MoveRight() {
	char op[20];
	scanf("%s",op);
	if((op[0] == 'L' && dir)) {
		int x = dqi.front();
		dqi.pop_front();
		lft.push_back(x);
	} else if(op[0]=='R' && dir) {
		int x = rgt.front();
		rgt.pop_front();
		dqi.push_back(x);

	} else if (op[0]=='L' && !dir){
		int x = dqi.back();
		dqi.pop_back();
		lft.push_back(x);
	} else {
		int x = rgt.front();
		rgt.pop_front();
		dqi.push_front(x);
	}
}
void output() {
	bool flag = false;
	for(deque<int>::iterator it = lft.begin(); it != lft.end(); it++) {
		if(!flag) {
			printf("%d",*it);
			flag = true;
		} else {
			printf(" %d",*it);
		}
	}

	if(!dir) reverse(dqi.begin(),dqi.end());
	for(deque<int>::iterator it = dqi.begin(); it != dqi.end(); it++) {
		if(!flag) {
			printf("%d",*it);
			flag = true;
		} else {
			printf(" %d",*it);
		}
	}
	for(deque<int>::iterator it = rgt.begin(); it != rgt.end(); it++) {
		if(!flag) {
			printf("%d",*it);
			flag = true;
		} else {
			printf(" %d",*it);
		}
	}
	puts("");
}
void solve() {
	char cmd[20];
	while(m--) {
		scanf("%s", cmd);
		if(cmd[0] == 'R') Reverse();
		else if(cmd[0] == 'I') Insert();
		else if(cmd[0] == 'D') Delete();
		else if(cmd[0] == 'M' && cmd[4] == 'R') MoveRight();
		else MoveLeft();
	}
	output();
}
int main(){
	freopen("a.in", "r", stdin);
	int ncase;
	cin >> ncase;
	while(ncase--) {
		init();
		input();
		solve();
	}
	return 0;
}
