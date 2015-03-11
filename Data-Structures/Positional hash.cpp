//RandomUsername(Nikola Jovanovic)
//Positional hash

#include <bits/stdc++.h>
#define MAXN 300005
#define MAXLEN 600005
#define MOD 1000003
#define P 100009
#define lld long long
#define ff(i,a,b) for(int i=a; i<=b; i++)
#define fb(i,a,b) for(int i=a; i>=b; i--)
#define par pair<int, int>
#define fi first
#define se second
#define mid (l+r)/2

using namespace std;

/*
    Hash(s) = product ( s[i] * P^i ) % MOD
    MOD, P are large primes

    Changing ith char in s : Hash(s) - s[i] * P^i + new_char * P^i
    Moving all chars one position to the right : Hash(s) * P
    Hashing the [i,j] substring : Hash(i, j) = ( Hash(0, j) - Hash(0, i-1) ) / P^i
    (Modular inverse when dividing!)
*/

/*
    Implemented for http://codeforces.com/problemset/problem/514/C
    Strings in a set : O(logn * strlen) per find -- Too slow
    Strings in an unordered set : average O(1) per find -- Also too slow
    Random hash -- Too slow, O(strlen) per rehash
    So we hash using a positional hash, rehash in O(1) -- False positives
    Use unordered_set to fix false positives -- AC
    We won't query unordered_set a lot of times, so this works
    Also, unordered_set works
*/

char s[MAXLEN];
lld powp[MAXLEN];

void PrecMulP() // Precalcute powers of P
{
    powp[0] = 1;
    for (int i=1; i < MAXLEN; i++)
        powp[i] = (powp[i-1] * P) % MOD;
}

lld hashish(char* a) // Hash(s) = product ( s[i] * P^i ) % MOD
{
    lld ret = 0;
    lld len = strlen(a);
    for (int i=0; i < len; i++)
    {
        ret += powp[i] * a[i];
        ret %= MOD;
    }
    return ret;
}

int main()
{
    PrecMulP();
    cout<<hashish("Random")<<endl;
    cout<<hashish("Username")<<endl;
    cout<<hashish("Random")<<endl;
    return 0;
}
