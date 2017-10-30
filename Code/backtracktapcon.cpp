#include <stdio.h>

int n;
bool a[100];

void show(){
    for (int i=1; i<=n; i++)
    if (a[i])
    printf("%d ", i);
    printf("\n");
}

void bt(int u){
    if (u==n+1) {
        show();
        return ;
    }
    a[u]=0;
    bt(u+1);
    a[u]=1;
    bt(u+1);
}

main(){
    scanf("%d", &n);
    bt(1);
}
