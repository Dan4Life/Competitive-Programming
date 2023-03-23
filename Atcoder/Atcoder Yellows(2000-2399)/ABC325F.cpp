/*
Solved with editorial (Was quite close tho)
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 998244353;

string target;
int p10[10010];
int n, m, x, mask, tot;
pair<int,int> dp[10010][1100];

pair<int,int> recur(int pos, int sm, int cmask){
    if(pos==-1) return make_pair((cmask&mask)==mask,0);
    
    auto &res = dp[pos][cmask];
    if(sm and res.first!=-1) return res;
    
    pair<int,int> ans = make_pair(0,0);
    int lim = sm?9:target[pos]-'0';
    for(int d = 0; d <= lim; d++)
    {
        int CMASK = (cmask==0 and d==0)?0:cmask|(1<<d);
        auto x = recur(pos-1, d!=lim or sm, CMASK);
        ans.first+=x.first, ans.first%=MOD;
        ans.second+=(x.second+(x.first*p10[pos])%MOD*d)%MOD;
        ans.second%=MOD;
    }
    return sm?res=ans:ans;
}

int32_t main()
{
    for(int i = 0; i < 10010; i++)
        for(int j = 0; j < 1100; j++)
            dp[i][j] = make_pair(-1,0);
    p10[0] = 1;
    for(int i = 1; i < 10010; i++) p10[i] = (p10[i-1]*10)%MOD;
    cin >> target >> m; reverse(target.begin(),target.end());
    for(int i = 0; i < m; i++) cin >> x, mask|=(1<<x);
    cout << recur((int)target.size()-1,0,0).second;
}
