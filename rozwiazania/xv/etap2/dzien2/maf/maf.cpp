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

const int N = 1e6+5;
vector<vector<int>> cycles;
vector<int> rg[N];
int nxt[N], dp[N][2], kon[N];
int n;

namespace init
{
    bitset<N> vis;

    void init()
    {
        vector<int> wsk(n+1,0);
        queue<int> q;

        for (int i = 1; i <= n; i++)
        {
            wsk[i] = len(rg[i]);

            if (len(rg[i]) == 0)
                q.push(i);
        }

        while (!q.empty())
        {
            auto acc = q.front();
            q.pop();

            wsk[nxt[acc]]--;
            vis[acc] = true;

            if (wsk[nxt[acc]] == 0)
                q.push(nxt[acc]);

            dp[acc][0] = 0;
            dp[acc][1] = 1;
            kon[acc] = (len(rg[acc]) == 0);

            bool good = true;

            for (auto i : rg[acc])
            {
                if (!vis[i]) continue;
                if (len(rg[i]) == 0) good = false;

                dp[acc][0] += dp[i][1];
                dp[acc][1] += min(dp[i][1], dp[i][0]);
                kon[acc] += kon[i];
            }

            if(len(rg[acc]) == 0) dp[acc][1] = INF;
            dp[acc][0] = (good ? dp[acc][0] : INF);
        }

        for (int i = 1; i <= n; i++)
        {
            if (vis[i]) continue;

            dp[i][0] = 0;
            dp[i][1] = 1;

            for (auto j : rg[i])
            {
                if (!vis[j]) continue;

                kon[i] += kon[j];
                dp[i][0] += dp[j][1];
                dp[i][1] += min(dp[j][1], dp[j][0]);
            }
        }

        vis.reset();

        for (int i = 1; i <= n; i++)
        {
            if (wsk[i] == 0 || vis[i]) continue;

            cycles.push_back({});

            while (!vis[i])
            {
                vis[i] = true;
                cycles.back().push_back(i);
                i = nxt[i];
            }
        }
    }
}

namespace sol
{
    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
        {
            cin >> nxt[i];
            rg[nxt[i]].push_back(i);
        }
    }

    bitset<N> removed;

    int solveMin(vector<int>& cycle)
    {
        if (len(cycle) == 1)
            return dp[cycle.back()][1];

        int r = 0;

        for (auto i : cycle)
        {
            bool one = [&]()
            {
                if (dp[i][0] >= dp[i][1])
                    return true;
                for (auto j : rg[i])
                    if (len(rg[j]) == 0)
                        return true;
                return false;
            }();

            removed[i] = one;
            if (one) r += dp[i][1];
        }

        if (r != 0)
        {
            bool did = removed[cycle[len(cycle) - 1]];

            for (int i = 0; i < len(cycle); i++)
            {
                if (removed[cycle[i]]) 
                {
                    did = true;
                    continue;
                }
                if (!did) continue;

                ii g1{}, g2{};
                int dl{};

                for (int j = i;; j = (j + 1) % len(cycle))
                {
                    if (removed[cycle[j]])
                        break;
                    removed[cycle[j]] = true;

                    if (dl % 2)
                    {
                        g1.fir += dp[cycle[j]][0];
                        g1.sec += dp[cycle[j]][1];
                    }
                    else
                    {
                        g2.fir += dp[cycle[j]][0];
                        g2.sec += dp[cycle[j]][1];
                    }
                    dl++;
                }

                r += min(g1.fir + g2.sec, g1.sec + g2.fir);
            }

            return r;
        }

        if (len(cycle) % 2 == 0)
        {
            ii g1{}, g2{};
            
            for (int i = 0; i < len(cycle); i++)
            {
                if (i&1)
                {
                    g1.fir += dp[cycle[i]][0];
                    g1.sec += dp[cycle[i]][1];
                }
                else
                {
                    g2.fir += dp[cycle[i]][0];
                    g2.sec += dp[cycle[i]][1];
                }
            }

            return min(g1.fir + g2.sec, g1.sec + g2.fir);
        }

        ii g1{}, g2{};

        for (int i = 0; i < len(cycle) - 1; i++)
        {
            if (i % 2 == 0)
            {
                g1.fir += dp[cycle[i]][0];
                g1.sec += dp[cycle[i]][1];
            }
            else
            {
                g2.fir += dp[cycle[i]][0];
                g2.sec += dp[cycle[i]][1];
            }
        }
        g1.fir += dp[cycle[len(cycle) - 1]][0];
        g1.sec += dp[cycle[len(cycle) - 1]][1];   

        int best = INF;

        for (int i = 0; i < len(cycle); i++)
        {
            best = min(best, g1.sec + g2.fir);

            swap(g1, g2);

            g1.fir += dp[cycle[i]][0];
            g1.sec += dp[cycle[i]][1];
            g2.fir -= dp[cycle[i]][0];
            g2.sec -= dp[cycle[i]][1];
        }

        return best;
    }

    int solveMax(vector<int>& cycle)
    {
        int tails = 0;

        for (auto i : cycle)
            tails += kon[i];
        
        return (tails == 0 ? (len(cycle) == 1 ? 0 : -1) : -tails);
    }

    void solve()
    {
        init::init();

        int rmin, rmax;
        rmin = 0, rmax = n;

        for (auto& i : cycles)
        {
            rmin += solveMin(i);
            rmax += solveMax(i);
        }

        cout << rmin << ' ' << rmax << '\n';
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