int main()
{
	ios_base::sync_with_stdio(false);cout.tie(0);cin.tie(0);

	int n, i, j, k;
	string s;
	cin >> n >> s;

	for (i = 0; s[i] == '<'; ++i);
	for (j = n-1; j >= 0 && s[j] == '>'; --j);

	cout << i + n - j - 1 << endl;

	return 0;
}