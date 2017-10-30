/*input
3 3 1 2
*/
#include<bits/stdc++.h>
using namespace std;
long long n,x[1000000],bit[100000],ans;
void up(int w){for(;w<=60066;w+=w&(-w)) bit[w]++;}
void get(int w){for(;w;w-=w&(-w)) ans+=bit[w];}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i];
	for(int i=n;i>=1;i--){
		up(x[i]);
		get(x[i]-1);
	}
	cout<<ans<<endl;
}