//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include "cliclib.h"

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;
using ld = long double;
using pld = pair<ld,ld>;
#define int128 __int128_t
#define uint128 __uint128_t

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

// best primes in the galaxy
#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define len(x) (int)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) x = z(x,y)

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

namespace sol
{
    const int N = 3e4+5, P2 = 15, P3 = 10;
    pair<bool,int> dp[N][P2+1][P3+1];

    int p3[P3+1], p2[P2+1];

    // inline void __attribute__((always_inline)) 

    void compute(int i, int j, int k)
    {
        ll sum = i - (ll)p2[j] * p3[k];

        if (sum <= 0)
            dp[i][j][k] = {false, 1};
        else if (!dp[sum][0][0].fir)
            dp[i][j][k] = {true, 1};
        else if (!dp[i][j + 1][k].fir)
            dp[i][j][k] = {true, 2};
        else if (!dp[i][j][k + 1].fir)
            dp[i][j][k] = {true, 3};
        else
            dp[i][j][k] = {false, 1};
    }

    void init(int n)
    {
        p2[0] = p3[0] = 1;
        for (int i = 1; i <= P2; i++)
            p2[i] = 1 << i;
        for (int i = 1; i <= P3; i++)
            p3[i] = p3[i - 1] * 3;

        dp[0][0][0] = {true, 1};

        for (int i = 1; i <= n; i++)
            for (int j = P3; j >= 0; j--)
                for (int k = P2; k >= 0; k--)
                    compute(i, k, j);
    }

    void move(int& stos, int& st2, int& st3, int& stawka, int ruch)
    {
        switch (ruch)
        {
            case 1:
                stos -= stawka;
                st2 = 0, st3 = 0;
                stawka = 1;
                break;
            case 2:
                stawka *= 2;
                st2++;
                break;
            case 3:
                stawka *= 3;
                st3++;
                break;
        }    
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n = inicjuj();

    sol::init(n);

    int stos = n, st2 = 0, st3 = 0, stawka = 1;

    while (stos > 0)
    {
        alojzy(sol::dp[stos][st2][st3].sec);
        sol::move(stos, st2, st3, stawka, sol::dp[stos][st2][st3].sec);
        sol::move(stos, st2, st3, stawka, bajtazar());
    }
}