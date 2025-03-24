#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define sz(a) (int)a.size()
#define all(a) begin(a),end(a)
using ll = long long;
using ar2 = array<ll,2>;
using vi = vector<int>;
const int mxN = (int)1e6+10;
const ll INF = (int)1e9;
int n, MOD;
string s;
 
int dp[2][3][3][2][2];

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	cin >> n >> MOD >> s;
	for(auto &u:s)u=(u=='L'?0:1);
	for(int i = 0; i <= 2; i++)
		for(int j = 0; j <= 2; j++)
			for(int k = 0; k < 2; k++)
				for(int l = 0; l < 2; l++)
					dp[n&1][i][j][k][l]=1;
	for(int i = n-1,ii=(n-1)&1; i >= 0; i--,ii^=1){
		for(int t = 0; t <= 2; t++){
			for(int lst = 0; lst <= 2; lst++){
				for(int row = 0; row < 2; row++){
					for(int sm = 0; sm < 2; sm++){
						int lim = sm?1:s[i];
						dp[ii][t][lst][row][sm] = 0;
						for(int d = 0; d <= lim; d++){
							if((t==d or row) and d==lst) continue;
							dp[ii][t][lst][row][sm]+=dp[ii^1][lst==d?d:t][d][d==lst][sm|(d<lim)];
							dp[ii][t][lst][row][sm]%=MOD;
 						}
					}
				}
			}
		}
	}
	cout << dp[0][2][2][0][0] << "\n";
}
