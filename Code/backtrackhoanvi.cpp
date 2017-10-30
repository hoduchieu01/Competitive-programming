#include <stdio.h>

int n;
bool used[123];
int a[123];

void show(){
    int i;
    for (i=1; i<=n; i++)
    printf("%d ", a[i]);
    printf("\n");
}

void back(int pos){
    int i;
    if (pos==n+1) { show(); return ; }
    for (i=1; i<=n; i++)
    if (not used[i]){
        a[pos]=i;
        used[i]=true;
        back(pos+1);
        used[i]=false;
    }
}

main(){
    scanf("%d", &n);
    back(1);
}
