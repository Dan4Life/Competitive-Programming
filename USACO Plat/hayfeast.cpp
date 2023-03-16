#include <bits/stdc++.h>
using namespace std;
int t, a, b, dp[5000010][2];
int recur(int cur, bool drink) // drink = true if already taken a drink before so as not to repeat it
{
    if(cur>t) return -100000;
    if(dp[cur][drink]!=-1) return dp[cur][drink];
    if(cur+a>t and cur+b>t and drink) return dp[cur][drink]=cur;
    if(drink) return dp[cur][drink]=max(recur(cur+a, drink), recur(cur+b, drink));
    return dp[cur][drink]=max({recur(cur+a, drink), recur(cur+b, drink), recur(cur/2, true)});
}

int32_t main()
{
    ifstream cin("feast.in"); ofstream cout("feast.out");
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> t >> a >> b; memset(dp, -1, sizeof(dp));
    cout << recur(0,0);
}
