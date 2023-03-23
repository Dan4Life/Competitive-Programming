/*
Solved by myself
For any query {a,b}, it is always better to go to the rightmost hotel as much as possible, 
until we reach a hotel that is reachable by b
We can use binary lifting to compute the answers greedily
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
#define fi first
#define se second
const int maxn = (int)2e5+10;
const int LINF = (int)1e18;
const int MOD = (int)1e9+7;
int n, L, q;
int dp[maxn][20], a[maxn];
set<pair<int,int>> S;
int get_path(int a, int b){
    int x = a, ans = 0;
    for(int i = 19; i >= 0; i--){
        if(dp[x][i]==-1) continue;
        if(dp[x][i]>b) continue;
        ans+=(1<<i), x=dp[x][i];
    }
    return ans+(x!=b);
}

int32_t main(){
    cin >> n; memset(dp, -1, sizeof(dp));
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) S.insert({a[i],i});
    cin >> L >> q;
    for(int i = 1; i < n; i++)
        dp[i][0] = prev(S.lower_bound({a[i]+L+1,-1}))->se;
    for(int j = 0; j < 20; j++)
        for(int i = 1; i <= n; i++)
            if(dp[i][j-1]!=-1) dp[i][j] = dp[dp[i][j-1]][j-1];
    while(q--){
        int a, b; cin >> a >> b;
        if(a>b) swap(a,b);
        cout << get_path(a,b) << "\n";
    }
}
