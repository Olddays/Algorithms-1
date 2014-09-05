//RandomUsername(Nikola Jovanovic)
//Sieve Of Eratosthenes
//Runtime: O(n)

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
#include <set>
#include <queue>
#include <stack>
#include <ctime>
#define MAXN 1000

using namespace std;

bool comp[1001];
bool tcomp[5001];

//comp[] keeps the composite numberes and the primes separated
void Sieve(int lmt)
{
    for(int i=2;i<=lmt;i++)
    {
        if(!comp[i])
        {
            for(int j=i*i;j<=lmt;j+=i)
            {
                comp[j]=true;
            }
        }
    }
}

//I also implemented the sieve translation technique for counting primes in an interval [a,b]
//With a sieve up to sqrt(b) we can just find primes in [a,b] in O(n) instead in O(n*isprime())
void TransSieve(int a,int b)
{
    int rng=b-a+1;
    int frst;
    //tcomp[0] -> a
    //tcomp[b-a] -> b
    int lmt=sqrt(a);
    for(int i=2;i<=lmt;i++)
    {
        if(!comp[i])
        {
            frst = (a/i)*i;
            if(frst!=a) frst+=i;
            for(int j=frst;j<=b;j+=i)
            {
                tcomp[j-a]=true;
            }
        }
    }
}

int main()
{
    Sieve(1000);
    printf("Primes 1-100:\n");
    for(int i=2;i<=100;i++)
    {
        if(!comp[i]) printf("%d ",i);
    }
    printf("\n");
    TransSieve(15000,20000);
    printf("Primes 15000-15100:\n");
    for(int i=0;i<100;i++)
    {
        if(!tcomp[i]) printf("%d ",i+15000);
    }
}
