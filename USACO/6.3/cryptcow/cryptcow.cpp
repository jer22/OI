/*
ID:shijiey1
LANG:C++
PROG:cryptcow
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

#define HASH_SIZE 99991

using namespace std;

const string dest = "Begin the Escape execution at the Break of Dawn";

bool vis[HASH_SIZE];

inline int getHash(const string &text) {
	unsigned long h=0,g;
	for (int i = 0; i < text.length(); i++) {
		h = (h << 4) + text[i];
		g = h & 0xf0000000l;
		if (g) {
			h ^= g >> 24;
		}
		h &= ~g;
	}
	return h % HASH_SIZE;
}

inline bool badString(const string &text) {
	if ((text.length() - 47) % 3) return true;
	int i = 0;
	while (i < text.length()) {
		int j = i + 1;
		if (text[i] != 'C' && text[i] != 'O' && text[i] != 'W') {
			while (j < text.length() && text[j] != 'C' && text[j] != 'O' && text[j] != 'W') j++;
			if (dest.find(text.substr(i, j - i)) == string::npos)
				return true;
		}
		i = j;
	}
	return false;
}

inline string trans(const string &text, int c, int o, int w) {
	char str[80];
	int len = 0;
	for (int i = 0; i < c; i++)
		str[len++] = text[i];
	for (int i = o + 1; i < w; i++)
		str[len++] = text[i];
	for (int i = c + 1; i < o; i++)
		str[len++] = text[i];
	for (int i = w + 1; i < text.length(); i++)
		str[len++] = text[i];
	str[len++] = '\0';
	return string(str);
}

inline bool dfs(string text) {
	if (text == dest) return true;
	int hash = getHash(text);
	if (vis[hash]) return false;
	vis[hash] = 1;
	if (badString(text)) return false;
	for (int o = 1; o < text.length() - 1; o++) {
		if (text[o] != 'O') continue;
		for (int c = 0; c < o; c++) {
			if (text[c] != 'C') continue;
			for (int w = text.length() - 1; w > o; w--) {
				if (text[w] != 'W') continue;
				if (dfs(trans(text, c, o, w))) return true;
			}
		}
	}
	return false;
}

int main() {
	freopen("cryptcow.in", "r", stdin);
	freopen("cryptcow.out", "w", stdout);
	string src;
	getline(cin, src);
	if (dfs(src)) {
		cout << 1 << ' ' << count(src.begin(), src.end(), 'C') << endl;
	} else cout << "0 0" << endl;


	return 0;
}
