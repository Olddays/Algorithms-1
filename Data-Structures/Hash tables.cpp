//RandomUsername(Nikola Jovanovic)
//Hash
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#define MAXN 100000
#define MOD 1720031
using namespace std;

int hash[MOD];//Hash table

void hashish(int x,int y)//Hash is for faggots so I'll be short
{
    long long sum=x*10007+y;//Invent a fancy function. You can also use
    sum%=MOD;               //powers(a*x^3+b*x^2...). Collision lists when needed.
    hash[sum]++;            //All in all, it's a thing for faggots.
}

int main(int argc, char *argv[])
{
   //#swag
}
