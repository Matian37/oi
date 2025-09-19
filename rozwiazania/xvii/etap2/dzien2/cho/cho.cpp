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
#define len(x) (int)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
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

const int N = 2e2 + 5;

struct matrix
{
    ll t[N][N], tmp[N][N];
    int n, m;

    void operator*=(matrix& b)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                tmp[i][j] = INFLL;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                for (int k = 0; k < m; k++)
                    tmp[i][j] = min(tmp[i][j], t[i][k] + b.t[k][j]);
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < b.m; j++)
                t[i][j] = tmp[i][j];
    }
};

namespace sol
{
    string t[N];
    vector<ii> hs[N], rhs[N];
    int n, m;

    void read()
    {
        cin >> n >> m;

        for (int i = 0; i < n; i++)
            cin >> t[i];
    }

    ll p;

    void init()
    {
        mt19937 rng(timeNow() ^ (ull)make_unique<char>().get());
        p = uniform_int_distribution<int>(27, MOD1-2)(rng);

        for (int i = 0; i < n; i++)
        {
            pll h = {0,0};

            for (int j = 0; j < len(t[i]); j++)
            {
                #define chuj(x, y) h.x = (h.x * p + (t[i][j] - 'a' + 1)) % y

                chuj(fir, MOD1);
                chuj(sec, MOD2);

                hs[i].push_back(h);

                #undef chuj
            }

            h = {0,0};

            pll pot = {1,1};

            for (int j = len(t[i]) - 1; j >= 0; j--)
            {
                #define mk(x, y) h.x = (h.x + (t[i][j] - 'a' + 1) * pot.x) % y

                mk(fir, MOD1);
                mk(sec, MOD2);

                pot.fir = (pot.fir * p) % MOD1;
                pot.sec = (pot.sec * p) % MOD2;

                rhs[i].push_back(h);

                #undef mk
            }
        }
    }
    
    int dist(int a, int b)
    {
        int d = min(len(t[a]), len(t[b])) - (a == b);

        for (int i = d - 1; i >= 0; i--)
        {
            if (rhs[a][i] != hs[b][i])
                continue;
            return len(t[b]) - (i + 1);
        }
        return len(t[b]);
    }

    void solve()
    {
        init();

        matrix g, r;
        g.n = g.m = n + 1;
        r.m = n + 1, r.n = 1;

        for (int i = 0; i < n; i++)
            r.t[0][i] = INFLL;
        r.t[0][n] = 0;

        for (int i = 0; i <= n; i++)
        {
            g.t[n][i] = len(t[i]);
            g.t[i][n] = INFLL;
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                g.t[i][j] = dist(i, j);
        
        //m++;

        while (m != 0)
        {
            if (m % 2)
                r *= g;
            g *= g;
            m /= 2;
        }

        ll path = INFLL;

        for (int i = 0; i < n; i++)
            path = min(path, r.t[0][i]);
        cout << path << '\n';
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