#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pb push_back
#define sz(a) (int)a.size()
const int mxN = (int)2e3+10;
const int MOD = (int)1e9+7;
int n, a, b, dp[mxN][mxN];

int32_t main(){
    cin >> n >> a >> b; dp[1][1]=1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(i==a or i==b) dp[i][j]+=dp[i-1][j]+dp[i-1][j-1];
            else dp[i][j]+=dp[i-1][j+1]*j+dp[i-1][j-1]*(j-(i>a)-(i>b));
            dp[i][j]%=MOD;
        }
    }
    cout << dp[n][1];
}
