#include<bits/stdc++.h>
using namespace std;
const long long N= 1000000;
long long cnt,m,ans,cr;
int c( char x){return x-'a';}
struct trie{
	int child[30],stop[30];
	bool have[26];
} a[N];
void update(string s,int po,int pre)
{
	int x= c(s[po]);
	if(a[pre].have[x]==1){
		if(po==s.size()-1)
		{
			a[pre].stop[x]++;
			return ;
		}
		update(s,po+1,a[pre].child[x]);
	}
	else{
		a[pre].stop[x]=0;
		a[pre].have[x]=1;
		a[pre].child[x]=++cnt;
		if(po==s.size()-1){
			a[pre].stop[x]++;
			return;
		}
		update(s,po+1,a[pre].child[x]);
	}
}
void solve(int u){
		for(int i=0;i<26;i++){
			if(a[u].have[i]==1){
				cr+=a[u].stop[i];
				ans=max(ans,cr);
				solve(a[u].child[i]);
				cr-=a[u].stop[i];
		}
	}
}
signed main(){
	cin >> m;
	string si;
	while(m--)
	{
		cin>>si;
		update(si,0,0);
	}
	solve(0);
	cout<<ans;
}