#include <bits/stdc++.h>
using namespace std;
int w, h, n, x, y, dp[610][610];
int32_t main()
{
    cin >> w >> h >> n;
    for(int i = 1; i <= w; i++)
        for(int j = 1; j <= h; j++)
            dp[i][j]=i*j;
    for(int i = 0; i < n; i++){
        cin >> x >> y; dp[x][y]=0;
    }
    for(int i = 1; i <= w; i++){
        for(int j = 1; j <= h; j++){
            for(int k = 1; k <= i; k++)
                dp[i][j] = min(dp[i][j], dp[k][j]+dp[i-k][j]);
            for(int k = 1; k <= j; k++)
                dp[i][j] = min(dp[i][j], dp[i][k]+dp[i][j-k]);
        }
    }
    cout << dp[w][h];
}
