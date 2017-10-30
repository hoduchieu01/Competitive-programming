#include<stdio.h>
char a[10][10];
int main()
 {
   for( int n=0;n<7;n++ ) 
   gets( a[n] );
   int ans = 0;
   for( int n=0; n<7; n++ ) 
   for( int m=0; m<7; m++ )
    {
   if( m+2 <  7 && a[n][m] == 'o' && a[n][m+1] == 'o' && a[n][m+2] == '.' ) ++ans;
   if( n+2 <  7 && a[n][m] == 'o' && a[n+1][m] == 'o' && a[n+2][m] == '.' ) ++ans;
   if( n-2 >= 0 && a[n][m] == 'o' && a[n-1][m] == 'o' && a[n-2][m] == '.' ) ++ans;
   if( m-2 >= 0 && a[n][m] == 'o' && a[n][m-1] == 'o' && a[n][m-2] == '.' ) ++ans;
   } 
        
   printf( "%d\n", ans );

   return 0;
}
