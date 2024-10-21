#include <bits/stdc++.h>
#include "grader.h"
using namespace std;
 
void play(){
    map<char, int> M, N;
    for(int i = 1; i <= 50; i+=2)
    {
        char a = faceup(i), b = faceup(i+1);
        if(M[a]>=1) N[a]=i;
        else M[a]=i;
        if(M[b]>=1) N[b]=i+1;
        else M[b]=i+1;
    }
    for(char i = 'A'; i < 'Z'; i++)
        faceup(M[i]), faceup(N[i]);
}
