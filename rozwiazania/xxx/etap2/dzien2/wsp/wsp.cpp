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
    const int N = 1e5+5;
    vector<int> g[N];
    int val[N], n, m, k;

    void read()
    {
        cin >> n >> m >> k;

        for (int i = 1; i <= n; i++)
            cin >> val[i];
        
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
        }
    }

    ull unq[1<<9][2], sum[1<<9][2];

    #define p2(x) (1<<(x))

    void solve()
    {
        stack<ull> solves;

        for (int i = n; i >= 1; i--)
        {
            bool curr = i % 2, last = !curr;
            int stan = 0;

            for (auto j : g[i]) stan += p2(k-(j-i-1));

            for (int j = 0; j < p2(k+1); j += 2)
                sum[j>>1][curr] = sum[j][last],
                unq[j>>1][curr] = unq[j][last];
            for (int j = 0; j < p2(k+1); j += 2)
                sum[p2(k) + (j>>1)][curr] = sum[stan|j][last] + val[i],
                unq[p2(k) + (j>>1)][curr] = sum[p2(k)][curr] + sum[j][last] - sum[p2(k) + (j>>1)][curr];

            solves.push(sum[p2(k)][curr]);
        }

        while(len(solves))
        {
            cout << solves.top() << '\n';
            solves.pop();
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