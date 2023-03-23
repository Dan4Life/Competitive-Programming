#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
 
int n, m, a[21], b[21];
pair<int,int> dp[1<<21];
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> m; dp[0] = {0,0};
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];
    for(int i = 0; i < (1<<m); i++){
        for(int j = 0; j < m; j++){
            if(i&(1<<j)) continue;
            int n_i = i|(1<<j), tot = dp[i].se+b[j];
            if(tot<a[dp[i].fi]) dp[n_i] = max(dp[n_i], {dp[i].fi, tot});
            else if(tot==a[dp[i].fi]) dp[n_i] = max(dp[n_i], {dp[i].fi+1, 0});
        }
        if(dp[i].fi==n){ cout<<"YES"; return 0;}
    }
    cout << "NO";
}
