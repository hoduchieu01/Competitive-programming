#include<bits/stdc++.h>
using namespace std;
int A[110000];
vector<int>x[110000];
const int N=100000;
int n;
void add(int k1,int k2){
	for (;k1<=n;k1+=k1&(-k1)) A[k1]+=k2;
}
int find(int k1){
	int ans=0;
	for (;k1;k1-=k1&(-k1)) ans+=A[k1]; return ans;
}
int calc(int l,int r){
	if (l>r) return calc(l,n)+calc(0,r);
	return find(r)-find(l);
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;i++){
		add(i,1); int k1; scanf("%d",&k1);
		x[k1].push_back(i);
	}
	int pre=0; long long ans=0;
	for (int i=1;i<=N;i++){
		if (x[i].size()==0) continue;
		int where=lower_bound(x[i].begin(),x[i].end(),pre)-x[i].begin();
		if (where==x[i].size()) where=0;
		for (int j=0;j<x[i].size();j++){
			ans+=calc(pre,x[i][where]);
			add(x[i][where],-1);
			pre=x[i][where];
			where=(where+1)%(int)(x[i].size());
		}
	}
	cout<<ans<<endl;
	return 0;
}
#include<bits/stdc++.h>
#define N 100005
using namespace std;
#define MAGIC 100000
int n;
set < int > ss[N];
set < int > :: iterator it;
//fenwick_tree
    int data[N];

    void upd(int x,int v){
        for(;x <= n ; x+=x&(-x))    data[x] += v;
    }

    int get(int x){
        int ret = 0;
        for(;x > 0 ; x-=x&(-x))     ret += data[x];
        return ret;
    }

    int cal(int start,int finish){
        if(start <= finish) return get(finish) - get(start - 1);
        return get(n) - get(start - 1) + get(finish);
    }
//


int main(){
//    freopen("test.inp","r",stdin);
    scanf("%d",&n);
    for(int i = 1 ; i <= n ; i++){
        int x;
        scanf("%d",&x);
        upd(i , 1);
        ss[x].insert(i);
    }
    int cur = 1;
    long long ans = 0;
    for(int val = 1 ; val <= MAGIC ; val++){
        while(!ss[val].empty()){
            it = ss[val].lower_bound(cur);
            if(it == ss[val].end()) it = ss[val].begin();
            ans += cal(cur , (*it));
            upd((*it) , -1);
            cur = (*it);
            ss[val].erase((*it));
        }
    }
    cout<<ans;
}