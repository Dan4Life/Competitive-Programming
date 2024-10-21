#include <bits/stdc++.h>
#include "cluedo.h"
#include "grader.h"
using namespace std;
 
void Solve()
{
    int i = 1, j = 1, k = 1, ans = 20;
    while(ans--)
    {
        int x = Theory(i, j, k);
        if(x==1) i++;
        if(x==2) j++;
        if(x==3) k++;
        if(x==0) return;
    }
}
