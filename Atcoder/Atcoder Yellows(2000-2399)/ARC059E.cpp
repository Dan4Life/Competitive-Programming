/*
Solved by myself
Naive DP runs in O(N*max_B*C*C) which is too slow (N=max_B=C=400)
We can improve to O(N*max_B*C) by prefix sums speedup because the states form a range and the formula can be found by simple math
Memory limit is still exceeded, so we use rollover dp trick, where we 'rollover' the indices as we only use dp[i-1][x][x]s from dp[i][x][x]
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = (int)401;
const int MOD = (int)1e9+7;
int n, c, a[maxn], b[maxn], pref[maxn][maxn], dp[2][maxn][maxn];

int32_t main(){
    cin >> n >> c;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    dp[0][0][0] = 1; int i = 0;

    for(int j = 0; j <= 400; j++) pref[j][0] = dp[i][b[i]][0];
        for(int j = 0; j <= 400; j++)
            for(int k = 1; k <= c; k++)
                pref[j][k] = (j*pref[j][k-1]+dp[i][b[i]][k])%MOD; // formula for prefix sums

    for(int i = 1; i <= n; i++){
        for(int j = a[i]; j <= b[i]; j++)
            for(int k = 0; k <= c; k++)
                dp[i%2][j][k] = (dp[i%2][j-1][k]+pref[j][k])%MOD;

        for(int j = 0; j <= 400; j++)
            for(int k = 0; k <= c; k++)
                pref[j][k] = 0;              // remember to re-initialize!

        for(int j = 0; j <= 400; j++) pref[j][0] = dp[i%2][b[i]][0];
        for(int j = 0; j <= 400; j++)
            for(int k = 1; k <= c; k++)
                pref[j][k] = (j*pref[j][k-1]+dp[i%2][b[i]][k])%MOD; // i%2 is rollover trick

        for(int j = 0; j <= 400; j++)
            for(int k = 0; k <= c; k++)
                dp[(i+1)%2][j][k]=0;  // remember to re-initialize!
    }
    cout << dp[n%2][b[n]][c];
}
