#include <stdio.h>
#include <assert.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define long long long
#define f1(i,n) for (int i=1; i<=n; i++)
#define f0(i,n) for (int i=0; i<n; i++)

typedef vector<int> vi;
const int BASE=10000;

void fix(vi &a){
    a.push_back(0);
    f0(i,a.size()-1) {
        a[i+1]+=a[i]/BASE; a[i]%=BASE;
        if (a[i]<0) { a[i]+=BASE; a[i+1]--; }
    }
    while (a.size()>=2 && a.back()==0) a.pop_back();
}

void operator += (vi &a, const vi &b) {
    a.resize(max(a.size(), b.size()));
    f0(i,b.size()) a[i]+=b[i];
    fix(a);
}

vi operator * (const vi &a, const vi &b){
    vi c(a.size()+b.size());
    f0(i,a.size()) f0(j,b.size()) c[i+j]+=a[i]*b[j];
    return fix(c), c;
}

vi to_vi(int x) // x<BASE
    { return vi(1,x); }

void operator -= (vi &a, const vi &b)
    { f0(i,b.size()) a[i]-=b[i]; fix(a); }
void operator *= (vi &a, int x) // x<BASE
    { f0(i,a.size()) a[i]*=x; fix(a); }
vi operator + (vi a, const vi &b)
    { a+=b; return a; }
vi operator - (vi a, const vi &b)
    { a-=b; return a; }
vi operator * (vi a, int x) // x<BASE
    { a*=x; return a; }

bool operator < (const vi &a, const vi &b){
    if (a.size() != b.size()) return a.size()<b.size();
    for (int i=a.size()-1; i>=0; i--)
    if (a[i]!=b[i]) return a[i]<b[i];
    return false;
}

void divide(const vi &a, int x, vi &q, int &r) {
    q.clear(); r=0;
    for (int i=a.size()-1; i>=0; i--) {
        r=r*BASE+a[i];
        q.push_back(r/x); r%=x;
    }
    reverse(q.begin(), q.end());
    fix(q);
}

vi operator / (const vi &a, int x)
    { vi q; int r; divide(a, x, q, r); return q; }
int operator % (const vi &a, int x)
    { vi q; int r; divide(a, x, q, r); return r; }

istream& operator >> (istream& cin, vi &a){
    string s; cin >> s;
    a.clear(); a.resize(s.size()/4+1);
    f0(i,s.size()) {
        int x = (s.size()-1-i)/4; // <- log10(BASE)=4
        a[x]=a[x]*10+(s[i]-'0');
    }
    return fix(a), cin;
}

ostream& operator << (ostream& cout, const vi &a){
    printf("%d", a.back());
    for (int i=(int)a.size()-2; i>=0; i--)
    printf("%04d", a[i]);
    return cout;
}

void test_fib(int n){
    vi a=to_vi(1), b=to_vi(1);
    f1(i,n/2) {
        a+=b; b+=a;
        cout << "F[" << i*2+1 << "]=" << a << endl;
        cout << "F[" << i*2+2 << "]=" << b << endl;
    }
}

void test_fact(int n){
    vi P=to_vi(1);
    f1(i,n) {
        P*=i;
        cout << i << "!= " << P << endl;
    }
}

void test_divide(){
    vi a; int x;
    for (;;){
        cout << "Input a big integer and a small integer (<10000)" << endl;
        if (cin >> a >> x); else break;
        cout << "a=" << a << " x=" << x << endl;
        vi q=a/x; int r=a%x;
        cout << "a/x=" << q << "; a%x=" << r << endl;
        vi a0 = q*to_vi(x)+to_vi(r);
        assert(a0==a && !(a0<a) && !(a0>a));
    }
}

main(){
    cout << "Press Enter to run test_fib()" << endl;
    cin.ignore(1); test_fib(100);
    cout << "Press Enter to run test_fact()" << endl;
    cin.ignore(1); test_fact(100);
    cout << "Press Enter to run test_divide()" << endl;
    cin.ignore(1); test_divide();
}
