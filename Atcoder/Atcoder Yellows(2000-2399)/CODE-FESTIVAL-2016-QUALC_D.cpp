/*
Solved with editorial
*/

#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)3e2+2;

int n, m;
string a[mxN];
int dp[mxN][mxN], cost[mxN][mxN];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m; int ans = 0;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int k = 1; k < m; k++){
        memset(dp,63,sizeof(dp)); memset(cost,0,sizeof(cost));
        for(int i = 0; i < n; i++){
            for(int j = 0; j+i < n; j++) cost[0][i]+=(a[j+i][k-1]==a[j][k]);
            for(int j = 0; j+i < n; j++) if(i) cost[i][0]+=(a[j+i][k]==a[j][k-1]);
        }
        for(int i = 1; i < n; i++)
            for(int j = 1; j < n; j++)
                cost[i][j] = cost[i-1][j-1]-(a[n-i][k-1]==a[n-j][k]);
        dp[0][0] = 0;
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= n; j++){
                if(i) dp[i][j] = min(dp[i][j], dp[i-1][j]+cost[i-1][j]); 
                if(j) dp[i][j] = min(dp[i][j], dp[i][j-1]+cost[i][j-1]);
            }
        }
        ans+=dp[n][n];
    }
    cout << ans;
}
