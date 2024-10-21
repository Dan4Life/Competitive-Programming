#include "quality.h"
#include <bits/stdc++.h>
using namespace std;
int n, m, h, w, a[3001][3001], pre[3002][3002];
 
inline int sum(int x1, int y1, int x2, int y2){
    return pre[x2][y2]-pre[x1-1][y2]-pre[x2][y1-1]+pre[x1-1][y1-1];
}
 
bool chk(int x){
    for(int i = 0; i <= n; i++) pre[i][0]=0;
    for(int i = 0; i <= m; i++) pre[0][i]=0;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            pre[i][j] = pre[i-1][j]+pre[i][j-1]-pre[i-1][j-1]+(a[i][j]<=x);
    for(int i = 1; i <= n-h+1; i++)
        for(int j = 1; j <= m-w+1; j++)
            if(sum(i,j,i+h-1,j+w-1)>=h*w/2+1) return true;
    return false;
}
 
int rectangle(int R, int C, int H, int W, int A[3001][3001]) {
    n=R, m=C, h=H, w=W;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            a[i+1][j+1] = A[i][j];
    int l = 0, r = n*m;
    while(l+1<r){
        int mid = (l+r)/2;
        if(chk(mid)) r=mid;
        else l=mid;
    }
    return r;
}
