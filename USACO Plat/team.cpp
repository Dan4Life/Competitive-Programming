#include <bits/stdc++.h>
using namespace std;

#define int long long
int n, m, K, a[1001], b[1001], dp[1001][1001][11];
const int MOD = 1e9+9;

int32_t main()
{
    ifstream cin("team.in");
    ofstream cout("team.out");
    cin >> n >> m >> K;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];
    sort(a, a+n), sort(b, b+m);
    reverse(a, a+n), reverse(b, b+m);
    for(int i = 0; i <= n; i++)
        for(int j = 0; j <= m; j++)
            dp[i][j][0]=1;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = 1; k <= K; k++){
                dp[i][j][k]+=dp[i-1][j][k]+dp[i][j-1][k]-dp[i-1][j-1][k]+MOD;
                if(a[i-1]>b[j-1]) dp[i][j][k]+=dp[i-1][j-1][k-1];
                dp[i][j][k]%=MOD;
            }
        }
    }
    cout << dp[n][m][K];
}
