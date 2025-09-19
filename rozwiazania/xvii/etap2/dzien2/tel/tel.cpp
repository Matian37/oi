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

namespace sol
{
    const int N = 4e4+5;
    vector<int> g[N];
    ll n, m;

    void read()
    {
        cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    ll d1[N], d2[N];

    void bfs(ll* d, int start)
    {
        bitset<N> visited;
        queue<ii> q;
        q.push({start, 0});

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            if (visited[acc.fir])
                continue;
            
            visited[acc.fir] = true;
            d[acc.fir] = acc.sec;

            for (auto i : g[acc.fir])
            {
                if (visited[i])
                    continue;
                q.push({i, acc.sec + 1});
            }
        }

        for (int i = 3; i <= n; i++)
            if (!visited[i])
                d[0]++;
    }
    void solve()
    {
        bfs(d1, 1);
        bfs(d2, 2);

        ll a, b, c, d, e;
        a = b = c = d = 0;

        for (int i = 1; i <= n; i++)
        {
            if (d1[i] == 1)
                a++;
            else if (d1[i] == 2)
                b++;
            if (d2[i] == 1)
                c++;
            else if (d2[i] == 2)
                d++;
        }

        e = n - 2 - a - b - c - d;

        ll r = n * (n - 1) / 2 - m - (n-1-a) - a * (1+c+d) - b * (1 + c) - d - e * (1 + min(a, c));

        cout << r << '\n';
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