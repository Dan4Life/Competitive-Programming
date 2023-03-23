#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fi first
#define se second
unordered_map<int, vector<int>> v[2];

int num(int a, int b, int c, int t){
    int itr = lower_bound(v[t][a].begin(), v[t][a].end(), b)-v[t][a].begin();
    int itr2 = upper_bound(v[t][a].begin(), v[t][a].end(), c)-v[t][a].begin()-1;
    if(itr2<0 or itr==(int)v[t][a].size()) return 0;
    return max(0, itr2-itr+1);
}

int chk(int x, int y){
    auto itr = lower_bound(v[0][x].begin(), v[0][x].end(), y)-v[0][x].begin();
    if(itr==(int)v[0][x].size()) return 0;
    return v[0][x][itr]==y;
}

int main()
{
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int x, y; cin >> x >> y;
        v[0][x].pb(y), v[1][y].pb(x);
    }
    for(int _ = 0; _ < 2; _++)
        for(auto &u : v[_])
            sort(u.se.begin(),u.se.end());
    int q; cin >> q;
    while(q--){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int ans = 0;
        ans-=chk(x1,y1)+chk(x1,y2)+chk(x2,y1)+chk(x2,y2);
        ans+=num(x1,y1,y2,0)+num(x2,y1,y2,0);
        ans+=num(y1,x1,x2,1)+num(y2,x1,x2,1);
        cout << ans << "\n";
    }
}
