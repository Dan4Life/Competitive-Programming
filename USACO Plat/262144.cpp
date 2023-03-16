#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
//#define int long long
using ll = long long;
using pii = pair<int,int>;

const int maxn = (int)3e5+10;
const ll LINF = (ll)1e18;

int n, a[maxn];
int dp[70][maxn];
// dp[i][j] = index 'k' such that subarray j..k has max value of i
void solve(){
    ifstream cin("262144.in");
    ofstream cout("262144.out");
    cin >> n;
    for(int i = 1; i <= n; i++) 
        cin >> a[i], dp[a[i]][i]=i;
    int ans = *max_element(a+1,a+n+1);
    for(int v = 1; v < 70; v++){
        for(int i = 1; i <= n; i++){
            if(!dp[v-1][i]) continue;
            dp[v][i] = dp[v-1][dp[v-1][i]+1];
            if(dp[v][i]) ans = max(ans, v);
        }
    }
    cout << ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t=1; //cin >> t;
    while(t--) solve();
}
