/*input
3 2
3 2 1
*/
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
long long n,k,a[10111],bit[10111],save[10111];

void up(long long w,long long d){
	for(;w<10011;w+=w&(-w)) bit[w]=(bit[w]+d)%mod;
}
long long get(long long w){
	long long res=0;
	for(;w;w-=w&(-w)) res=(res+bit[w])%mod;
	return res;
}
signed main(){	
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		 cin>>a[i];
		 save[i]=1;
	}
	for(int i=2;i<=k;i++){
		for(int j=n;j>=1;j--){
			up(a[i],save[i]);
			save[j] = get(a[j]-1);
		}
	memset(bit,0,sizeof bit);
	}
	long long res=0;
	for(int i=1;i<=n;i++) res+=(res+save[i])%mod;
		cout<<res<<endl;
}