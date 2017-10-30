#include<bits/stdc++.h>
using namespace std;

int a1,b1,a2,b2,t1,t2,ng[10],ck, k, l;

int main()
{
//freopen("vauvau.inp","r",stdin);
//freopen("vauvau.out","w",stdout);
    cin>>a1>>b1>>a2>>b2;
    cin>>ng[1]>>ng[2]>>ng[3];
    t1=a1+b1;
    t2=a2+b2;
    for(int i=1;i<=3;i++)
    for(int j=1;j<=999;j++)
    {
        ck=0;
        if(j==ng[i])
        {
            k=j%t1;
            l=j%t2;
            if(k==0 && l==0)ck=0;
            if(k<=a1 && l<=a2 && k!=0 && l!=0)ck=2;
            if(k<=a1 && l>a2 && k!=0 || k>a1 && l<=a2 && l!=0)
				ck=1;
            if(k==0 && l<=a2 && l!=0 || k!=0 && k<=a1 && l==0)
				ck=1;
			if(ck==0)printf("none\n");
			if(ck==1)printf("one\n");
			if(ck==2)printf("both\n");
        }
        if(j==ng[i]) 
		break;
    }
}
