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
    const int N = 1e6+5;
    int n;

    ull id[N];

    void init()
    {
        mt19937_64 r64(timeNow());

        for (int i = 1; i <= n; i++)
            id[i] = uniform_int_distribution<ull>(1,ULLONG_MAX)(r64);
    }

    ull h[N];
    vector<int> g[N];

    void read()
    {
        cin >> n;
        init();

        for (int i = 1; i <= n; i++)
        {
            int k;
            cin >> k;

            g[i].reserve(k);

            for (int j = 0; j < k; j++)
            {
                int c;
                cin >> c;
                g[i].push_back(c);
                h[i] ^= id[c];
            }
        }
    }

    vector<int> city[N];
    int r[N];

    int join(int a, int b)
    {
        a = r[a], b = r[b];

        if (r[a] == r[b])
            return 0;
        
        if (len(city[a]) < len(city[b]))
            swap(a,b);
        
        for (auto i : city[b])
        {
            r[i] = a;
            city[a].push_back(i);
        }
        return 1;
    }

    set<ii> edges;
    map<int,int> norm;

    void solve()
    {
        if (n == 1)
        {
            cout << "1\n1\n";
            return;
        }

        for (int i = 1; i <= n; i++)
            r[i] = i, city[i].push_back(i);

        int unq = n;

        for (int i = 1; i <= n; i++)
            for (auto j : g[i])
                if ((h[j] ^ id[i]) == (h[i] ^ id[j]))
                    unq -= join(i,j);


        for (int i = 1; i <= n; i++)
        {
            for (auto j : g[i])
            {
                if (r[j] < r[i]) continue;

                if ((h[j] ^ id[i]) != (h[i] ^ id[j]))
                    edges.insert({r[i], r[j]});
            }
        }

        for (int i = 1; i <= n; i++)
            norm[r[i]];
        int lic = 0;
        for (auto& i : norm)
            i.second = ++lic;

        if (unq == 1)
        {
            cout << "2 \n";
            for (int i = 1; i < n; i++)
                cout << "1 ";
            cout << "2\n";
            cout << "1 2\n";
            return;
        }

        cout << unq << '\n';
        for (int i = 1; i <= n; i++)
            cout << norm[r[i]] << ' ';
        cout << '\n';
        for (auto i : edges)
            cout << norm[i.fir] << ' ' << norm[i.sec] << '\n';
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