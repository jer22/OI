#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

int main() {
	srand(time(0));
	freopen("apec.in", "w", stdout);
	cout << 1 << ' ' << 40 << endl;
	for (int i = 0; i < 40; i++) {
		for (int j = 0; j < 40; j++) {
			int cc=rand()%4;
			if (cc!=0) cc=1;
			cout << cc << ' ';
		}
		cout << endl;
	}
}
