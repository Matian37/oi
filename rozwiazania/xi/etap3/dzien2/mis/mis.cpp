//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include "mis.h"

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
    const int N = 2*1e6+5;

    int n, sc = 0, sr = 0;

    inline int id(int a, int b)
    {
        int m = min(a,b);

        a -= m;
        b -= m;

        return (a == 0 ? b : n + a);
    }

    int lX[N], lY[N];
    ii lid[N];

    void add(int x, int y)
    {
        lX[x] = y;
        lY[y] = x;
        lid[id(x,y)] = {x,y};
    }

    void getLosing()
    {
        vector<bool> done(2*n, false), col(n, false), row(n, false);

        int i = 0, j = 0;

        while (j < n)
        {
            if (col[j])
            {
                j++;
                continue;
            }

            while (i < n)
            {
                if (!done[id(i,j)] && !row[i])
                    break;
                i++;
            }

            if (i >= n || j >= n)
                break;
            done[id(i,j)] = done[id(j,i)] = true;
            col[i] = col[j] = true;
            row[i] = row[j] = true;
            add(i,j);
            add(j,i);
            j++;
        }
    }

    void init(int mpo)
    {
        n = mpo;

        for (int i = 0; i < 2 * n; i++)
            lX[i] = -1, lY[i] = -1, lid[i] = {-1,-1};

        getLosing();
    }
};

void poczatek(int m, int p, int mpo)
{
    sol::init(mpo + 1);
}

void ruch_bolka(int m, int p, int *bm, int *bp)
{
    *bm = *bp = 0;

    int minn = min(m,p);

    m %= (sol::n);
    p %= (sol::n);

    #define m1 ((sol::n + p - sol::lX[m]) % sol::n)

    if (sol::lX[m] != -1 && sol::lX[m] != p && m1 <= p)
    {
        *bp = m1;
        return;
    }

    #define m2 ((sol::n + m - sol::lY[p]) % sol::n)

    if (sol::lY[p] != -1 && sol::lY[p] != m && m2 <= m)
    {
        *bm = m2;
        return;
    }
    
    ii diag = sol::lid[sol::id(m,p)];
    int d = (sol::n + m - diag.fir) % sol::n;

    *bm = d, *bp = d;
    return;
}