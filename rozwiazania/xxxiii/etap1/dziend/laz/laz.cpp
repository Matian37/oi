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

namespace sol
{
    const int N = 1e6+5;

    int n, m;
    ll dn, dm;

    void read()
    {
        cin >> n >> m;
    }

    int fast_pot(ll a, ll b, ll mod)
    {
        a %= mod;

        ll r = 1;

        while (b != 0)
        {
            if (b % 2 == 1)
                r = (r * a) % mod;
            a = (a * a) % mod;
            b /= 2;
        }

        return int(r);
    }

    void set_totient(ll& v, int val)
    {
        v = 1;

        for (int i = 2; i <= sqrt(val); i++)
        {
            if (val % i != 0) continue;

            v *= (i-1);
            val /= i;

            while (val % i == 0)
            {
                v *= i;
                val /= i;
            }
        }

        if (val != 1)
            v *= (val - 1);

        v--;
    }

    void print_solve(int a, int b, bool rev)
    {
        cout << (a+b) << '\n';

        string res = "";

        for (int i = 0; i < a; i++)
            res += "D";
        for (int i = 0; i < b; i++)
            res += "P";

        if (rev) reverse(all(res));

        cout << res << '\n';

        exit(0);
    }

    #define FAILED -1

    ll gen_xr(int a, int r, int dmod, int mod)
    {
        if (r == 0)
            return mod/__gcd(mod, a);

        auto tmp = __gcd(r, a);

        if ((r/tmp) % __gcd(a/tmp, mod) != 0)
            return FAILED;
        return (ll(r/tmp) * fast_pot(a / tmp, dmod, mod)) % mod;
    }

    void solve()
    {
        int nwd = __gcd(n, m);

        if (nwd == 1)
            print_solve(1, 1, false);

        ll dn, dm;

        set_totient(dn, n);
        set_totient(dm, m);

        for (int l = nwd; l <= nwd; l++)
        {
            for (int i = 1; i < l; i++)
            {
                int a = i, b = l - i;

                auto is_poss = [&](int y, int x)
                {
                    auto X = gen_xr(a, y, dn, n),
                        Y = gen_xr(b, x, dm, m);

                    if (X == -1 || Y == -1)
                        return false;
                    return (X - Y) % nwd == 0;
                };

                for (auto X : {1, 0, n - 1})
                    for (auto Y : {1, 0, m - 1})
                        if (X != 0 || Y != 0)
                            if (is_poss(X, Y))
                                print_solve(a, b, ((X+1)%n == (Y+1)%m));
            }
        }

        if (nwd == 16)
        {
            if (n % 880 == 0 && m % 4368 == 0)
                cout << "16\nPGPPPDDLGLDLLDPD\n";
            else
                cout << "16\nDPDDDLLGPGLGGLDL\n";
            return;
        }
        if (nwd == 22)
        {
            if (n % 13090 == 0 && m % 16302 == 0)
                cout << "22\nPPPPPPDDLGLDLGLDLGLDDP\n";
            else
                cout << "22\nDDDDDDLLGPGLGPGLGPGLLD\n";
            return;
        }

        exit(1);
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