/*input
3 3
1 2 50
2 3 60
1 3 600
*/
#include<bits/stdc++.h>
using namespace std; 
const int oo = 1000111000;
int a[300][300];
int n,m;
void minimize(int &a, int b){ if (a>b) a=b; }
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    a[i][j] = oo;
    for(int i=1;i<=n;i++) a[i][i] = 0;  
    for(int i=1;i<=m;i++){
    	int p,q,w;
    	cin>>p>>q>>w;
        a[p][q] = a[q][p] = w;
    }
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    minimize(a[i][j], a[i][k] + a[k][j]);
	cout<<a[1][n];    
}
