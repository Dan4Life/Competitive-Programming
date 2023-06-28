#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define int long long
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
const int mxN = (int)5e2+2;
const int MOD = (int)1e9+7;
string a[mxN];
int n, dp[2][mxN][mxN];

int32_t main() {
    ifstream cin("palpath.in");
    ofstream cout("palpath.out");
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) 
        cin >> a[i], dp[0][i][i]=1;
    for(int k = 1, kk=1; k < n; k++,kk^=1){
        for(int i = 0; i < n; i++){
            int ci = n-i-1-k; 
            if(ci<0 or ci>=n) continue;
            for(int j = i; j < n; j++){
                int cj = n-j-1+k; 
                if(cj<0 or cj>=n) continue;
                for(int di = 0; di < 2; di++){
                    int pi = i+di; 
                    if(pi<0 or pi>=n) continue;
                    for(int dj = -1; dj < 1; dj++){
                        int pj = j+dj; 
                        if(pj<0 or pj>=n) continue;
                        dp[kk][i][j]+=(a[i][ci]==a[j][cj])*dp[kk^1][pi][pj], dp[kk][i][j]%=MOD;
                    }
                }
            }
        }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                dp[kk^1][i][j]=0;
    }
    cout << dp[(n-1)%2][0][n-1];
}
