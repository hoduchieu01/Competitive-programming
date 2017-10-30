#include<stdio.h>
#include<iostream>
using namespace std;

const long long INF = 1e18;
long long f[1005][1005];

int main()
{
    long long p[]={2,3,5,7,11,13,17,19,23,29};
    long long i,j,k,n,c,d;
    cin>>n;
    f[1][0] = 1LL; for(i=2;i<=1000;i++) f[i][0] = INF;

    for(i=1;i<=n;i++)
    {
        for(j=1;j<=10;j++)
        {
            f[i][j] = f[i][j-1]; c=1;
            for(k=1;k+1<=i;k++)
            {
                c*=p[j-1];
                if(c>=INF) break;
                if(i%(k+1)==0 && f[i/(k+1)][j-1]<INF && INF/c>=f[i/(k+1)][j-1]){
                    d=f[i/(k+1)][j-1]*c;
                    f[i][j]=min(f[i][j],d);
                }
            }
            //cout << i << " " << j << " " << f[i][j] << "\n";
        }
    }
    cout<<f[n][10];
}