#include <bits/stdc++.h>
using namespace std;
const int mxN = (int)1e6;
 
int IND=1,tot=0;
char seg[mxN*160];
int num[mxN], ro[mxN];
int L[mxN*160], R[mxN*160];
 
int newChild(int p, char v){ int p2=++IND; L[p2]=L[p],R[p2]=R[p], seg[p2]=v; return p2; }
int newParent(int l, int r){ int p = ++IND; L[p]=l, R[p]=r; return p; }
 
int upd(int x, char v, int p, int l=0, int r=mxN){
    if(!p) return p; int mid = (l+r)/2;
    if(l==r) return newChild(p,v);
    if(!L[p]) L[p]=++IND; if(!R[p]) R[p]=++IND;
    if(x<=mid) return newParent(upd(x,v,L[p],l,mid),R[p]);
    return newParent(L[p],upd(x,v,R[p],mid+1,r)); 
}
 
int query(int x, int p, int l=0, int r=mxN){
    if(l==r) return seg[p]; int mid = (l+r)/2;
    if(x<=mid) return query(x,L[p],l,mid);
    return query(x,R[p],mid+1,r);
}
 
void Init(){ ro[0]=1; }
void TypeLetter(char L){ tot++,ro[tot]=upd(num[tot-1],L,ro[tot-1]), num[tot]=num[tot-1]+1; }
void UndoCommands(int x){ tot++,ro[tot]=ro[tot-x-1], num[tot]=num[tot-x-1]; }
char GetLetter(int x){ return query(x,ro[tot]); }
