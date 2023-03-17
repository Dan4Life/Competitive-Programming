#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
const int mxN = 510;
int n, a[mxN], freq[mxN], t[mxN];

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("fcount.in");
    ofstream cout("fcount.out");
    cin >> n; vector<int> v;
    for(int i = 1; i <= n+1; i++) 
        cin >> a[i], freq[a[i]]++, t[a[i]]++;
    for(int i = 1; i <= n+1; i++){
        if(a[i]>=n or a[i]<0){ v.pb(i); continue; }
        for(int j = 0; j < n; j++) freq[j]=t[j];
        bool ok = 1; int sum = 0;  freq[a[i]]--;
        for(int j = n-1; j; j--) sum+=j*freq[j];
        if(sum%2) continue;
        for(int j = n-1; j; j--){
            if(!freq[j]) continue; 
            int sum = 0, k; freq[j]--;
            for(k = j; k; sum+=freq[k--]) 
                if(sum+freq[k]>=j) break;
            if(!k) ok=0;
            int rem = sum+freq[k]-j;
            for(int x = k; x <= j; x++){
                if(!x) continue; int add = freq[x];
                if(x==k) add = freq[k]-rem;
                freq[x-1]+=add, freq[x]-=add;
            }
        }
        if(ok) v.pb(i);
    }
    cout << sz(v) << "\n";
    for(auto u : v) cout << u << "\n";
}
