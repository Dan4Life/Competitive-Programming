#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
int n, a[55000], l[55000], r[55000];
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("cardgame.in");
    ofstream cout("cardgame.out");
    cin >> n; set<int> bessie; int ans = 0;
    for(int i = 1; i <= 2*n; i++) bessie.insert(i);
    for(int i = 1; i <= n; i++) cin >> a[i], bessie.erase(a[i]);
    set<int> bessie2(bessie);
    int tot = 0;
    for(int i = 1; i <= n; i++){
        auto itr = bessie.lower_bound(a[i]);
        if(itr!=bessie.end()) tot++, bessie.erase(itr);
        l[i]=tot;
    }
    bessie2.swap(bessie); tot = 0;
    for(int i = n; i >= 1; i--){
        auto itr = bessie.lower_bound(a[i]);
        if(itr!=bessie.begin()) tot++, bessie.erase(prev(itr));
        r[i]=tot;
    }
    for(int i = 0; i <= n; i++) ans = max(ans, l[i]+r[i+1]);
    cout << ans;
}
