#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Card{
	int tim, num;
	int team, card;
	bool operator < (const Card & c) const {
		return tim < c.tim;
	}
};

string te[2];
vector<Card> cards;
int n;
int ye[2][110];
int main() {
	cin >> te[0] >> te[1];
	scanf("%d", &n);
	int tim, num;
	char c, card;
	for (int i = 0; i < n; i++) {
		cin >> tim >> c >> num >> card;
		Card ca;
		ca.tim = tim;
		ca.num = num;
		if (c == 'h') ca.team = 0;
		else ca.team = 1;
		if (card == 'r') ca.card = 1;
		else ca.card = 0;
		cards.push_back(ca);
	}
	int l = cards.size();
	for (int i = 0; i < l; i++) {
		if (cards[i].card && ye[cards[i].team][cards[i].num] < 2) {
			cout << te[cards[i].team] << ' ' << cards[i].num << ' ' << cards[i].tim << endl;
			ye[cards[i].team][cards[i].num] += 2;
		} else {
			if (ye[cards[i].team][cards[i].num] == 1) {
				cout << te[cards[i].team] << ' ' << cards[i].num << ' ' << cards[i].tim << endl; 
			}
			ye[cards[i].team][cards[i].num]++;
		}
	}



	return 0;
}
