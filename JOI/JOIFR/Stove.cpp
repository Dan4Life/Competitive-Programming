#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define all(a) a.begin(),a.end()
const int mxN = (int)1e5+10;
int a[mxN];
vector<int> v;
int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(i)v.pb(a[i]-a[i-1]-1);
    }
    if(n==1){cout<<1;return 0;}
    sort(all(v)); reverse(all(v));
    cout << a[n-1]-a[0]+1-accumulate(v.begin(),v.begin()+k-1,0);
}
