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

#define qll(x) ((ll)(x)*(x-1))

const int N = 1e5 + 5;
vector<int> g[N], lg[N];
int n, m;

namespace low
{
    bitset<N> visited;
    int low[N], id[N], sajz[N], cnt, parent[N];

    void dfs(int v, int p)
    {
        visited[v] = true;
        low[v] = id[v] = ++cnt;
        sajz[low[v]] = 1;

        for (auto i : g[v])
        {
            if (i == p) continue;

            if (!visited[i])
                dfs(i, v);
        
            if (low[i] < low[v])
            {
                sajz[low[i]] += sajz[low[v]];
                sajz[low[v]] = 0;
                low[v] = low[i];
            }
        }
    }

    int lgDfs(int v, int p)
    {
        parent[v] = p;

        for (auto i : lg[v])
        {
            if (i == p) continue;

            lgDfs(i, v);

            sajz[v] += sajz[i];
        }

        return sajz[v];
    }


    void init()
    {
        dfs(1, 0);

        for (int i = 1; i <= n; i++)
        {
            for (auto j : g[i])
            {
                if (j < i) continue;
                if (low[i] == low[j]) continue;

                ii ord = {low[i], low[j]};

                if (ord.fir > ord.sec) 
                    swap(ord.fir, ord.sec);
                
                lg[ord.fir].push_back(ord.sec);
                lg[ord.sec].push_back(ord.fir);
            }
        }

        lgDfs(1, 0);
    }
}

namespace sol
{
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
    
    void solve()
    {
        low::init();
    
        for (int i = 1; i <= n; i++)
        {
            ll sum = n - 1, result = 0;

            bool did = false, outside = false;

            for (int j : g[i])
            {
                if (low::low[j] == low::parent[low::low[i]]) continue;

                outside = true;

                if (low::low[j] == low::low[i]) continue;
                
                sum -= low::sajz[low::low[j]];
                result += qll(low::sajz[low::low[j]]);
                did = true;
            }

            if (!outside)
                result = qll(n - 1);
            else if (!did)
            {
                result += qll(low::sajz[low::low[i]] - 1);
                result += qll(n - low::sajz[low::low[i]]);
            }
            else
                result += qll(sum);

            result = qll(n) - result;

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