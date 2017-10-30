#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
int n, m, cnt=0;
vector<int> a[1000006]; 
int Visited[1000006], Low[1000006], Parent[1000006]; 
vector<pair<int, int> > Bridge; 
bool minimize(int &a, int b) { if (a>b) a=b; else return false; return true; }
void visit(int u){
    Low[u]=Visited[u]=++cnt;
    for (int i=0,v; v=a[u][i]; i++)
    if (v!=Parent[u]){
        if (Visited[v]) minimize(Low[u], Visited[v]);
        else {
            Parent[v]=u; visit(v); minimize(Low[u], Low[v]);
            if (Low[v]>=Visited[v]) Bridge.push_back(ii(u,v));
        }
    }
}

main(){
    ios :: sync_with_stdio(false);
    cin >> n >> m;
    f1(i,m) {
        int p, q;
        cin >> p >> q;
        a[p].push_back(q);
        a[q].push_back(p);
    }
    for(int i=1;i<=n;i++) a[i].push_back(0);
    for(int i=1;i<=n;i++) if (!Visited[i]) visit(i);
    cout << Bridge.size() << " critical links" << endl;
    for(int i=0;i<Bridge.size();i++) cout << Bridge[i].first << " " << Bridge[i].second << endl;
    cin.ignore(2);
}