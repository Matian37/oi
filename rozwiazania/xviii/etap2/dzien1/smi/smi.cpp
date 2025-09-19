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

// best primes in te galaxy
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
    const int N = 1e5+5;

    struct info
    {
        int first;
        list<info>::iterator second;
    };

    list<info> g[N];
    int n, m, rm;

    void read()
    {
        cin >> n >> m;

        for (int i = 0; i < m; i++)
        {
            int a, b;
            bool c, d;
            cin >> a >> b >> c >> d;

            if (c ^ d)
            {
                g[a].push_back({b, g[b].end()});
                g[b].push_back({a, prev(g[a].end())});
                g[a].back().second = prev(g[b].end());
            }
            else rm++;
        }
    }

    stack<int> el;
    vector<int> result;
    vector<vector<int>> cycles;
    int visited[N], token;

    pair<bool,bool> dfs(int v, int p)
    {
        visited[v] = token;
        el.push(v);

        for (auto i : g[v])
        {
            if (i.fir == p) continue;
            if (visited[i.fir] == token)
            {
                auto edg = *i.sec;

                g[i.fir].erase(i.sec);
                g[v].erase(edg.sec);
                rm++;

                cycles.push_back({i.fir});
                while (el.top() != i.fir)
                {
                    cycles.back().push_back(el.top());
                    el.pop();
                }
                cycles.back().push_back(i.fir);

                return {true, true};
            }

            auto val = dfs(i.fir, v);

            if (val.sec) 
            {
                auto edg = *i.sec;

                g[i.fir].erase(i.sec);
                g[v].erase(edg.sec);
                rm++;

                if (cycles.back().back() == v)
                    val.sec = false;
            }
            if (val.fir) return val;
        }

        el.pop();
        return {false, false};
    }

    int getCycle(int v)
    {
        while (el.size()) el.pop();
        result.clear();

        ++token;
        if (!dfs(v, v).fir)
            return 0;
        return len(cycles.back()) - 1;
    }
    
    void solve()
    {
        int s = 0;

        for (int i = 1; i <= n; i++)
        {
            int c;

            do
            {
                c = getCycle(i);
                s += c;

                if (s > 5 * m)
                {
                    cout << "NIE\n";
                    return;
                }
            } while (c != 0);
        }

        if (rm != m)
        {
            cout << "NIE\n";
            return;
        }

        cout << len(cycles) << '\n';

        
        for (auto& i : cycles)
        {
            cout << len(i) - 1 << ' ';

            for (auto j : i)
                cout << j << ' ';
            cout << '\n';
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