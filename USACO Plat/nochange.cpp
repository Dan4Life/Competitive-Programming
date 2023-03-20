#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define int long long
#define sz(a) (int)a.size()
const int mxN = (int)2e5+10;
int n, k, a[mxN], coin[mxN], pre[mxN], dp[1<<16];

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("nochange.in");
    ofstream cout("nochange.out");
    cin >> k >> n; int ans = -1;
    for(int i = 0; i < k; i++) cin >> coin[i];
    for(int i = 0; i < n; i++) cin >> a[i], pre[i+1]=pre[i]+a[i];
    for(int mask = 0; mask < (1<<k); mask++){
        int left = 0;
        for(int i = 0; i < k; i++){
            if(mask&(1<<i)){
                int nmask = mask ^ (1<<i), cost = coin[i];
                int l = dp[nmask], r = n;
                while(l<r){
                    int mid = (l+r+1)/2;
                    if(pre[mid]-pre[dp[nmask]] <= cost) l=mid;
                    else r=mid-1;
                }
                dp[mask] = max(dp[mask], l);
            }
            else left+=coin[i];
        }
        if(dp[mask]==n) ans = max(ans, left);
    }
    cout << ans;
}
