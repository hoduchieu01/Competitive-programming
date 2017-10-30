#include<bits/stdc++.h>
using namespace std;
long long n, m, a[300][300],r,c,i,j,k;
int sumlr( int left, int right, int x) {
	int sum = 0;
	for( int i=left;i<right;i++) sum += a[i][x];
	return sum;
}
int main()
{
	freopen("nered.inp","r",stdin);
	freopen("nered.out","w",stdout);
	cin>>n>>m;
	for(int i=0;i<m;i++){
		cin>>r>>c;
		a[r-1][c-1] = 1;
	}
	int minn=n*n;
	for(i=0;i<n;++i)
	for(j=i+1;j<=n;++j) {
		if(m%(j-i)&&m/(j-i)>n)continue;
		int tmp=0;
		for(k=0;k<m/(j-i);k++) tmp=tmp+sumlr(i,j,k );
		for(k=m/(j-i);k<=n;k++) {
		if(minn>m-tmp) minn=m-tmp;
		tmp =tmp-sumlr(i,j,k-m/(j-i));
		tmp =tmp+sumlr(i,j,k);
		}
	}
	cout<<minn<<endl;
}
