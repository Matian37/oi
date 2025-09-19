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

#define INF 1'000'000'000
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

struct Hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

const int N = 5e5 + 5;

vector<int> g[N], rg[N];
int wsk[N];
int n, m;

namespace scc
{
    vector<int> _g[N], _rg[N];
    int _n, _m;

    void read()
    {
        cin >> _n >> _m;

        for (int i = 0; i < _m; i++)
        {
            int a, b;
            cin >> a >> b;
            _g[a].push_back(b);
            _rg[b].push_back(a);
        }
    }

    int scc[N], visited[N], token, cnt;
    vector<int> vert;
    
    void dfs(int v)
    {
        visited[v] = token;

        for (auto i : _g[v])
        {
            if (visited[i] == token) continue;
            dfs(i);
        }

        vert.push_back(v);
    }

    void checkDfs(int v)
    {
        scc[v] = cnt;

        for (auto i : _rg[v])
            if (scc[i] == 0)
                checkDfs(i);
    }

    void calculate()
    {
        ++token;

        for (int i = 1; i <= _n; i++)
            if (visited[i] != token)
                dfs(i);

        for (; vert.size(); vert.pop_back())
        {
            auto acc = vert.back();

            if (scc[acc] != 0) continue;

            ++cnt;
            checkDfs(acc);
        }

        n = cnt;

        set<ii> edges;

        for (int i = 1; i <= _n; i++)
        {
            for (auto j : _g[i])
            {
                if (scc[i] == scc[j]) continue;

                int v = scc[i], w = scc[j];
                if (v > w) swap(v, w);

                if (edges.find({v, w}) != edges.end()) continue;

                edges.insert({v, w});
                m++;

                g[scc[i]].push_back(scc[j]);
                rg[scc[j]].push_back(scc[i]);
            }
        }
    }
}

namespace sol
{
    int id[N];
    vector<int> ord;

    void topsort()
    {
        ord.reserve(n + 1);
        ord.push_back(0);

        queue<int> q;

        for (int i = 1; i <= n; i++)
        {
            wsk[i] = rg[i].size();

            if (wsk[i] == 0) q.push(i);
        }

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            id[acc] = isize(ord);
            ord.push_back(acc);

            for (auto i : g[acc])
            {
                wsk[i]--;
                if (wsk[i] == 0) q.push(i);
            }
        }
    }

    int bd[N];
    bool goodSCC[N];

    void solve()
    {
        topsort();

        for (int i = 1; i <= n; i++)
        {
            int v = n + 1;

            for (auto j : g[ord[i]]) v = min(v, id[j]);

            if (v > i + 1) bd[i + 1]++, bd[v]--;

            v = 0;

            for (auto j : rg[ord[i]]) v = max(v, id[j]);

            if (v < i - 1) bd[i]--, bd[v + 1]++;
        }

        vector<int> sol;

        for (int i = 1; i <= n; i++)
        {
            bd[i] += bd[i - 1];

            if (bd[i] == 0) 
                goodSCC[ord[i]] = true;
        }

    for (int i = 1; i <= scc::_n; i++)
        if (goodSCC[scc::scc[i]])
            sol.push_back(i);

        cout << sol.size() << '\n';

        for (auto i : sol)
            cout << i << ' ';
        cout << '\n';
    }
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    scc::read();
    scc::calculate();
    sol::solve();
}