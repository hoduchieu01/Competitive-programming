#include<bits/stdc++.h>
using namespace std;
int a[10101], b[10101];
int F[1010][1010];

int dp(int i, int j) {
  if (i <= 0) return 0;
  if (j <= 0) return 0;
  int& res = F[i][j];
  if (res != -1) return res;
  if (a[i] == b[j]) return res = dp(i - 2, j - 2) + 1;
  return res = max(dp(i - 1, j), dp(i, j - 1));
}
signed main() {
  ios_base::sync_with_stdio(false);
  memset(F, -1, sizeof(F));
  int m, n;
  cin>>m>>n;
	for (int i = 1; i <= m; ++i)
		cin>>a[i];
	for (int i = 1; i <= n; ++i)
		cin>>b[i];
	cout<<dp(m, n);
}
