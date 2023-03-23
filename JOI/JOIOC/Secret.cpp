#include "secret.h"
#include <bits/stdc++.h>
using namespace std;
 
const int mxN = 1010;
int n, a[mxN], ans[mxN][mxN];
 
void dnc(int l, int r){
    if(l==r) return;
    int m = (l+r)/2; ans[m][m]=a[m], ans[m+1][m+1]=a[m+1];
    for(int i = m-1; i>=l; i--) ans[i][m] = Secret(a[i],ans[i+1][m]);
    for(int i = m+2; i<=r; i++) ans[m+1][i] = Secret(ans[m+1][i-1],a[i]);
    dnc(l,m), dnc(m+1,r);
}
 
int dnc2(int l, int r, int L, int R){
    int m = (l+r)/2;
    if(L<=m and m<R)
        return Secret(ans[L][m],ans[m+1][R]);
    if(m<L) return dnc2(m+1,r,L,R);
    return dnc2(l,m,L,R);
}
 
void Init(int N, int A[]) {
    for(int i = 0; i < N; i++) a[i]=A[i];
    dnc(0,N-1); n=N;
}
 
int Query(int L, int R) {
    if(L==R) return a[L];
    return dnc2(0,n-1,L,R);
}
