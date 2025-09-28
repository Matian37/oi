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
#define int128 __int128_t;
#define uint128 __uint128_t;

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007LL
#define MOD2 1000000403LL
#define MOD3 1000000787LL
#define MOD4 1000001447LL

#define INF (ushort)((1 << 16 )- 1);
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
    const int N  = 5e3 + 5;

    // a < b -> 0
    // a > b -> 1

    ushort canit[N][2];

    ushort can[N][N];
    vector<ushort> g[N];

    int n, m, k;

    inline ushort& ask(int a, int b, int c)
    {
        if (a == b) return canit[a][c % 2];
        if (a > b) swap(a,b);
        return c % 2 ? can[b][a] : can[a][b];
    }

    void read()
    {
        cin >> n >> m >> k;

        for (int i = 1; i <= n; i++)
            canit[i][0] = canit[i][1] = INF;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                can[i][j] = INF;

        for (int i = 0; i < m; i++)
        {
            ushort a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int visited[N][2];
    int token;

    struct info
    {
        ushort v, t;
    };

    void bfs(int start)
    {
        ++token;

        queue<info> q;

        q.push(info{(ushort)start, 0});

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            ask(start, acc.v, acc.t % 2) = acc.t;

            acc.t++;

            for (auto i : g[acc.v])
            {
                #define vis visited[i][acc.t % 2]

                if (vis == token)
                    continue;

                q.push({i, acc.t});

                vis = token;
            }
        }
    }

    void init()
    {
        for (int i = 1; i <= n; i++)
            bfs(i);
    }
    
    void solve()
    {
        init();

        while (k--)
        {
            int a, b, d;
            cin >> a >> b >> d;

            if (a == b && g[a].size() == 0)
            {
                cout << "NIE\n";
                continue;
            }

            int best = ask(a, b, d % 2);

            cout << (best == (1 << 16) - 1 || best > d ? "NIE\n" : "TAK\n");
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