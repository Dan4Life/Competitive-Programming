/*
Solved with editorial
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = (int)1e9+7;
int n, m, k;

int poww(int a, int b){
    if(b==0) return 1;
    int x = poww(a, b/2);
    x*=x, x%=MOD;
    if(b&1) x*=a, x%=MOD;
    return x;
}

int comb(int a, int b){
    if(a<b) return 0;
    int ans = 1;
    for(int i = 2; i <= a; i++) ans*=i, ans%=MOD;
    for(int i = 2; i <= b; i++) ans*=poww(i,MOD-2), ans%=MOD;
    for(int i = 2; i <= a-b; i++) ans*=poww(i,MOD-2), ans%=MOD;
    return ans;
}


int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m >> k; if(n>m+k){cout<<0; return 0;}
    cout << (comb(n+m,n)-comb(n+m,m+k+1)+MOD)%MOD;
}
