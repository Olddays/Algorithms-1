#include <bits/stdc++.h>
#define lld long long
#define MAXLEN 1005

using namespace std;

//KMP O(wl + tl)
//good tut : http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=stringSearching
//failure function f[i] := the length of the longest proper suffix=prefix for string w[ 0 ]..w[ i-1 ] (string of length i)
// f[i] <=> w[ 0 ]...w[ f[i]-1 ]
//clarification : if we align t[j] and w[i], and fail to match a character we should try to match w[f[i]] and t[j]
//we move our word to the right skipping all the unnecessary comparations
//f[f[i]] is the second "best" prefix=suffix (best prefix=suffix of the best prefix=suffix )

char t[MAXLEN]; int tl; //text and textlen
char w[MAXLEN]; int wl; //word and wordlen
vector<int> matches; //matches will be stored here
int F[MAXLEN]; //failure function

void KMP()
{
    //Compute faliure function
    int i, j;
    F[0] = F[1] = 0; //always zero
    for(i=2; i<=wl; i++)//compute f[i]
    {
        j = F[i-1]; //expanding the solution for i-1 is our best guess for f[i]
        while(1)
        {
            //if w[j] and w[i-1] match, we expand, f[i] is found, break
            if(w[j] == w[i-1])  { F[i] = j + 1;  break; }
            //if we failed to expand an empty string, we have to quit trying, f[i] is zero, break
            if(j == 0) { F[i] = 0;  break; }
            //usually we just try expanding the next best match
            j = F[j];
        }
    }

    //Actual matching
    i = j = 0; //i - word iterator, j - text iterator
    while(1)
    {
        if(j == tl) break; //end of the text
                            //we are trying to match t[j] and p[i]
        if(t[j] == w[i])    //if they do match
        {
            i++, j++;       //move on
            if(i == wl)      //end of the word
            {
                matches.push_back(j - wl); //we found a match, and it' starting at t[j-wl]
                i = F[i];   //next possible match for t[j]
            }
        }
        else if(i > 0) i = F[i];    //if they do not match, try the next possible match for t[j]
        else j++;                   //if i=0 failed to match there are no more possible matches for t[j], move on
    }
}

int main()
{
    //Testing
    scanf("%s",t);
    scanf("%s",w);
    tl = strlen(t);
    wl = strlen(w);
    KMP();
    for(int i=0; i<matches.size(); i++)
        printf("%d ",matches[i]);
    return 0;
}
