#include<bits/stdc++.h>
using namespace std;
long long a,b,c,d,ans;
signed main(){
    ios_base::sync_with_stdio(false);
    freopen("paint.in","r",stdin);
    freopen("paint.out","w",stdout);
    cin>>a>>b>>c>>d;
    if(a<=c&&d<=b) ans=b-a;
    if(a<=c&&c<=b&&b<=d) ans=b-a+d-b;
    if(b<=c) ans=d-c+b-a;
    if(c<=a&&a<=d&&d<=b) ans=a-c+b-a;
    if(c<=a&&b<=d) ans=d-c;
    if(c<=a&&d<=a) ans= d-c+b-a;
    cout<<ans<<endl;
    return 0;


}
