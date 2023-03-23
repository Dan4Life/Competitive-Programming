#include "jumps.h"
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
const int mxN = (int)2e5+2, mxLg = 19;
stack<pair<int,int>> S;
int n, pr[mxN], nx[mxN];
int l[mxLg][mxN], r[mxLg][mxN], hi[mxLg][mxN];
 
void calc(int jmp[][mxN]){
    for(int i = 1; i < mxLg; i++)
        for(int j = 1; j <= n; j++)
            jmp[i][j] = jmp[i-1][jmp[i-1][j]];
}
 
void init(int N, vector<int> a) {
    n = N; a.insert(a.begin(),-1);
    for(int i = 1; i <= n; i++){
        while(!S.empty() and S.top().fi<a[i]) S.pop();
        if(!S.empty()) pr[i] = S.top().se;
        S.push({a[i],i});
    }
    while(!S.empty()) S.pop();
    for(int i = n; i>=1; i--){
        while(!S.empty() and S.top().fi<a[i]) S.pop();
        if(!S.empty()) nx[i] = S.top().se;
        S.push({a[i],i});
    }
    for(int i = 1; i <= n; i++){
        l[0][i]=pr[i], r[0][i]=nx[i];
        if(l[0][i] and r[0][i])
            hi[0][i] = (a[pr[i]]<a[nx[i]]?nx[i]:pr[i]);
    }
    calc(l), calc(r), calc(hi);
}
 
int get_path(int *x, int y, int z, int jmp[][mxN], int rx=1, int tot=0){
    for(int i = mxLg-1; i >= 0; i--)
        if(jmp[i][*x]>=rx and jmp[i][*x]<y)
            if(nx[jmp[i][*x]] and nx[jmp[i][*x]]<=z)
                *x = jmp[i][*x], tot+=(1<<i);
    return tot;
}
 
int minimum_jumps(int A, int B, int C, int D) {
    A++,B++,C++,D++;
    int x = B; get_path(&x,C,D,l,A);
    if(nx[x]>=C and nx[x]<=D) return 1;
    int ans = get_path(&x,C,C-1,hi);
    if(nx[hi[0][x]]>=C and nx[hi[0][x]]<=D) return ans+2;
    ans+=get_path(&x,C,C-1,r); x = r[0][x];
    return (nx[x]>=C and nx[x]<=D)?ans+2:-1;
}
