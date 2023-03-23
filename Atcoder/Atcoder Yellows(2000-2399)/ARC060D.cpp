/*
Solved with help (editorial)
Notice that if b>sqrt(n), there are at most 2 digits
there is exactly one digit if b = n+1(when s=n), other cases is 2 digits(cornercase)
else we can just bruteforce b in O(sqrt(n))
let the digits be x and y, then n = xb+y
we also know that               s = x+y (or else, no answer)
With some simple math, we get b = (n-s)/x + 1
We can bruteforce x knowing that x can be at most sqrt(n) (because b>=sqrt(n)) 
and make ans as small as possible if f(b,n)=s after substituting current x in equation
Make sure to handle b=1 case
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int LINF = 1e18;
int n, s;

int f(int b, int n){
  	if(b<=1) return LINF;
    int x = 0; while(n) x+=n%b, n/=b; return x;
}

int32_t main(){
    cin >> n >> s; 
  	if(n==s){cout<<n+1; return 0;}
  	int ans = LINF;
    for(int i = 2; i*i<= n; i++){
        if(f(i,n)==s){ cout << i << "\n"; return 0; }
    }
    
    for(int p = 1; p*p <= n; p++){
        if((n-s)%p) continue;
      	int b = (n-s)/p+1;
        if(f(b,n)==s) ans = min(ans, b);
    }
    if(ans==LINF) ans=-1;
    cout << ans;
}