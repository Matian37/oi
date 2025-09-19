//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

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
#define self(x,y,z) x = z(x,y)

template <typename X, typename Y, typename Z>
using gp_hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using cc_hashmap = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
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
    ull n, k, c;

    void read()
    {
        cin >> n >> k >> c;
    }

    vector<ull> factors;

    ull compute_pos(ull x)
    {
        uint m = len(factors);

        ll r = x;

        for (uint i = 1; i < (1U << m); i++)
        {
            ll mult = 1;

            for (uint j = 0; j < m; j++)
                if (i >> j & 1)
                    mult *= factors[j];
            
            if (__builtin_popcount(i) % 2) r -= x / mult;
            else r += x / mult;
        }

        return r;
    }
    
    vector<ull> result;

    void solve()
    {
        ull tmp = n;

        for (ull i = 2; i <= sqrtl(tmp); i++)
        {
            int cnt = 0;

            while (tmp % i == 0)
                cnt = 1, tmp /= i;
            if (cnt != 0) factors.push_back(i);
        }
        if (tmp != 1)
            factors.push_back(tmp);

        ull low = 1, high = 1e18, med;

        while (low != high)
        {
            med = (low + high) / 2;
            if (compute_pos(med) < k) low = med + 1;
            else high = med;
        }

        ull val = low;

        auto test = [&](ull x)
        {
            for (auto i : factors)
                if (x % i == 0)
                    return false;
            return true;
        };

        while (result.size() != c)
        {
            if (!test(val)) goto nxt;
            
            result.push_back(val);

            nxt:
            val++;
        }

        for (auto i : result)
            cout << i << ' ';
        cout << '\n';
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