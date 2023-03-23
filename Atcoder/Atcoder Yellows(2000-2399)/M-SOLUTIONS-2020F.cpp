/*
Solved with editorial (Well, i technically got the solution, but my implementation would have been cancer)
Btw its been quite a while since I solved a yellow wtf, almost 2 weeks...
*/

#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define int long long
#define pb push_back
#define all(a) a.begin(),a.end()
const int MOD = (int)1e9+7;
const int maxn = (int)2e5+10;

set<pair<int,int>> diag[maxn*2], diagr[maxn*2];
vector<int> xcord[5][maxn], ycord[5][maxn];
int ans = maxn*maxn*maxn, n;
vector<pair<int,int>> cord;
int X[maxn], Y[maxn];
char Z[maxn];

void calc(){
    sort(all(cord));
    for(auto u : cord){
        int D = u.fi+u.se;
        while(!diag[D].empty() and diag[D].begin()->fi < u.fi){
            diagr[D].erase({diag[D].begin()->se,diag[D].begin()->fi});
            diag[D].erase(diag[D].begin());
        }
        auto itr = diagr[D].lower_bound({u.se+1,-1});
        if(itr!=diagr[D].begin()) 
            ans = min(ans, (u.se-prev(itr)->fi)*10);
    }
}

void rotate(){
    for(int i = 0; i < maxn*2; i++) 
        diag[i].clear(), diagr[i].clear();
    cord.clear();
    for(int i = 0; i < n; i++){
        int x=X[i],y=Y[i]; char z=Z[i];
        if(z=='U') cord.pb({y,x});
        else if(z=='R'){
            diag[x+y].insert({y,x}),
            diagr[x+y].insert({x,y});
        }
        if(z=='U') z='L';
        else if(z=='R') z='U';
        else if(z=='D') z='R';
        else z='D';
        X[i]=maxn-y-9,Y[i]=x,Z[i]=z;
    }
}

int32_t main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++){
        int x, y; char z;
        cin >> X[i] >> Y[i] >> Z[i];
        x=X[i],y=Y[i],z=Z[i];
        int lol = 0;
        if(z=='R') lol=1;
        else if(z=='D') lol=2;
        else if(z=='L') lol=3;
        xcord[lol][x].pb(y);
        ycord[lol][y].pb(x);
    }
    for(int i = 0; i < maxn; i++){
        sort(all(xcord[2][i]));
        sort(all(ycord[3][i]));
        for(auto u : xcord[0][i]){
            int pos = lower_bound(all(xcord[2][i]),u)-xcord[2][i].begin();
            if(pos!=(int)xcord[2][i].size()) ans = min(ans, (xcord[2][i][pos]-u)*5);
        }
        for(auto u : ycord[1][i]){
            int pos = lower_bound(all(ycord[3][i]),u)-ycord[3][i].begin();
            if(pos!=(int)ycord[3][i].size()) ans = min(ans, (ycord[3][i][pos]-u)*5);
        }
    }
    for(int i = 0; i < 4; i++) rotate(), calc();
    if(ans==maxn*maxn*maxn) cout<<"SAFE\n";
    else cout << ans;
}