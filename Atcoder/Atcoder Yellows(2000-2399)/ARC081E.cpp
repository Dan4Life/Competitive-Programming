/*
Solved with help (editorial)
dp[i] = minimum length of subsequence that CANNOT be made starting from ith character of s
nx[i][j] = smallest position 'k' starting from ith character of s such that s[k]=j (where a=0,b=1...)
*/

#include <bits/stdc++.h>
using namespace std;

set<int> S[27]; string s;
int nx[200010][27], dp[200010];

int main(){
    cin >> s; s+='z'; int n = (int)s.size();

    for(int i = 0; i < 26; i++) S[i].insert(n);
    for(int i = 0; i < n; i++) S[s[i]-'a'].insert(i);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < 26; j++)
            nx[i][j] = *S[j].lower_bound(i); 

    for(int i = 0; i < n; i++) dp[i]=300010;
    for(int i = n-1; i >= 0; i--)
        for(int j = 0; j < 26; j++)
            dp[i]=min(dp[i],dp[nx[i][j]+1]+1);
    
    // The answer string can be built recursively from dp[]
    int pos = 0;
    while(pos<n){
        for(int j = 0; j < 26; j++){
            if(dp[pos]==dp[nx[pos][j]+1]+1){
                pos=nx[pos][j]+1; cout << (char)(j+'a'); break;
            }
        }
    }
}
