//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <bits/extc++.h>

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
#define lenl(x) (ll)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) y = x(y,z)


template <typename X, typename Y, typename Z>
using gp_hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using gp_hashmap_safe = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;

template <typename X, typename Y, typename Z>
using cc_hashmap = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using cc_hashmap_safe = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;

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

inline ll cross(pll a, pll b, pll c)
{
    return (a.fir - c.fir) * (b.sec - c.sec) - (a.sec - c.sec) * (b.fir - c.fir);
}

inline ll cross(pll a, pll b)
{
    return cross(a, b, {0,0});
}

pll operator+(const pll& a, const ii& b)
{
    return {a.fir + b.fir, a.sec + b.sec};
}

pll operator-(const pll& a, const ii& b)
{
    return {a.fir - b.fir, a.sec - b.sec};
}

ll dist(pll a)
{
    return a.fir*a.fir+a.sec*a.sec;
}

namespace sol
{
    const int N = 1e6+5;

    ii t[N];
    int n;

    void read()
    {
        cin >> n;
        n *= 2;

        for (int i = 0; i < n; i += 2)
        {
            cin >> t[i].fir >> t[i].sec;

            if (t[i] == ii{0,0})
            {
                n -= 2, i -= 2;
                continue;
            }

            t[i ^ 1] = {-t[i].fir, -t[i].sec};
        }
    }
    
    void solve()
    {
        #define quoter(X) ((X.sec<0)*2 + ((X.fir<0) ^ (X.sec<0)))

        sort(t, t + n, [&](const ii& a, const ii& b){
            int qa = quoter(a), qb = quoter(b);
            if (qa == qb)
                return cross(a, b) > 0;
            return qa < qb;
        });

        int a = 0, b = 0;
        pll v = t[a], bv = v;


        #define nxt(x) ((x+1)%n)

        while (a < n)
        {
            while (nxt(b) != a)
            {
                int nxt_b = nxt(b);
                pll nxt = v + t[nxt_b];

                if (dist(v) > dist(nxt))
                    break;

                b = nxt_b;
                v = nxt;
            }

            if (dist(v) > dist(bv))
                bv = v;

            a++;

            v = v - t[a - 1];

            if (b == a - 1)
                b = a, v = v + t[a];
        }

        cout << dist(bv) << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    sol::solve();
}