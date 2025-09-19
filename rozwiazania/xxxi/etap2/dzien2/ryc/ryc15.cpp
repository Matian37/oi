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

template<int K>
struct _swords
{
    int val[K] = {};

    inline int& operator[](int k)
    {
        return val[k];
    }

    bool operator<(_swords& b)
    {
        for (int i = 0; i < K; i++)
            if (val[i] != b.val[i])
                return val[i] < b.val[i];
        return false;
    }

    void choose(_swords& b)
    {
        if (!(*this < b)) return;

        for (int i = 0; i < K; i++)
            val[i] = b.val[i];
    }

    inline bool visited()
    {
        return val[0] != -1;
    }
};

namespace sol
{
    const int K = 10;
    const int N = 10005;

    using swords = _swords<K>;

    pair<ii, swords> edges[N];
    int n, m, d, k;

    void read()
    {
        cin >> n >> m >> d >> k;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;

            edges[i] = {{a, b}, swords()};

            for (int j = 0; j < k; j++)
                cin >> edges[i].sec[j];
        }
    }
    
    swords best[N][2];
    swords tmp;

    void solve()
    {
        swords res;

        for (int j = 2; j <= n; j++)
            for (int i = 0; i < 2; i++)
                best[j][i][0] = -1;

        for (int i = 0; i < d; i++)
        {
            bool cur = i % 2, prv = (i + 1) % 2;

            for (int _j = 0; _j < m; _j++)
            {
                int a = edges[_j].fir.fir, b = edges[_j].fir.sec;

                #define push_best(X, Y) \
                if (best[X][prv].visited()) \
                { \
                    for (int j = 0; j < K; j++) \
                        tmp[j] = max(best[X][prv][j], edges[_j].sec[j]); \
                    best[Y][cur].choose(tmp); \
                }

                push_best(a, b);
                push_best(b, a);
            }

            res.choose(best[n][cur]);
        }

        for (int i = 0; i < k; i++)
            cout << res[i] << ' ';
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