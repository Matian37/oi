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
    const int N = 5e5 + 5;
    vector<int> g[N], rg[N];
    int n, m;

    void read()
    {
        cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            rg[b].push_back(a);
        }
    }

    vector<int> ord;
    int wsk[N], postr[N];
    
    void topsort()
    {
        queue<int> q;

        ord.reserve(n);

        for (int i = 1; i <= n; i++)
        {
            wsk[i] = len(rg[i]);

            if (wsk[i] == 0)
                q.push(i);
        }

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            postr[acc] = len(ord);
            ord.push_back(acc);

            for (auto i : g[acc])
            {
                wsk[i]--;

                if (wsk[i] == 0)
                    q.push(i);
            }
        }
    }

    int dist[N][2];
    // left, right

    void side(int start, int end, int inc, bool which, vector<int>* gr)
    {
        for (int i = start; i != end; i += inc)
        {
            auto v = ord[i];

            for (auto j : gr[v])
                dist[v][which] = max(dist[v][which], dist[j][which] + 1);
        }
    }

    int get(set<ii, greater<ii>>& s, int rm)
    {
        auto it = s.begin();

        while (it != s.end())
        {
            if (it->sec == rm) 
                it++;
            else 
                return it->fir;
        }
        return 0;
    }

    vector<ii> jump[N];

    void solve()
    {
        topsort();

        side(0, n - 1, 1, 0, rg); // 0
        side(n - 1, 0, -1, 1, g); // 1

        #define FL 0
        #define FR 1

        set<ii, greater<ii>> values, jumps;

        for (int i = 0; i < n; i++)
            values.insert({dist[ord[i]][FR], ord[i]});
        
        int best = INT32_MAX;
        int vert;

        for (int i = 0; i < n; i++)
        {
            auto v = ord[i];

            while (jump[v].size())
            {
                jumps.erase(jump[v].back());
                jump[v].pop_back();
                jumps.insert({dist[v][FL], v});
            }

            values.erase({dist[v][FR], v});

            int val = max(get(values, ord[i]), get(jumps, ord[i]));

            #ifdef LOCAL
                assert(val >= 0);
            #endif

            if (best > val)
                best = val, vert = v;

            for (auto j : g[v])
            {
                jumps.insert({dist[v][FL] + 1 + dist[j][FR], j});
                jump[j].push_back({dist[v][FL] + 1 + dist[j][FR], j});
            }
        }

        cout << vert << ' ' << best << '\n';
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