// cho mot cay co goc tim to tien chung gan nhat cua 2 nut A,B
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

const int N = 100005;
int n, Root, l[N], P[20][N];

int level(int u) {
    if (u==Root) return l[u]=1;
    if (l[u]==0) l[u]=level(P[0][u])+1;
    return l[u];
}

int lca(int x, int y) {
    for (int k=19; k>=0; k--)
        if (l[P[k][x]]>=l[y])
        x=P[k][x];
    for (int k=19; k>=0; k--)
        if (l[P[k][y]]>=l[x])
        y=P[k][y];
    for (int k=19; k>=0; k--)
        if (P[k][x]!=P[k][y])
        { x=P[k][x]; y=P[k][y]; }
    while (x!=y)
        { x=P[0][x]; y=P[0][y]; }
    return x;
}

void solve() {
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        int p; scanf("%d", &p);
        while (p-->0) {
            int q; scanf("%d", &q);
            P[0][q] = i;
        }
    }
    for (int i=1; i<=n; i++)
        if (P[0][i]==0) Root=i;
    for (int i=1; i<=n; i++)
        level(i); // done l

    for (int k=1; k<=19; k++)
    for (int i=1; i<=n; i++)
    P[k][i] = P[k-1][P[k-1][i]];

    int m; scanf("%d", &m);
    while (m-->0) {
        int x, y;
        scanf("%d%d", &x, &y);
        printf("%d\n", lca(x, y));
    }
}

main() {
    int t; scanf("%d", &t);
    for (int i=1; i<=t; i++) {
        printf("Case %d:\n", i);
        solve();
        for (int j=1; j<=n; j++)
        { l[j]=0; P[0][j]=0; }
    }
}
