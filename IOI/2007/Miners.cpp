#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
//#define int ll
#define pb push_back
#define pf push_front
#define PB pop_back
#define PF pop_front
#define mp make_pair
#define fir first
#define sec second
#define all(a) a.begin(), a.end()
#define r_all(a) a.rbegin(), a.rend()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0);
 
const int maxn = 300010;
const int MOD = 1e9+7; //1e9+9;
const int MOD2 = 998244353; //998244853;
const int INF = 2e9;
const ll LINF = 4e18;
map<int, int> M, N;
string s, ss;
int k, a, b, n, m;
 
int dp[4][4][4][4][4];
int cnt(int a, int b, int c){
    if(a+b+c==0)return 0;
    if(a==0 and b!=0 and c!=0){
        if(b!=c)return 2;
        return 1;
    }
    if(b==0 and a!=0 and c!=0){
        if(a!=c)return 2;
        return 1;
    }
    if(c==0 and a!=0 and b!=0){
        if(a!=b)return 2;
        return 1;
    }
    if(a+b==0)return (c!=0);
    if(a+c==0)return (b!=0);
    if(b+c==0)return (a!=0);
    if(a==b and b==c)return 1;
    if(a==b and b!=c)return 2;
    if(a==c and b!=c)return 2;
    if(b==c and a!=b)return 2;
    if(a!=b and b!=c)return 3;
    return 0;
}
 
void solve()
{
    cin >> n >> s;
    for(auto &u : s){
        if(u=='B')u='1';
        else if(u=='F')u='2';
        else u='3';
    }
    for(int i = n-1; i>=0; i--)
        for(int j = 0; j < 4; j++)
            for(int k = 0; k < 4; k++)
                for(int l = 0; l < 4; l++)
                    for(int m = 0; m < 4; m++)
                        a = dp[(i+1)%2][k][s[i]-'0'][l][m]+cnt(j,k,s[i]-'0'),
                            b = dp[(i+1)%2][j][k][m][s[i]-'0']+cnt(l,m,s[i]-'0'),
                                dp[i%2][j][k][l][m] = max(a, b);
    cout << dp[0][0][0][0][0];
}
 
int32_t main()
{
    fast_io
    int t = 1; //cin >> t;
    while(t--) solve();
}
