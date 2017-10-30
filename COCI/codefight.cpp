#include<bits/stdc++.h>
using namespace std;
int gcdEuclid(int a, int b) {
      if (a%b == 0) {
        return b;
      }
      return gcdEuclid( b,a % b);
    }
signed main(){
	cout<<gcdEuclid(6,16);	
}