/*
Solved by myself (Well, i fucked up the impl part and had to check other's codes cuz I was missing a stupid cornercase
My solution is just like editorial
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define int ll // delete if causing problems
#define pb push_back
#define pf push_front
#define mp make_pair
#define fi first
#define se second
#define mod(a) (a+MOD)%MOD
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()

const int maxn = (int)2e2+10; // change when needed!
const int MOD = (int)998244353; // same!
const int INF = (int)2e9;
const ll LINF = (ll)4e18;
int n, m, x, y, k, q, t;
map<int, int> M, N;
set<int> S, SS;
string s, ss;
int a[maxn], b[maxn];
bool dp[maxn];

bool isrange(int pos, int num, int ind){
    return ind>=pos and ind<pos+2*num;
}

bool chk(int pos, int num){
    int used[maxn]; fill(used,used+maxn,0);
    for(int i = 0; i < n; i++){
        if(a[i]==-1 and b[i]==-1) continue;
        if(a[i]!=-1 and b[i]!=-1){
            if(isrange(pos,num,a[i]) or isrange(pos,num,b[i])){
                if(b[i]-a[i]!=num) return false;
                if(used[b[i]] or used[a[i]]) return false;
                used[a[i]]=used[b[i]]=1;
            }
        }
        else if(a[i]!=-1){
            if(!isrange(pos,num,a[i])) continue;
            if(!isrange(pos,num,a[i]+num)) return false;
            if(used[a[i]] or used[a[i]+num]) return false;
            used[a[i]]=used[a[i]+num]=1;
        }
        else{
            if(!isrange(pos,num,b[i])) continue;
            if(!isrange(pos,num,b[i]-num)) return false;
            if(used[b[i]] or used[b[i]-num]) return false;
            used[b[i]]=used[b[i]-num]=1;
        }
    }
    return true;
}

void solve()
{
    cin >> n; bool ok = 1;
    for(int i = 0; i < n; i++)
        cin >> a[i] >> b[i];
    if(!ok){cout<<"No"; return; } dp[0] = 1;
    for(int i = 2; i <= 2*n; i+=2)
        for(int j = 1; j*2 <= i; j++)
            if(chk(i-j*2+1,j)) dp[i]|=dp[i-j*2];
    cout << (dp[2*n]?"Yes":"No");
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; //cin >> t;
    while(t--) solve();
}
