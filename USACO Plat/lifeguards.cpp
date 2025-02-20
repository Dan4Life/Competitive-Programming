#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define pb push_back
//#define int long long
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using ll = long long;
using vi = vector<int>;
using ar2 = array<int,2>;
using ar3 = array<int,3>;

const int mxN = (int)1e5+2;
const int INF = (int)1e9+2;
const ll LINF = (ll)2e18;
const int mxLg = 16;

int n, m;
int dp[mxN][103];
ar2 a[mxN];

int32_t main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("lifeguards.in");
    ofstream cout("lifeguards.out");
    cin >> n >> m; if(n==m){cout<<0;return 0;}
    for(int i = 1; i <= n; i++)
        cin >> a[i][0] >> a[i][1];
    sort(a+1,a+n+1,[&](ar2 x, ar2 y){ 
        if(x[1]==y[1]) return x[0]<y[0];
        return x[1]<y[1]; 
    });
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= 100; j++)
            dp[i][j]=-INF;
    for(int i = 1; i <= n; i++){
        for(int j = 0; j <= min(m,i-1); j++){
            for(int k = 1; k <= min(j+1,m); k++){
                dp[i][j]=max(dp[i][j], dp[i-k][j-k+1]-
                    (a[i][0]>=a[i-k][1]?a[i][0]:a[i-k][1])+a[i][1]);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= n; i++){
        int j = m-n+i;
        if(j>=0 and j<=m)
            ans=max(ans, dp[i][j]);
    }
    cout << ans << "\n";
}
