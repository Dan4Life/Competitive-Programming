/*
Solved with help (external help)
Solution: https://pitsbuffersolution.com/compro/atcoder/arc088e.php
Alternate Solution(Impl is a bit weird tho): https://ykmaku.hatenablog.com/entry/2018/10/21/170709
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int maxn = (int)2e5+10;
string s; int cnt;
vector<int> S[27];
vector<pair<int,int>> V;
int fenwick[maxn];

void update(int x, int v){
    for(; x<maxn; x+=(x&-x))
        fenwick[x]+=v;
}

int sum(int x){
    int ans = 0;
    for(;x>0;x-=(x&-x)) ans+=fenwick[x];
    return ans;
}

int32_t main(){
    cin >> s; int n = (int)s.size(), ans = 0;
    for(int i = 0; i < n; i++) S[s[i]-'a'].pb(i);

    for(int i = 0; i < 26; i++) 
        cnt+=(int)S[i].size()%2;
    if(cnt>1){cout<<-1;return 0;}

    for(int i = 0; i < 26; i++){
        int m = (int)S[i].size();
        for(int j = 0; j < m/2; j++)
            V.pb({S[i][m-1-j],S[i][j]});
        if(m%2) V.pb({S[i][m/2],S[i][m/2]});
    }
    sort(V.begin(), V.end());
    for(auto u : V){
        ans+=sum(u.second)/((u.first==u.second)+1);
        update(u.first+1,1);
        if(u.first!=u.second) update(u.second+1,1);
    }
    cout << ans;
}
