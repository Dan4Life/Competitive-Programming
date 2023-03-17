#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define pb push_back
#define int long long
#define all(a) a.begin(),a.end()
#define sz(a) (int)a.size()
const int mxN = 18;
int n, k, a[mxN][mxN], b[mxN][mxN];
int32_t main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("partition.in");
    ofstream cout("partition.out");
    cin >> n >> k;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            cin >> a[i][j];
    int l = 0, r = 225000;
    while(l<r){
        int mid = (l+r)>>1; bool ok = 0;
        for(int mask = 0; mask < (1<<(n-1)) and !ok; mask++){
            int left = k-__builtin_popcount(mask);
            if(left<0) continue;
            vector<int> v; v.clear();v.pb(0);
            for(int i = 0; i < n-1; i++)
                if(mask&(1<<i)) v.pb(i+1);

            for(int i = 0; i <= n; i++)
                for(int j = 0; j <= n; j++)
                    b[i][j]=0;
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                    b[i][upper_bound(all(v),j)-begin(v)]+=a[i][j];
            bool bad = 0;
            for(int i = 0; i < n; i++)
                for(int j = 1; j <= sz(v); j++)
                    if(b[i][j]>mid) bad=1;
            if(bad) continue;
            int sum[n+3];
            for(int i = 0; i <= n; i++) sum[i]=0;
            for(int i = 0; i < n; i++){
                bool chk = 0;
                for(int j = 1; j <= sz(v); j++)
                    if(sum[j]+b[i][j]>mid) chk=1;
                if(chk) left--;
                for(int j = 1; j <= sz(v); j++){
                    if(chk)sum[j]=0;
                    sum[j]+=b[i][j];
                }
            }
            if(left>=0) ok=1;
        }
        if(ok)r=mid;
        else l=mid+1;
    }
    cout << l;
}
