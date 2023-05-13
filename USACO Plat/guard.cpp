#include <bits/stdc++.h>
using namespace std;
#define int long long
tuple<int,int,int> a[21];
int n, H, dp[1<<21], ans = -1;
int32_t main()
{
    ifstream cin("guard.in");
    ofstream cout("guard.out");
    cin >> n >> H; dp[0] = (int)2e18;
    for(int i = 0; i < n; i++)
        cin >> get<0>(a[i]) >> get<1>(a[i]) >> get<2>(a[i]);
    for(int mask = 1; mask < (1<<n); mask++)
    {
        int h = 0; dp[mask] = -1;
        for(int i = 0; i < n; i++)
        {
            if(mask&(1<<i))
            {
                h+=get<0>(a[i]);
                if(dp[mask^(1<<i)]>=get<1>(a[i]))
                    dp[mask] = max(dp[mask], min(dp[mask^(1<<i)]-get<1>(a[i]), get<2>(a[i])));
            }
        }
        if(h>=H) ans = max(ans, dp[mask]);
    }
    if(ans==-1) cout << "Mark is too tall";
    else cout << ans;
}
