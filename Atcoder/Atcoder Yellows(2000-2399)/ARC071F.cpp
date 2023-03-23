/*
Solved with help (editorial)
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = (int)1e6+10;
const int MOD = (int)1e9+7;
int n, sum;
int dp[maxn];

int32_t main(){
    cin >> n; sum = 0; dp[1] = n, dp[2] = n*n; sum = n*n+n+1;
    for(int i = 3; i <= n; i++){
        dp[i] = sum+MOD-dp[i-2]+(n-1)*(n-1)+n-i+1;
        dp[i]%=MOD; sum+=dp[i], sum%=MOD;
    }
    cout << dp[n];
}