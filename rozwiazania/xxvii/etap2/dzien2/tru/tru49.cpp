//
// Mateusz Pietrowcow
//

#pragma GCC optimize("fast-math,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

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
    size_t operator()(const ull& a) const
    {
        const static ull rng = (ull)timeNow() ^ (ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    ull N;

    void read()
    {
        cin >> N;
    }

    constexpr int px[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

    vector<ull> getNumbers(const int* p, ull LIMIT, int n)
    {
        vector<int> state(n,0);

        vector<ull> numbers;
        ull val = 1;

        while (true)
        {
            numbers.push_back(val);

            bool did = false;

            for (int i = 0; i < n; i++)
            {
                if (val * p[i] > LIMIT)
                {
                    for (int j = 0; j < state[i]; j++)
                        val /= p[i];
                    state[i] = 0;
                }
                else
                {
                    did = true;
                    state[i]++;
                    val *= p[i];
                    break;
                }
            }

            if (!did)
                break;
        }

        return numbers;
    }

    int sigma(ull x, const int* p, int n) // can be changed to ull
    {
        int r = 1;

        for (int i = 0; i < n; i++)
        {
            int cnt = 0;

            while (x % p[i] == 0)
                cnt++, x /= p[i];
            r *= (cnt + 1);
        }

        return r;
    }

    int vl[1'000'001];
    const int K1 = 7, K2 = 7;

    void solve()
    {
        vector<ull> n6 = getNumbers(px, min(N, (ull)1000000), K1),
                    n14 = getNumbers(px, min((ull)N, 1'000'000'000'000ULL), K2);
        
        sort(all(n6));
        sort(all(n14));

        for (int i = 0; i < len(n6); i++)
        {
            for (int j = 0; j < len(n14); j++)
            {
                if (n6[i] * n14[j] > N) break;
                vl[n6[i] * n14[j]] = sigma(n6[i] * n14[j], px, K2);
            }
        }

        ull result = 1, a = 1, b = 1, d = 1;

        for (int i = 0; i < len(n6); i++)
        {
            for (int j = i; j < len(n6); j++)
            {
                if (__gcd(n6[i],n6[j]) != 1) continue;

                for (int k = 0; k < len(n14); k++)
                {
                    if (n14[k] * n6[j] > N) break;

                    int r = vl[n14[k] * n6[i]] + vl[n14[k] * n6[j]] - vl[n14[k]];

                    if (r > result)
                        result = r, a = n14[k] * n6[i], b = n14[k] * n6[j]; 
                }
            }
        }

        cout << result << '\n';
        cout << a << ' ' << b << '\n';
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