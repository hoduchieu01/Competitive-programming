/*input
3
1 2
3 4
2 3
*/
#include<bits/stdc++.h>
using namespace std;
bool sortbysec(const pair<int,int> &a,const pair<int,int> &b)
{
    return (a.second < b.second);
}
bool sortbyfirst(const pair<int,int> &a,const pair<int,int> &b){
    return (a.first < b.first);
}
vector< pair <int,int> > vect;
int x[100000],y[100000];
int n;
signed main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cin>> x[i] >> y[i];
        vect.push_back( make_pair(x[i],y[i]) );
    }
    sort(vect.begin(),vect.end(),sortbysec);
    for (int i = 0 ; i <n ; i++)  cout << vect[i].first << " "<< vect[i].second << endl;
    return 0;
}
