/*
Solved with help (editorial)
*/

#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
const int maxn = (int)2e5+10;

int n, ans;
int a[maxn], b[maxn];

int32_t main(){
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    for(int i = 1; i <= n; i++) cin >> b[i];
    for(int i = 0; i < 30; i++){
        vector<int> v, w; v.clear(); w.clear();
        for(int j = 1; j <= n; j++) v.pb(a[j]%(1ll<<(i+1)));
        for(int j = 1; j <= n; j++) w.pb(b[j]%(1ll<<(i+1)));
        sort(v.begin(),v.end()), sort(w.begin(),w.end());
        for(auto u : v){
            int sz = (int)w.size(), num = 0;
            int pos1 = lower_bound(w.begin(), w.end(), (1ll<<i)-u)-w.begin();
            int pos2 = lower_bound(w.begin(), w.end(), 2*(1ll<<i)-u)-w.begin()-1;
            int pos3 = lower_bound(w.begin(), w.end(), 3*(1ll<<i)-u)-w.begin();
            if(pos1!=sz and pos2!=sz) num+=pos2-pos1+1;
            if(pos3!=sz) num+=sz-pos3;
            ans^=num%2*(1ll<<i);
        }
    }
    cout << ans;
}