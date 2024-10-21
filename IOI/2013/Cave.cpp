#include "cave.h"
#include <bits/stdc++.h>
using namespace std;
 
void exploreCave(int n) {
    int s[n+1], d[n+1];
    for(int i = 0; i < n; i++) s[i]=0, d[i]=-1;
    for(int i = 0; i < n; i++)
    {
        int x = tryCombination(s);
        int l = 0, r = n-1;
        while(l<r)
        {
            int mid = (l+r)/2;
            for(int j = l; j <= mid; j++) if(d[j]==-1) s[j]=1;
            int y = tryCombination(s); int L = l;
            if(x>i or x==-1){
                if(y<=i and y!=-1)r=mid;
                else l=mid+1;
            }
            else{
                if(y>i or y==-1)r=mid;
                else l=mid+1;
            }
            for(int j = L; j <= mid; j++) if(d[j]==-1) s[j]=0;
        }
        if(x<=i and x!=-1) s[l]=1;
        d[l]=i;
    }
    answer(s, d);
}
