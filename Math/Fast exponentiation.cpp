//RandomUsername(Nikola Jovanovic)
//Fast exponentiation + Multiplicative modular inverse
//Runtime: O(logb) for a^b

#include <bits/stdc++.h>
#define MAXN 30005
#define MOD 1000000007
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2

using namespace std;

lld logExp(lld a, lld b)
{
    if(b==1) return a;

    lld m = logExp(a, b/2);
    m = (m * m) % MOD;

    if(b%2 == 0)
        return m;
    else
        return (m * a) % MOD;
}

lld logExpIt(lld a, lld b) //Iterative version, less memory
{
    // a^b = a^(2^b1 + 2^b2 + ... 2^bn) [ bi - ith bit position ]
    // a^b = a^(2^b1) * a^(2^b2) * ... * a^(2^bn)
    // so we multiply when w hit a set bit

    lld ret = 1;
    while(b > 0)
    {
        if(b%2 == 1) //last bit
        {
            ret *= a;
        }
        b /= 2; // b >>= 1;
        a *= a;
    }
    return ret;
}

//Based on little Fermat's theorem
lld mulInv(lld x)
{
    return logExp(x, MOD-2);
}

int main()
{
    printf("%lld\n",logExp(2,5));
    printf("%lld\n",logExpIt(2,5));
    printf("%lld\n",logExp(2,10));
    printf("%lld\n",logExpIt(2,10));
    printf("%lld\n",logExp(3,3));
    printf("%lld\n",mulInv(3));
    printf("%lld\n",mulInv(1000));
}
