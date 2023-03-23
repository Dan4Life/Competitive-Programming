/*
Solved with editorial
Gosh, I'm bad at math
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MOD = 998244353;

int R,G,B,K;
int fact[3000010];

int poww(int a, int b){
    if(b==0) return 1;
    int x = poww(a,b/2); x*=x,x%=MOD;
    if(b&1) x*=a, x%=MOD; return x;
}

int comb(int a, int b){
    if(a<b) return 0;
    int ans = (fact[a]*poww(fact[b],MOD-2))%MOD;
    return (ans*poww(fact[a-b],MOD-2))%MOD;
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> R >> G >> B >> K; fact[0] = 1;
    for(int i = 1; i <= R+G+B; i++) 
        fact[i]=(fact[i-1]*i)%MOD;
    int ans = fact[R+B]; 
    ans*=poww(fact[K],MOD-2), ans%=MOD;
    ans*=poww(fact[R-K],MOD-2), ans%=MOD;
    ans*=poww(fact[B],MOD-2), ans%=MOD;
    ans*=comb(G+B,B+K), ans%=MOD;
    cout << ans;
}
