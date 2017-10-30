/* USACO 2015 BRONZE FEB CENSOR */
#include<bits/stdc++.h>
using namespace std;
string s,t,v;
signed main(){
    freopen("censor.in","r",stdin);
    freopen("censor.out","w",stdout);
    cin>>s>>t;
    for(int i=0;i<s.size();i++){
        v+=s[i];
        if(v.size()>=t.size() && v.substr(v.size()-t.size())==t  )
            v.resize(v.size()-t.size());
    }
    cout<<v<<endl;
    return 0;
}
