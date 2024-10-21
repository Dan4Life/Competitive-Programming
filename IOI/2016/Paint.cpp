#include "paint.h"
#include <bits/stdc++.h>
using namespace std;
 
string ans, ss;
vector<int> C;
int pref[200010], pref2[200010], a[200010][2];
int n, k, dp[200010][101];
 
bool recur(int pos, int num)
{
    if(dp[pos][num]!=-1) return dp[pos][num];
    if(pos==n) return dp[pos][num]=(num==k);
    bool op1=false, op2=false;
    if(num==k){
        int cnt = pref2[n]-pref2[pos];
        if(cnt) return false;
        op2 = recur(pos+1, num);
        if(op2) a[pos][0] = 1;
        return dp[pos][num]=true;
    }
    int cnt = C.at(num);
    if(ss[pos]=='_')
    {
        if(ss[pos]=='X') return dp[pos][num]=false;
        op2 = recur(pos+1, num);
    }
    else if(ss[pos]=='X'){
        if(num!=k-1){
            if(pos+cnt<n and pref[pos+cnt]==pref[pos])
                if(pref2[pos+cnt+1]==pref2[pos+cnt])
                    op1 = recur(pos+cnt+1, num+1);
        }
        else{
            if(pos+cnt<=n and pref[pos+cnt]==pref[pos])
                op1 = recur(pos+cnt, num+1);
        }
    }
    else{
        if(num!=k-1){
            if(pos+cnt<n and pref[pos+cnt]==pref[pos])
                if(pref2[pos+cnt+1]==pref2[pos+cnt])
                    op1 = recur(pos+cnt+1, num+1);
        }
        else{
            if(pos+cnt<=n and pref[pos+cnt]==pref[pos])
                op1 = recur(pos+cnt, num+1);
        }
        op2 = recur(pos+1, num);
    }
    if(op1)
    {
        a[pos][1]++, a[pos+cnt][1]--;
        if(num!=k-1) a[pos+cnt][0] = 1;
    }
    if(op2) a[pos][0] = 1;
    return dp[pos][num]=(op1||op2);
}
 
string solve_puzzle(string s, vector<int> c)
{
    n = (int)s.size(), k = (int)c.size();
    ss = s, C = c, pref[0]=pref2[0]=0;
    for(int i = 0; i < n; i++)
        pref[i+1] = pref[i]+(s[i]=='_'?1:0),
        pref2[i+1] = pref2[i]+(s[i]=='X'?1:0);
    memset(dp, -1, sizeof(dp)), recur(0, 0);
    for(int i = 0; i < n; i++)
    {
        a[i+1][1]+=a[i][1];
        if(a[i][1] and a[i][0]) ans+='?';
        else if(a[i][1]) ans+='X';
        else ans+='_';
    }
    return ans;
}
