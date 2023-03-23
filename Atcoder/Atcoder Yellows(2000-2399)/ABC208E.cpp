/*
Solved by myself (Wow, it's been a long time since i submitted a yellow. Won't take too long again...)
Basically digit dp like in editorial
dp[i][j][k][l] = answer considering the first i digits such that the digit product is l and:
                 j = 0/1 (determines if the current number is already smaller than n)
                 k = 0/1 (determines if we still have only leading zeros in the number)               
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
string s;
unordered_map<int,int> dp[20][2][2];

int recur(int pos=0, int prod=1, bool sm=0, bool le=1){
    int n = (int)s.size();
    if(dp[pos][sm][le].count(prod)) 
        return dp[pos][sm][le][prod];
    if(pos==n) return dp[pos][sm][le][prod]=(!le and prod<=k);
    int lim = (sm?9:s[pos]-'0'), ans = 0;
    for(int d = 0; d <= lim; d++){
        bool SM=sm, LE=le;
        int PROD = prod;
        if(d<lim and !SM) SM=1;
        if(LE and d) LE=0;
        if(!LE) PROD*=d;
        ans+=recur(pos+1, PROD, SM, LE);
    }
    return dp[pos][sm][le][prod]=ans;
}

int32_t main()
{
    cin >> n >> k; 
    s = to_string(n); 
    cout << recur();
}
