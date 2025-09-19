//
// Mateusz Pietrowcow
//
 
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

// best can in the galaxy
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
    const int N = 1e6+5;
    pull t[N];
    int n;

    void read()
    {
        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cin >> t[i].fir >> t[i].sec;
            if (t[i].fir > t[i].sec) swap(t[i].fir, t[i].sec);
        }

        mt19937 rng(timeNow() ^ (ull)make_unique<char>().get());
        shuffle(t,t+n, rng);
    }

    vector<int> can;
    vector<ii> primes;

    ull getResult()
    {
        vector<int> lic(len(primes), 0);

        ull r = t[0].sec;

        for (int i = 1; i < n; i++)
            r = __gcd(r, t[i].sec);

        ull val = 1;

        while (true) // can be optimized
        {            
            bool good = [val]()
            {
                for (int i = 0; i < n; i++)
                    if (t[i].fir % val && t[i].sec % val)
                        return false;
                return true;
            }();

            if (good) r = max(r, val);

            bool did = false;
            
            for (int i = 0; i < len(primes); i++)
            {
                if (lic[i] == primes[i].sec)
                {
                    for (int j = 0; j < lic[i]; j++)
                        val /= primes[i].fir;
                    lic[i] = 0;
                }
                else
                {
                    lic[i]++;
                    val *= primes[i].fir;
                    did = true;
                    break;
                }
            }

            if (!did) break;
        }

        return r;
    }

    void solve()
    {
        for (int i = 0; i < n; i++)
        {
            int x = (int)t[i].fir;

            if (x % 2 == 0)
                can.push_back(2),
                x /= 1<<__builtin_ctz((uint)x);

            for (int j = 3; j <= sqrt(x); j += 2)
            {
                if (x % j) continue;

                can.push_back(j);

                while (x % j == 0) 
                    x /= j;
            }

            if (x != 1) can.push_back(x);
        }

        sort(all(can));
        can.resize(distance(can.begin(), unique(all(can))));

        for (auto i : can)
        {
            int c = [i]()
            {
                int k = INF;
                
                for (int j = 0; j < n; j++)
                    if (t[j].fir % i && t[j].sec % i)
                        return 0;

                for (int j = 0; j < n; j++)
                {
                    int a = (int)t[j].fir;
                    ull b = t[j].sec;
                    int ca = 0, cb = 0;

                    while (a % i == 0) a /= i, ca++;
                    while (b % i == 0) b /= i, cb++;

                    k = min(k, max(ca,cb));

                    if (k == 0) 
                        return k;
                }
                return k;
            }();

            if (c != 0) 
                primes.push_back({i, c});
        }

        cout << getResult() << '\n';
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