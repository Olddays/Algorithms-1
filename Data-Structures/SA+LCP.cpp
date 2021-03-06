//RandomUsername(Nikola Jovanovic)
//Suffix Array + LCP Array
//Credits go to PetarV-, the Sensei

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <set>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>
#define MAXLEN 1000000

using namespace std;

int len, it; //length of the string, and the iterator
char s[MAXLEN]={'b','a','n','a','n','a','\0'}; //the string, test
int SA[MAXLEN], LCP[MAXLEN]; //SA+LCP
int tmp[MAXLEN], posInSA[MAXLEN]; //position of i in SA, used as a hint for sorting
int currPaired; //used in LCP build

bool suffcmp(int i, int j)//used for smart sorting
{
    //different bucket
    if(posInSA[i]!=posInSA[j])
        return posInSA[i] < posInSA[j];
    //same bucket, jump it chars
    //rinse and repeat
    i+=it;
    j+=it;
    if(i<len && j<len)
        return posInSA[i] < posInSA[j];
    else
        return i > j;
}

//O(len log^2 len)
//sort the array of suffixes
void buildSA()
{
    //initialize SA
    for(int i=0;i<=len-1;i++)
    {
        SA[i]=i;
        posInSA[i]=s[i]; //initial sorting hint is first char
    }
    for(it=1;it<=2*len;it*=2) //exponential increments
    {
        //sort using the current hint
        sort(SA,SA+len,suffcmp);

        //update the hints
        //(create the buckets, for every inequality tmp++)
        //preparing for the next iteration
        for(int i=0;i<=len-2;i++)
        {
            tmp[i+1]=tmp[i];
            if(suffcmp(SA[i],SA[i+1]))
                tmp[i+1]++;
        }
        //copy the buckets where they belong
        for(int i=0;i<=len-1;i++)
            posInSA[SA[i]]=tmp[i];
        //sorted?
        if(tmp[len-1]==len-1)
            break;
    }
}

//O(len)
//LCP[i] := LCP(SA[i],SA[i+1])
void buildLCP()
{
    //variable init
    int j;
    currPaired=0;
    //main loop(banana,anana,nana,ana,na,a)
    for(int i=0;i<=len-1;i++)
      if(posInSA[i]!=len-1) //s[len] doesn't exist, currPaired is always 0 when you're about to skip one iteration 
      {                     //currPaired > 0 => LCP[posInSA[i-1]] > 1 => LCP[posInSA[i]] > 0 => posInSA[i] != len - 1
          //we are currently computing LCP(i,j=i's successor in SA)
          j=SA[posInSA[i]+1];
          //manually find the longest common prefix
          while( s[i+currPaired] == s[j+currPaired] )
             currPaired++;
          //write it down
          LCP[posInSA[i]]=currPaired;
          //decrease it only by one to prepare for the next iteration
          //if i and j have currPaired in common
          //the successor of i+1 must have at least currPaired-1
          //in common with i+1 (i+1 = i without the first char)
          if(currPaired>0)
            currPaired--;
      }
}

int main()
{
    //test
    len = 6;

    buildSA();
    buildLCP();

    for (int i=0;i<=len-1;i++)
        printf("SA[%d]=%d\n",i,SA[i]);
    for (int i=0;i<=len-1;i++)
        printf("LCP[%d]=%d\n",i,LCP[i]);

    return 0;
}

//Practice tasks:
//http://www.z-trening.com/tasks.php?show_task=5000001916
//http://www.z-trening.com/tasks.php?show_task=5000000451
//http://www.z-trening.com/tasks.php?show_task=5000001626
//http://www.z-trening.com/tasks.php?show_task=5000000320
//http://www.codechef.com/MARCH14/problems/SSTORY
