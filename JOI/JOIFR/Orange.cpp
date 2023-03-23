#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mxN = (int)2e4+10;
int n,m,k,a[mxN],dp[mxN];

int32_t main()
{
    cin >> n >> m >> k;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++){
        int mx = a[i], mn = a[i], tot=1; dp[i] = dp[i-1]+k;
        for(int j = i-1; j>=max(0ll,i-m); j--){
            dp[i] = min(dp[i], dp[j]+k+tot*(mx-mn));
            mx=max(mx, a[j]), mn = min(mn, a[j]); tot++;
        }
    }
    cout << dp[n] << endl;
}
