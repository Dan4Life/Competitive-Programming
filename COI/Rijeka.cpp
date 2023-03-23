#include <bits/stdc++.h>
using namespace std;
#define int long long
#define fi first
#define se second
#define pb push_back

const int maxn = (int)3e5+10;

int n, m;
int32_t main()
{
    cin >> n >> m;
    set<pair<int,int>> S;
    for(int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        if(x>y) S.insert({y,x});
    }
    while(!S.empty()){
        int cur = S.begin()->fi;
        int x = S.begin()->fi, y = S.begin()->se;
        while(!S.empty()){
            auto itr = S.begin();
            if(S.begin()->fi <= y) y=max(y,S.begin()->se), S.erase(S.begin());
            else break;
        }
        m+=2*(y-x);
    }
    cout << m;
}
