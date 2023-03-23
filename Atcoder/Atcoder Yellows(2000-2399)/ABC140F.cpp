/*
Solved with help (external help, this problem is easy smh)
Basically assign greedily, make each slime produce spawn with health as big as possible
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define int ll // delete if causing problems
#define pb push_back
#define fi first
#define se second

const int maxn = (int)5e5+10; 

int n;
int a[maxn];
vector<int> v,w;
multiset<int> S;

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 0; i < (1<<n); i++) 
        cin >> a[i], S.insert(a[i]);
    v.pb(*prev(S.end())); S.erase(prev(S.end()));
    while(!S.empty()){
        vector<int> w; w.clear();
        for(auto u : v){
            auto itr = S.lower_bound(u);
            if(itr==S.begin()) {cout<<"No";return 0;} itr--;
            w.pb(*itr), S.erase(itr);
        }
        for(auto u : w) v.pb(u);
    }
    cout << "Yes";
}
