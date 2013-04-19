//RandomUsername(Nikola Jovanovic)
//KMP(String Matching) O(m+n)
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#define MAXN 100000
#define MAXM 1000

using namespace std;

int n,m;
char haystack[MAXN],needle[MAXM];//haystack(length:n), needle(length:m)
int pref[MAXN];
vector<int> hit;

void KMP()
{
     for(int i=0;i<=m-1;i++)
      pref[i]=-1; //prefix function initialization
      
      //calculate prefix function
     int i=0,j=-1;
     while(i<=m-1)//needle
     {
        while(j>-1 && needle[i]!=needle[j])
          j=pref[j];                        
          
        i++,j++;
        
        pref[i]=j;
     }
     
     //do the search
     i=0,j=0;
     while(i<=n-1)//haystack
     {
         while(j>-1 && haystack[i]!=needle[j])//when you fail
           j=pref[j];                         //make a jump
           
         i++,j++;                             
         
         if(j==m)                             //a hit!
         {
            hit.push_back(i-m);
            j=pref[j];     
         }     
     }
}

int main()
{
    scanf("%d %d",&n,&m);
    scanf("%s %s",haystack,needle);
    KMP();
    int limit=hit.size();
    for(int i=0;i<=limit-1;i++)
       printf("Match found! Position: %d\n",hit[i]);
    system("PAUSE");
    return 0;
}
