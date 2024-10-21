#include "dna.h"
#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int)a.size()
 
string s, t;
const int mxN = (int)1e5+10;
int pref[3][3][mxN];
 
void init(string a, string b) {
    int n = sz(a);
    map<char,int> M; M.clear();
    M['A']=0,M['C']=1,M['T']=2;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < 3; j++)
            for(int k = 0; k < 3; k++)
                pref[j][k][i+1]=pref[j][k][i]
                    +(M[a[i]]==j and M[b[i]]==k);
}
 
int get(int i, int j, int l, int r){
    return pref[i][j][r+1]-pref[i][j][l];
}
 
int get_distance(int l, int r) {
    int AC=get(0,1,l,r);
    int CA=get(1,0,l,r);
    int AT=get(0,2,l,r);
    int TA=get(2,0,l,r);
    int CT=get(1,2,l,r);
    int TC=get(2,1,l,r);
    int A=AC+AT-CA-TA;
    int C=CA+CT-AC-TC;
    int T=TA+TC-AT-CT;
    if(A|C|T) return -1;
    int ACCA = min(AC,CA);
    int ATTA = min(AT,TA);
    int CTTC = min(CT,TC);
    AC-=ACCA, CA-=ACCA;
    AT-=ATTA, TA-=ATTA;
    CT-=CTTC, TC-=CTTC;
    int rem = AC+CA+AT+TA+CT+TC;
    return ACCA+ATTA+CTTC + rem*2/3;
}
