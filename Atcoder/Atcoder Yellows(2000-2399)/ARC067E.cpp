/*
Solved with help (external help)
dp[i][j] is number of ways to pick from first i people, groups consisting of AT LEAST j people each
dp[i][j] = dp[i][j-1]*comb(i,k*j)*(number of ways to arrange k groups of j people each)
the last two expressions can be done using dp
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
const int maxn = (int)1e3+10;
const int MOD = (int)1e9+7;
int n, A, B, C, D;
int dp[maxn][maxn], comb[maxn][maxn], dp2[maxn][maxn];

int poww(int a, int b){
    if(b==0) return 1;
    int x = poww(a, b/2); x*=x, x%=MOD;
    if(b&1) x*=a, x%=MOD; return x;
}

int32_t main(){
    cin >> n >> A >> B >> C >> D; 
    for(int i = 0; i <= n; i++) comb[i][0]=1;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= i; j++)
            comb[i][j] = (comb[i-1][j-1]+comb[i-1][j])%MOD;

    for(int i = 0; i <= n; i++) dp[0][i] = dp2[0][i] = 1;

    for(int i = 1; i <= n; i++)
        for(int j = 1; i*j <= n; j++)
            dp2[i][j] = ((dp2[i-1][j]*comb[i*j][j])%MOD*poww(i,MOD-2))%MOD;
    
    for(int i = 1; i <= n; i++){
        for(int j = A; j <= B; j++){ //Loops j,k run in O(NlogN) 
            dp[i][j] = dp[i][j-1];
            for(int k = C; k <= D and i>=k*j; k++) 
                dp[i][j] = (dp[i][j]+(dp[i-k*j][j-1]*comb[i][k*j])%MOD*dp2[k][j])%MOD;
        }
    }
    cout << dp[n][B];
}