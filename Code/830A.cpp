#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool possible(const vector<int> &person, const vector<int> &key, int p, int t) {
	int j = 0;
	for (auto x : person) {
		while (j < key.size() && 1LL*abs(x - key[j]) + abs(key[j] - p) > t) j++;
		if (j == key.size()) return false;
		j++;
	}
	return true;
}

int main() {
	int n, k, p; cin >> n >> k >> p;
	vector<int> person(n), key(k);
	for (auto &i : person) cin >> i;
	for (auto &i : key) cin >> i;
	sort(person.begin(), person.end());
	sort(key.begin(), key.end());
	
	int S = 0, T = (int) 2e9;
	while (S < T) {
		int md = (1LL*S + T) / 2;
		if (possible(person, key, p, md)) T = md;
		else S = md + 1;
	}
	cout << S << endl;
	return 0;
}