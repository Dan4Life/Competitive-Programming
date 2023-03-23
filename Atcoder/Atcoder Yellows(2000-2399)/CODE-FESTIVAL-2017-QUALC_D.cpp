/*
Solved with help (editorial)
Really nice trick learnt
Slow dp is straightforward, ie dp[i] = ans for first i characters
State transition is dp[i] = min(dp[i], dp[x]+1) where its possible to form a palindrome from s[x+1...i]
To speed it up, we can reformulate the problem as:
Each string is a number, such that in the number, if the ith bit is on, then there is an odd number of occurrences of character i(a=0...z=25)
To get the state for a substring, its equivalent to use prefix xor logic
If a substr is palindromable, then its xor is a power of 2, or 0
Using normal dp still TLES, so use an array such that A[x] = min answer for all dp[i] such that the prefix substr xor = x
Then it becomes straightforward to just check all 26 possible "correct" xor
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int maxn = (int)2e5+10;
string s;
unordered_map<int,int> calc;
int dp[maxn], f[maxn];

int32_t main(){
    cin >> s; int n = (int)s.size(); calc[0]=0;
    for(int i = 0; i < n; i++) f[i+1]=f[i]^(1<<(s[i]-'a'));
    for(int i = 1; i <= n; i++){
        int x = f[i];
        dp[i] = min(i-1, calc.count(x)?calc[x]:i+1);
        for(int j = 0; j < 26; j++)
            dp[i] = min(dp[i], calc.count((1<<j)^x)?calc[(1<<j)^x]:i);
        if(!calc.count(x)) calc[x]=++dp[i];
        else calc[x] = min(calc[x], ++dp[i]);
    }
    cout << dp[n];
}
