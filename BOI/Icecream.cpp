#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
#define int ll // delete if causing problems
#define ld long double
#define pb push_back
#define pf push_front
#define mp make_pair
#define fir first
#define sec second
#define all(a) a.begin(), a.end()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0);
 
const int maxn = 200010;
const int MOD = 1e9+7;
const int MOD2 = 998244353;
const int INF = 1e9;
const ll LINF = 1e18;
int n, m, a[maxn], b[maxn];
map<int, int> M, N;
string s, ss;
set<pair<int,int> > S;
 
struct hash_pair {
   template <class T1, class T2>
   size_t operator()(const pair<T1, T2>& p) const{
      auto hash1 = hash<T1>{}(p.first);
      auto hash2 = hash<T2>{}(p.second);
      return hash1 ^ hash2;
   }
};
 
void solve()
{
    cin >> n >> m;
    unordered_map<pair<int,int>, bool, hash_pair> M;
    while(m--)
    {
        int a, b;
        cin >> a >> b;
        M[{a,b}]=true;
        M[{b,a}]=true;
    }
 
    int cnt = 0;
    for(int i = 1; i <= n; i++)
        for(int j = i+1; j <= n; j++)
            if(!M.count({i,j}))
                for(int k = j+1; k <= n; k++)
                    if(!M.count({j,k}) and !M.count({i,k}))
                        cnt++;
    cout << cnt;
}
 
int32_t main()
{
    fast_io;
    int t=1; //cin >> t;
    while(t--) solve();
}
