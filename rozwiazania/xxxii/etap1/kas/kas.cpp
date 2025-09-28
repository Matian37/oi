//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include "kaslib.h"

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;
#define int128 __int128_t
#define uint128 __uint128_t

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

struct chash
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace pc
{
    const int N = 1e6 + 5;
    vector<int> primes;
    bitset<N> t;

    ll bg;

    void sieve(ll n)
    {
        for (int i = 2; i <= n; i++)
        {
            if (t[i]) continue;

            primes.push_back(i);
            bg = i;

            for (ll j = (ll)i * i; j <= n; j += i) t[j]=1;
        }
    }

    vector<pair<ll,vector<int>>> packed;

    void pack(int n)
    {
        sieve(n);

        packed.push_back({primes[0], {primes[0]}});

        for (int i = 1; i < isize(primes); i++)
        {
            if ((uint128)packed.back().fir * primes[i] > (uint128)INFULL)
                packed.push_back({primes[i], {primes[i]}});
            else
            {
                packed.back().fir *= primes[i];
                packed.back().sec.push_back(primes[i]);
            }
        }
    }
}

bool inline canGo(ll x, ll r)
{
    return (uint128)x * x * r <= (uint128)INFLL;
}

ll biggest(ll x)
{
    ll r = x;

    while ((uint128)r * x <= (uint128)INFULL)
        r *= x;
    return r;
}

pair<int, ll> arr[] = {
    {47, 260LL}, // 9
    {140, 3'700LL}, // 6
    {350, 20'000LL}, // 5
    {460, 800'000LL}, // 4
    {1300, 1'200'000LL}, // 3
    {1850, 650'000'000LL}, // 2
    {9500, 2'555'070'000'000LL} // 1
};

int main()
{
    pc::pack(850001);

    while (true)
    {
        ll result = 1;

        for (auto i : pc::packed)
        {
            for (auto j : arr)
                if (i.sec.front() >= j.fir && result <= j.sec)
                    goto nxt;

            ll val = Pytaj(i.fir);

            for (auto j : i.sec)
            {
                if (val % j == 0)
                {
                    if (canGo(j, result)) 
                        result *= Pytaj(biggest(j));
                    else 
                        result *= j;
                }

                if ((uint128)result * j > (uint128)INFLL) 
                    goto odp;

                for (auto k : arr)
                    if (j >= k.fir && result <= k.sec)
                        goto nxt;
            }

            if ((uint128)result * i.sec.back() > (uint128)INFLL) 
                goto odp;
        }

        if ((uint128)result * pc::bg > (uint128)INFLL)
        {
            odp:
            Odpowiedz(result);
            continue;
        }
        nxt:
        Szturchnij();
    }
}