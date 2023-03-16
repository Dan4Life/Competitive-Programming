#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define int long long
string dir1,dir2;
int n,m,dp[1010][1010];
int op1,op2,op3,f_x,f_y,b_x,b_y;
pair<int,int> DIR1[1010],DIR2[1010];

inline int dist(pair<int,int> a, pair<int,int> b){
    return (a.f-b.f)*(a.f-b.f)+(a.s-b.s)*(a.s-b.s);
}

int32_t main()
{
    ifstream cin("radio.in");
    ofstream cout("radio.out");
    cin >> n >> m >> f_x >> f_y >> b_x >> b_y >> dir1 >> dir2;
    for(int i = 0; i <= n; i++)
    {
        DIR1[i]={f_x,f_y};
        if(dir1[i]=='N') f_y++;
        else if(dir1[i]=='S') f_y--;
        else if(dir1[i]=='E') f_x++;
        else f_x--;
    }
    for(int i = 0; i <= m; i++)
    {
        DIR2[i]={b_x,b_y};
        if(dir2[i]=='N') b_y++;
        else if(dir2[i]=='S') b_y--;
        else if(dir2[i]=='E') b_x++;
        else b_x--;
    }
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            op1=op2=op3=1e18;
            if(i)op1 = dp[i-1][j];
            if(j)op2 = dp[i][j-1];
            if(i and j)op3 = dp[i-1][j-1];
            if(i or j) dp[i][j] = min({op1, op2, op3})+dist(DIR1[i],DIR2[j]);
        }
    }
    cout << dp[n][m];
}
