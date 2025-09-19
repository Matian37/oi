//
// Mateusz Pietrowcow
//
 
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

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
#define lenl(x) (ll)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) x = z(x,y)

template <typename X, typename Y, typename Z>
using gp_hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using cc_hashmap = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
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

namespace sol
{
    vector<int> g[N];
    bitset<N> isAgent;
    int n, k;

    void read()
    {
        cin >> n >> k;

        for (int i = 0; i < k; i++)
        {
            int c;
            cin >> c;
            isAgent[c] = true;
        }

        for (int i = 1; i < n; i++)
        {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int dp[N][3];
    #define CHILL 0
    #define UP 1
    #define DOWN 2

    void dfs(int v, int p)
    {
        int sum = 0;

        for (auto i : g[v])
        {
            if (i == p) continue;
            dfs(i, v);
            sum += dp[i][CHILL];
        }

        if (isAgent[v])
        {
            dp[v][DOWN] = -INF;
            dp[v][UP] = dp[v][CHILL] = sum;

            for (auto i : g[v])
                if (i != p)
                    self(dp[v][CHILL], sum - dp[i][CHILL] + dp[i][DOWN] + 1, max);
        }
        else
        {
            dp[v][UP] = -INF;
            dp[v][DOWN] = dp[v][CHILL] = sum;

            int best_up = -1, best_down = -1;

            for (auto i : g[v])
            {
                if (i == p) continue;
                
                self(dp[v][UP], sum - dp[i][CHILL] + dp[i][UP] + 1, max);
                self(dp[v][DOWN], sum - dp[i][CHILL] + dp[i][DOWN] + 1, max);
                self(dp[v][CHILL], sum - dp[i][CHILL] + dp[i][UP] + 1, max);

                if (best_up != -1)
                {
                    int val = sum - dp[i][CHILL] - dp[best_up][CHILL] + dp[i][DOWN] + dp[best_up][UP] + 2;
                    self(dp[v][CHILL], val, max);

                    val = sum - dp[i][CHILL] - dp[best_down][CHILL] + dp[i][UP] + dp[best_down][DOWN] + 2;
                    self(dp[v][CHILL], val, max);
                }

                if (best_up == -1) best_up = best_down = i;
                else
                {
                    #define f(x, y) (dp[x][y] - dp[x][CHILL])

                    if (f(i, DOWN) > f(best_down, DOWN)) 
                        best_down = i;
                    if (f(i, UP) > f(best_up, UP))
                        best_up = i;
                }
            }
        }
    }
    
    void solve()
    {
        dfs(1, 0);
        cout << 2 * (n - k) - dp[1][CHILL] << '\n';
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