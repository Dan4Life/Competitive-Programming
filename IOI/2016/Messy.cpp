#include <bits/stdc++.h>
#include "messy.h"
using namespace std;
 
int n;
vector<int> A(128);
 
void dnc(int l, int r){
    if(l==r) return; int m = (l+r)/2;
    string s(n,'1'); for(int i=l;i<=r;i++)s[i]='0';
    for(int i = l; i <= m; i++)
        s[i]='1',add_element(s),s[i]='0';
    dnc(l,m), dnc(m+1,r);
}
 
void cnd(int l, int r, vector<int>&a){
    if(l==r) return void(A[a[0]]=l);
    int m = (l+r)/2; vector<int> x[2];
    string s(n,'1'); for(int i : a) s[i]='0';
    for(int i : a) s[i]='1', x[check_element(s)].push_back(i), s[i]='0';
    cnd(l,m,x[1]), cnd(m+1,r,x[0]);
}
 
vector<int> restore_permutation(int N, int w, int r) {
    n = N; dnc(0,n-1); compile_set();
    vector<int> a(n); iota(begin(a),end(a),0);
    cnd(0,n-1,a); A.resize(n); return A;
}
