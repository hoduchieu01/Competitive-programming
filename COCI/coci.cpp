#include <stdio.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
using namespace std;
#define f1 first
#define f2 second
typedef long long ll;
typedef pair <int, int> ii;
vector <string> list;

bool is_up(char c){
	return 'A' <= c && c <= 'Z';
}
int cal(string sentence){

	int cnt = 0;

	string word;

	istringstream iss(sentence);

	while (iss >> word){

		if (!is_up(word[0])) continue;
		for (int i = 1; i <= word.size(); i++){
			if (i == word.size()){ cnt++; break; }
			if (word[i] < 'a' || word[i] > 'z') break;
		}
	}
	return cnt;
}
int main(){
	int n;
	cin >> n;

	string line;

	getline(cin, line);
	getline(cin, line);

	int pr = 0, pos;
	while ((pos = line.find_first_of(".!?", pr)) != std::string::npos){
		if (pos > pr) list.push_back(line.substr(pr, pos-pr));
		pr = pos + 1;
	}
	if (pr < line.size())
		list.push_back(line.substr(pr, std::string::npos));

	for (int i = 0; i < n; i++) cout << cal(list[i]) << "\n";

	return 0;

	return 0;
}
