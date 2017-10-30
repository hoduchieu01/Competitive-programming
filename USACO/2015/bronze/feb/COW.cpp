/*  USACO 2015 Feb
    Bronze
    CENSOR
*/
#include<bits/stdc++.h>
using namespace std;
long long cnt,n;
long long C,CO;
string s;
signed main(){
    freopen("cow.in","r",stdin);
    freopen("cow.out","w",stdout);
    cin>>n;
    cin>>s;
    for(int i=0;i<n;i++){
        if(s[i]=='C') C++;
        if(s[i]=='O') CO+=C;
        if(s[i]=='W') cnt+=CO;
    }
    cout<<cnt<<endl;
    return 0;

}
