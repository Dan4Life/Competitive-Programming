#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back

const int mxN = (int)21;
int n, m;
vector<pair<int,int>> b[mxN];
int dp[1<<mxN], a[mxN][mxN];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("dec.in");
    ofstream cout("dec.out");
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x,y,z; cin >> x >> y >> z;
        b[x].pb({y,z});
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];
    fill(dp,dp+(1<<mxN),-1000000000); dp[0]=0;
    for(int mask = 0; mask < (1<<n); mask++){
        int num = __builtin_popcount(mask);
        for(int i = 0; i < n; i++){
            if(!((mask>>i)&1)) continue;
            int nmask = mask^(1<<i);
            dp[mask] = max(dp[mask], dp[nmask]+a[i][num-1]);
        }
        int x = dp[mask];
        if(dp[mask]>=0) for(auto [A,B]:b[num]) dp[mask]+=(A<=x)*B;
    }
    cout << dp[(1<<n)-1];
}
