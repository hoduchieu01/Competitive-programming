/*
Với một dãy số, thực hiện các truy vấn sau
0 X Y: tăng phần tử thứ X lên Y đơn vị
1 X Y: tính tổng các phần tử từ phần tử thứ X đến phần tử thứ Y
*/
#include<bits/stdc++.h>
using namespace std;
struct indexed_tree {
   int n;
   int T[1000000];

   void clear(int N){ n=N; }
   void update(int pos, int value){
      for (int i=pos; i<=n; i+=i&-i)
      T[i]+=value;
   }
   int get(int pos){
      int r;
      for (int i=pos; i>=1; i-=i&-i)
      r+=T[i];
      return r;
   }
   int get(int ll, int rr){
      return get(rr)-get(ll-1);
   }
};

int n, m;
indexed_tree tr;

main(){
   char c; int i, x, y;

   scanf("%d%d", &n, &m);
   tr.clear(n);

   for (int i=1; i<=m; i++){
      scanf(" %c%d%d", &c, &x, &y);
      if (c=='u') tr.update(x, y);
      if (c=='g') printf("%d\n", tr.get(x, y));
   }
}
