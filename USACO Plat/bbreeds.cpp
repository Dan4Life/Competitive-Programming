#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
int n, a[1010], dp[1010][1010][2];
string s; int ans;

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("bbreeds.in");
    ofstream cout("bbreeds.out");
    cin >> s; n = sz(s); dp[0][0][0]=1;
    for(int i = 1; i <= n; i++) a[i] = (s[i-1]=='('?1:-1);
    for(int i = 1, pre=a[1]; i <= n; pre+=a[++i]){
        for(int j = 0; j <= n; j++){
            int other = pre-j; if(other<0) continue;
            dp[i][j][0]+=dp[i-1][j][0]+dp[i-1][j][1];
            if(j-a[i]>=0) dp[i][j][1]+=dp[i-1][j-a[i]][0]+dp[i-1][j-a[i]][1];
            if(i==n and !j and !other) ans+=dp[i][j][0]+dp[i][j][1];
            dp[i][j][0]%=2012, dp[i][j][1]%=2012,ans%=2012;
        }
    }
    cout << ans;
}
