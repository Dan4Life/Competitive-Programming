#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)1e3+10;
int n, m;
string a[mxN], b[2];

bool chk(int i, int j){
    if(i==n-1 or j==m-1 or i<0 or j<0) return 0;
    return (a[i].substr(j,2)==b[0] and a[i+1].substr(j,2)==b[1]);
}

int main()
{
    cin >> n >> m; int ans = 0, sum = 0;
    for(int i = 0; i < n; i++) cin >> a[i];
    cin >> b[0] >> b[1];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            sum+=chk(i,j);
    ans = sum;
    string s = "JOI"; int x = sum;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            for(auto k : s){ if(k==a[i][j]) continue;
                char t = a[i][j];
                sum = x-chk(i-1,j-1)-chk(i,j)-chk(i,j-1)-chk(i-1,j);
                a[i][j]=k;
                sum+=chk(i-1,j-1)+chk(i,j)+chk(i,j-1)+chk(i-1,j);
                ans = max(ans, sum); a[i][j]=t;
            }
        }
    }
    cout << ans << endl;
}
