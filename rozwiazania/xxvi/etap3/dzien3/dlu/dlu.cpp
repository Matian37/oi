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

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007ULL
#define MOD2 1000000403ULL
#define MOD3 1000000787ULL
#define MOD4 1000001447ULL

#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

struct Hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    const int N = 1e5 + 5;
    const int K = 100;
    int k = K;

    vector<int> g[N];

    int dist[N][K];
    int n, m, p;

    void read()
    {
        cin >> n >> m >> p;

        k = min(n, k);

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int visited[N], token = 0;

    void bfs(int start, int ind)
    {
        ++token;
        queue<ii> q;

        q.push({start, 0});

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            if (visited[acc.fir] == token) continue;

            visited[acc.fir] = token;
            dist[acc.fir][ind] = acc.sec;

            for (auto i : g[acc.fir])
            {
                if (visited[i] == token) continue;
                q.push({i, acc.sec + 1});
            }   
        }
    }
    
    vector<int> kan, chosen;

    inline uint getRandom(uint a, uint b, mt19937& rng)
    {
        return a + (uint)rng() % (b - a + 1);
    }

    void preprocess()
    {
        kan.resize(n);
        chosen.reserve(k);

        iota(all(kan), 1);

        mt19937 rng((ull)timeNow() ^ (ull)(make_unique<char>().get()));

        for (int i = 0; i < k; i++)
        {
            int a = getRandom(0, isize(kan) - 1, rng);

            chosen.push_back(kan[a]);
            bfs(chosen.back(), i);

            kan.erase(kan.begin() + a);
        }
    }

    void solve()
    {
        preprocess();

        while (p--)
        {
            int a, b;
            cin >> a >> b;

            int result = INF;

            for (int i = 0; i < k; i++) 
                result = min(result, dist[a][i] + dist[b][i]);
            
            cout << result << '\n';
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