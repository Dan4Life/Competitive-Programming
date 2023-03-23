#include "secret.h"
#include <bits/stdc++.h>
using namespace std;
 
const int mxN = 1010;
const int mxLg = 10;
int n, a[mxN], ans[mxLg][mxN], mask[mxN];
 
void dnc(int l, int r, int lev){
    if(l==r) return;
    int m = (l+r)/2; ans[lev][m]=a[m], ans[lev][m+1]=a[m+1];
    for(int i = m-1; i>=l; i--) ans[lev][i] = Secret(a[i],ans[lev][i+1]);
    for(int i = m+2; i<=r; i++) ans[lev][i] = Secret(ans[lev][i-1],a[i]);
    for(int i = m+1; i<=r; i++) mask[i]^=(1<<lev);
    dnc(l,m,lev+1), dnc(m+1,r,lev+1);
}
 
void Init(int N, int A[]) {
    for(int i = 0; i < N; i++) a[i]=A[i];
    dnc(0,N-1,0); n=N;
}
 
int Query(int L, int R) {
    if(L==R) return a[L];
    int m = __builtin_ctz(mask[L]^mask[R]);
    return Secret(ans[m][L],ans[m][R]);
}
