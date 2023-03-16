#include <bits/stdc++.h>
using namespace std;
int n, a[310], dp[310][310];
int32_t main()
{
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < 310; i++)
        for(int j = i; j < 310; j++)
            dp[i][j]=1e9;
    for(int l = 0; l < n; l++) {
    	for(int i = 0; i < n-l; i++) {
    		int j = i+l;
    		dp[i][j] = 1+dp[i+1][j];
    		for(int x = i; x < j; x++)
                dp[i][j] = min(dp[i][j], dp[i][x]+dp[x+1][j]-(a[i]==a[j]));
    	}
    }
    cout << dp[0][n-1];
}
