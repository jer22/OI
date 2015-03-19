#include <algorithm>
#include <iostream>
#include <cstring>
#include <climits>
#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <map>
#include <set>

using namespace std;

const int MAXT = 1005;
const int MAXN = 105;

struct Person{
	int st;
	int cnt;
	int book[6];
	int tim[6];
	bool operator < (const Person &n) const {
		return st < n.st;
	}
};

int T, n;
Person arr[MAXN];

struct Ret{
	int person, book_idx;
	Ret() {}
	Ret(int a, int b) : person(a), book_idx(b) {}
};
vector<Ret> return_book[MAXT << 1];
bool vis[MAXT];
int main() {
	freopen("reading.in", "r", stdin);
	int ans = 0;
	cin >> T >> n;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i].st;
		cin >> arr[i].cnt;
		for (int j = 1; j <= arr[i].cnt; j++)
			cin >> arr[i].book[j] >> arr[i].tim[j];
	}
	sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++)
		return_book[arr[i].st].push_back(Ret(i, 0));
	for (int cur_tim = 0; cur_tim < T; cur_tim++) {
		// 如果现在有人还书
		if (return_book[cur_tim].size() != 0) {
			// 枚举要还的书
			for (int i = 0; i < return_book[cur_tim].size(); i++) {
				Ret event = return_book[cur_tim][i];
				Person person = arr[event.person];
				int book = person.book[event.book_idx]; // 书的编号
				vis[book] = 0; // 该书为空闲状态
				
				// 还书的人还有想看的书
				if (event.book_idx < arr[event.person].cnt) {
					book = person.book[event.book_idx + 1];
					if (!vis[book]) { // 该书空闲
						vis[book] = 1;
						return_book[cur_tim + person.tim[event.book_idx + 1]].push_back(Ret(event.person, book));
					}
				}
			}
		}

	}

	return 0;
}
