#include<bits/stdc++.h>
using namespace std;
long long x,y,m,maxx=-9999999;
signed main(){

    ios_base::sync_with_stdio(false);
    freopen("pails.in","r",stdin);
    freopen("pails.out","w",stdout);
    cin>>x>>y>>m;
    int tmp=m/x+1;
    int tmp1=m/y+1;
    for(int i=0;i<=tmp;i++)
        for(int j=0;j<tmp1;j++)
            if(x*i+y*j<=m) maxx=max(x*i+y*j,maxx);
    cout<<maxx<<endl;
}
