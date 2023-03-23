#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(a) a.begin(),a.end()
#define mp make_pair
#define fi first
#define se second
#define sz(a) (int)a.size()
using ll = long long;
const int maxn = (int)1e5+10;
const ll INF = (ll)2e18;
ll n, K, a[maxn], s[maxn];
ll dp[2][maxn];
int p[205][maxn];
vector<int> v;
 
void recur(int i, int k){ if(k) v.pb(i), recur(p[k][i],k-1); }
 
double slope(int i, int j, int k){
    if(s[j]==s[i]) return INF;
    return (double)((dp[k][j]-s[n]*s[j])-(dp[k][i]-s[n]*s[i]))/(s[j]-s[i]);
}
 
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n >> K; int ind = 0;
    for(int i = 0; i < n; i++) cin >> a[i], s[i+1]=s[i]+a[i];
    for(int k = 1; k <= K+1; k++){
        deque<int> DQ; DQ.clear(); DQ.push_back(0); ind = k%2;
        for(int i = 1; i <= n; i++){
            while(sz(DQ)>1 and slope(DQ[0],DQ[1],!ind)>= -s[i]) DQ.pop_front();
 
            int j = DQ[0]; dp[ind][i]=dp[!ind][j]+(s[i]-s[j])*(s[n]-s[i]), p[k][i]=j;
 
            while(sz(DQ)>1 and slope(DQ[sz(DQ)-2], DQ.back(),!ind) <= slope(DQ.back(),i,!ind)) DQ.pop_back();
            DQ.push_back(i);
        }
        memcpy(dp[!ind],dp[ind],sizeof(dp[ind]));
    }
    cout << dp[ind][n] << "\n"; recur(n,K+1);
    sort(all(v)); v.pop_back(); for(auto u : v) cout << u << " ";
}
