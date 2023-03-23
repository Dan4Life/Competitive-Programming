/*
Solved by myself (but had to check implementation)
Same as official editorial
*/

#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MOD = (int)1e9+7;

int n, m, k, ans;
vector<int> v; 
int len[70000];
int dp[110][70000], dp2[110][70000];

int32_t main(){
    cin >> n >> k; int sum = 0;
    for(int i = 1; i*i<=n; i++){
        v.push_back(i);
        if(i*i!=n) v.push_back(n/i);
    }
    sort(v.begin(),v.end());
    
    dp[1][0]=len[0]=1; m =(int)v.size();
    for(int i = 1; i < m; i++) 
        dp[1][i] = len[i] = v[i]-v[i-1];

    for(int i = 1; i < k; i++){
        for(int j = 0; j < m; j++) 
            dp2[i][j+1]=dp2[i][j]+dp[i][j], dp2[i][j+1]%=MOD;

        for(int j = 0; j < m; j++) 
            dp[i+1][j]+=dp2[i][m-j]*len[j], dp[i+1][j]%=MOD;
    }
    for(int j = 0; j < m; j++) 
        sum+=dp[k][j], sum%=MOD;
    cout << sum;
}