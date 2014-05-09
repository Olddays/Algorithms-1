//RandomUsername(Nikola Jovanovic)
//Fast exponentiation + Multiplicative modular inverse
//Runtime: O(logb) for a^b

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
#define MOD 1007

using namespace std;

long long logExp(long long a,long long b)
{
    if(b==1) return a;
    long long res=logExp(a,b/2);
    if(b%2==0)
        return (res*res)%MOD;
    else
        return (((res*res)%MOD)*a)%MOD;
}

//Based on little Fermat's theorem
long long mulInv(long long x)
{
    return logExp(x,MOD-2);
}

int main()
{
    printf("%d\n",logExp(2,5));
    printf("%d\n",logExp(2,10));
    printf("%d\n",logExp(3,3));
    printf("%d\n",mulInv(3));
    printf("%d\n",mulInv(1000));
}
