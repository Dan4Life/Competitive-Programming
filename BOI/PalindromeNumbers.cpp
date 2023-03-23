#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define int ll // delete if causing problems
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define mod(a) (a+MOD)%MOD
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
 
const int maxn = 3e5+10; // change when needed!
const int MOD = 1e9+7; // same!
const int INF = 2e9;
const ll LINF = 4e18;
int n, m, x, y, l, r, k, q, t;
map<int, int> M, N;
string a, b,s;
int dp[20][12][12][2][2];
 
bool chk(string a){
    int n = (int)a.size();
    for(int i = 0; i < n-1; i++){
        if(i<n-2 and a[i]==a[i+2]) return false;
        if(a[i]==a[i+1]) return false;
    }
    return true;
}
 
int recur(int pos=0, int last=10, int last2=11, bool sm=0, bool le=1)
{
    int n = (int)s.size();
    if(pos==n) return dp[pos][last][last2][sm][le]=1;
    if(dp[pos][last][last2][sm][le]!=-1) return dp[pos][last][last2][sm][le];
    int limit = 9, ans = 0;
    if(!sm) limit = s[pos]-'0';
    for(int d = 0; d <= limit; d++)
    {
        if(d==last or d==last2) continue;
        bool SM = sm, LE = le;
        if(!SM and d<limit) SM=true;
        if(LE and d) LE=false;
        ans+=recur(pos+1, LE?10:d, LE?10:last, SM, LE);
    }
    return dp[pos][last][last2][sm][le]=ans;
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> a >> b; memset(dp, -1, sizeof(dp)); s = b;
    int ans = recur(); memset(dp, -1, sizeof(dp)); s = a;
    cout << ans-recur()+chk(a);
}
