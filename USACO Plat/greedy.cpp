#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define int long long
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) a.begin(),a.end()
const int LINF = (int)1e18;
string s;

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    ifstream cin("greedy.in");
    ofstream cout("greedy.out");
    int n; cin >> n; int v[n+5];
    for(int i = 0; i < n; i++) cin >> v[i];
    set<int> S;
    for(int i = 0; i < n; i++) S.insert(i);
    for(int i = 0; i < n; i++){
        auto itr = S.upper_bound(n-v[i]-1);
        if(itr!=S.begin()) itr--, S.erase(itr);
        if(!S.count(0)) {cout<<n-i-1;return 0;}
    }
    cout << 0;
}
