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
    const int N = 4e2+5;
    vector<pair<int,char>> g[N], rg[N];
    char value[N][N];
    int n, m;

    vector<ii> edges;

    void read()
    {
        cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            char c;
            cin >> a >> b >> c;
            edges.push_back({a,b});
            g[a].push_back({b,c});
            rg[b].push_back({a,c});
            value[a][b] = c;
        }
    }

    int dp[N][N][27];
    int parent[N][N][27];
    
    // abba

    struct info
    {
        int a, b, c;
    };

    void bfs()
    {
        queue<info> q;

        for (int j = 1; j <= n; j++)
            dp[j][j][26] = 0,
            parent[j][j][26] = j,
            q.push({j,j,26});          

        for (auto [u,w] : edges)
            dp[u][w][26] = 1,
            parent[u][w][26] = u,
            q.push({u,w,26});

        while (len(q))
        {
            auto acc = q.front();
            q.pop();

            int val = dp[acc.a][acc.b][acc.c];

            if (acc.c != 26)
            {
                for (auto i : g[acc.b])
                {
                    if (i.sec - 'a' != acc.c) continue;
                    if (dp[acc.a][i.fir][26] != INF) continue;
                    q.push({acc.a, i.fir, 26});
                    dp[acc.a][i.fir][26] = val + 1;
                    parent[acc.a][i.fir][26] = acc.b;
                }
            }
            else
            {
                for (auto i : rg[acc.a])
                {
                    if (dp[i.fir][acc.b][i.sec-'a'] != INF)
                        continue;
                    q.push({i.fir, acc.b, i.sec-'a'});
                    dp[i.fir][acc.b][i.sec-'a'] = val + 1;
                    parent[i.fir][acc.b][i.sec-'a'] = acc.a;
                }
            }
        }
    }

    void solve()
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 0; k < 27; k++)
                    dp[i][j][k] = INF;
        bfs();

        int d;
        cin >> d;

        int a, b, c;
        cin >> a;

        for (int i = 1; i < d; i++, a = c)
        {
            cin >> b;
            c = b;

            if (dp[a][b][26] == INF)
            {
                cout << -1 << '\n';
                continue;
            }

            string left = "", right = "";
            int stan = 26;

            cout << dp[a][b][26] << ' ';

            while (a != b)
            {
                int nstan;

                if (stan != 26)
                {
                    left += value[a][parent[a][b][stan]];
                    nstan = 26;
                    a = parent[a][b][stan];
                }
                else
                {
                    right += value[parent[a][b][stan]][b];
                    nstan = value[parent[a][b][stan]][b]-'a';
                    b = parent[a][b][stan];
                }

                stan = nstan;
            }

            reverse(all(right));
            cout << left + right << '\n';
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