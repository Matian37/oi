//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/numeric>

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;
//using int128 = __int128_t;
//using uint128 = __uint128_t;

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

struct Hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    int q;
    vector<ii> zap;

    void read()
    {
        cin >> q;

        zap.reserve(q);

        while (q--)
        {
            int a, b;
            cin >> a >> b;

            zap.push_back({a,b});
        }
    }

    const int N = 31650;

    vector<int> primes;
    int p[N];
    
    void init()
    {
        ull limit = 31622;

        for (ull i = 2; i <= limit; i++)
        {
            if (p[i] == 0)
            {
                p[i] = i;
                primes.push_back(i);
            }

            for (ull j : primes)
            {
                if (i * j > limit) continue;

                p[i * j] = j;
            
                if (j == p[i]) break;
            }
        }
    }

    set<int> s;

    ull cyfr[10];

    void solve()
    {
        init();

        cyfr[1] = 1;

        for (int j = 2; j < 10; j++)
            cyfr[j] = cyfr[j - 1] * 10;

        s.insert(1);

        #define potega(x,y) (cxx::power((ull)x,y))

        constexpr ull limit = 1e9;

        for (auto i : {ii{2,1},ii{3,1},ii{4, 2},ii{5,1},ii{6, 2},ii{7,1},ii{8,2},ii{9,3}}) 
        {
            if (i.sec == 1)
            {
                for (auto j : p)
                {
                    ull val = potega(j, i.fir-1);

                    if (val > limit) break;
                    if (val < cyfr[i.fir]) continue;
                    if (val >= cyfr[i.fir + 1]) break;

                    s.insert(val);
                }
                continue;
            }

            int p1 = (i.fir / i.sec) - 1, p2 = i.sec - 1;

            for (int j = 0; j < isize(primes); j++)
            {
                ull val1 = potega(primes[j], p1);

                if (val1 > limit) break;

                for (int k = 0; k < isize(primes); k++)
                {
                    if (j == k) continue;

                    ull val2 = potega(primes[k], p2);

                    if (val2 > limit) break;
                    
                    ull val3 = val1 * val2;

                    if (val3 > limit) break;
                    if (val3 < cyfr[i.fir]) continue;
                    if (val3 >= cyfr[i.fir + 1]) break;

                    s.insert(val3);
                }
            }
        }

        vector<int> prz;

        prz.reserve(isize(s));

        for (auto i : s)
            prz.push_back(i);

        for (auto[a, b] : zap)
        {
            int orga = a, orgb = b;

            int low = 0, high = isize(s) - 1, med;

            while (low != high)
            {
                med = (low + high) / 2;

                if (prz[med] < a) low = med + 1;
                else high = med;
            }

            a = low;

            low = 0, high = isize(s) - 1;

            while (low != high)
            {
                med = (low + high) / 2;

                if (prz[med] < b) low = med + 1;
                else high = med;
            }

            if (prz[low] > b) low--;
            b = low;

            if (a == b && orga > prz[a] || orgb < prz[a])
            {
                cout << "0\n";
                continue;
            }

            cout << (b - a + 1) << '\n';
        }
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