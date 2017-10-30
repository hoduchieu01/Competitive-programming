/*input
6 2
1 3 2
4 6 3
1
3 4
day gom n phan tu gia tri ban dau =0, m dong (u,v,k) tang gia tri tu u-> v len k don vi q truy van gia tri lon nhat thuoc doan u,v
*/
#include<bits/stdc++.h>
using namespace std;
const int MAX_ARR = 5e4+5, INF = 2e9;
int Node[4*MAX_ARR];
int lazy[4*MAX_ARR];
int n, m;
void True_val(int id, int Left, int Right){
    if (lazy[id]==0) return;
    Node[id] += lazy[id];
    if (Left!=Right){
        lazy[id*2] += lazy[id];
        lazy[id*2+1] += lazy[id];
        }
    lazy[id]=0;
}

void update(int id, int Left, int Right, int a, int b, int val){
    True_val(id, Left, Right);
    if(Left>b||Right<a||Left>Right) return;
    if(a<= Left && Right<= b){
        Node[id] += val;
        if(Left!=Right) {
            lazy[id*2] += val;
            lazy[id*2+1] += val;
            return;
        }
        return;
    }
    int Mid = (Left + Right)/2;
    update(id*2, Left, Mid, a, b, val);
    update(id*2+1, Mid+1, Right, a, b, val);
    Node[id]=max(Node[id*2], Node[id*2+1]);
}

int get(int id, int Left, int Right, int a, int b){
    True_val(id, Left, Right);
    if(Left>b||Right<a||Left>Right) return -INF;
    if(a<= Left&&Left<= Right&&Right<= b) return Node[id];
    int Mid = (Left+Right)/2;
    int Tmp1 = get(id*2, Left, Mid, a, b);
    int Tmp2 = get(id*2+1, Mid+1, Right, a, b);
    return max(Tmp1, Tmp2);
}
int main()
{
int q,a,b,val;
cin>>n>>m;
while(m--)
{
cin>>a>>b>>val;
update(1,1,n,a,b,val);
}
cin>>q;
while(q--)
{
cin>>a>>b;
cout<<get(1,1,n,a,b)<<endl;
}
}
