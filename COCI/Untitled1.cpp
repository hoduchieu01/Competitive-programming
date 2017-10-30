#include<bits/stdc++.h>
using namespace std;
int dr[] = {0,0,-1,1};
int dc[] = {-1,1,0,0};
char grid[150][150];
int R,C,ct;
void floodfill2(int r, int c, char c1, char c2) {
    if (r < 0 || r >= R || c < 0 || c >= C) return ;
    if (grid[r][c] != c1) return ;
    grid[r][c] = c2;
    for (int d = 0; d < 4; d++)
        floodfill2(r + dr[d], c + dc[d], c1, c2);
}
void floodfill(int r, int c, char c1, char c2) {
    if (r < 0 || r >= R || c < 0 || c >= C || grid[r][c]=='.') return ;
    if(grid[r][c]=='X') floodfill2(r,c,'X','*'),ct++;
    if (grid[r][c] != c1) return ;
    grid[r][c] = c2;
    for (int d = 0; d < 4; d++)
        floodfill(r + dr[d], c + dc[d], c1, c2);
}
int main(){
    int cas=0;
    while(scanf("%d %d",&C,&R),(R||C)){
        getchar();
        for(int i=0;i<R;i++) gets(grid[i]);
        vector <int> v;
        for(int i=0;i<R;i++){
            for(int j=0;j<C;j++){
                if(grid[i][j]!='.'){
                    ct=0;
                    floodfill(i,j,'*','.');
                    if(ct) v.push_back(ct);
                }
            }
        }
        if(!v.size()){
            printf("Throw %d\n0\n\n",++cas);
            continue;
        }
        sort(v.begin(),v.end());
        printf("Throw %d\n",++cas);
        for(int k=0;k<v.size()-1;k++) printf("%d ",v[k]);
        printf("%d\n\n",v[v.size()-1]);
    }
    return 0;
}
