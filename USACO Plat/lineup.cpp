#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
const int mxN = (int)1e5+10;
int n, k, a[mxN];
unordered_map<int,int> ind;
vector<int> v[mxN], w;

int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("lineup.in");
    ofstream cout("lineup.out");
    cin >> n >> k;
    for(int i = 0; i < n; i++) cin >> a[i], w.pb(a[i]);
    sort(all(w)); w.erase(unique(all(w)),w.end());
    int xd = 0; for(auto u : w) ind[u]=xd++;
    for(int i = 0; i < n; i++) a[i]=ind[a[i]],v[a[i]].pb(i);
    for(int i = 0; i < xd; i++) sort(all(v[i]));
    int l = 1, r = n;
    while(l<r){
        int mid = (l+r+1)>>1; bool ok = 0;
        int pj[xd+1]; fill(pj,pj+xd,0);
        int vv[n], occ[n]; fill(vv,vv+n,n+1); fill(occ,occ+n,0);
        for(int i = 0; i < n and !ok; i++){
            if(pj[a[i]]+mid-1>=sz(v[a[i]])) continue;
            int j = v[a[i]][pj[a[i]]+mid-1]; pj[a[i]]++;
            vv[i]=min(vv[i],j);
        }
        set<int> S; S.clear();
        for(int i = 0, j = 0; i < n and !ok; i++){
            while(j<n and sz(S)<=k+1){
                S.insert(a[j]), occ[a[j]]++, j++;
            }
            if(vv[i]<j) ok=1;
            if(occ[a[i]]==1) S.erase(a[i]);
            occ[a[i]]--;
        }
        if(ok)l=mid;
        else r=mid-1;
    }
    cout << l;
}
