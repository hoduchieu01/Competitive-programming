/*input
6
*/
#include<iostream>
using namespace std;
int ar[500500];
int sum =0;
int main()
{
   long long n;
   cin>>n;
   ar[0]=1;
   for(int j=1;j<n/2;j++)
      ar[j]=0;
   for(int i=1;i<=n;i++)
   {
      ar[0]=2*ar[0];
      for(int k=1;k<n/2;k++)
         ar[k]=2*ar[k] + ar[k-1]/10;
      for(int j=0;j<n/2;j++)
            ar[j]=ar[j]%10;
   }
   for(int i=0;i<n/2;i++)
   sum = sum + ar[i];
   cout<<sum;
}
