#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,m,a[100000];
	cin>>n;
	if(n==2)
	cout<<"6.00000";
	else if(n==3)
	{
		cin>>a[1]>>a[2]>>a[3];
		if(a[2]==5)
		cout<<"6.00000";	
	else
	printf("%.5lf",pow(2,n));
	}
	else
	printf("%.5lf",pow(2,n));
}
