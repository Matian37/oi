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
#define isize(x) (int)(x.size())
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
    const int N = 3e3 + 5;

    vector<int> b3[] = {{}, {0b001, 0b010, 0b100}, {0b011, 0b101, 0b110}, {0b111}};

    uint dp[N][N][4];
    vector<int> f[N], g[N];
    int h[N];
    int n, m, k;

    void hdfs(int v, int p)
    {
        int pos = 0;

        for (int i = 0; i < isize(f[v]); i++)
        {
            if (f[v][i] == p) pos = i;
            else hdfs(f[v][i], v);
        }

        swap(f[v][pos], f[v].back());
    }

    int z0;

    void read()
    {
        cin >> n >> m >> k;

        f[1].push_back(0);
        f[0].push_back(1);

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            f[a].push_back(b);
            f[b].push_back(a);
        }

        hdfs(1, 0);

        z0 = isize(f[1]) - 1;

        for (int i = 0; i < m - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    inline int seeParent(int v, int x, vector<int> *gr)
    {
        if (isize(gr[v]) <= x) return -1;
        return gr[v][x];
    }

    inline int getParent(int v, int p, vector<int> *gr)
    {
        for (int i = 0; i < isize(gr[v]); i++)
            if (gr[v][i] == p)
                return i;
        return 3;
    }

    int parents[4];

    void solveVert(int v, int w, int gnr)
    {
        int Sg = isize(g[w]) - (gnr != 3), Sf = isize(f[v]) - 1;
        if (Sf > Sg) return;

        if (gnr != 3) 
        {
            swap(g[w][gnr], g[w].back());
            swap(parents[gnr], parents[isize(g[w]) - 1]);
        }

        #define dpacc dp[v][w][gnr]
        #define dp(X,Y) dp[f[v][X]][g[w][Y]][parents[Y]]
        
        switch(Sg)
        {
            case 1:
                dpacc = (dpacc + dp(0,0)) % k;
                break;
            case 2:
                if (Sf == 1)
                {
                    dpacc = (dpacc + dp(0,0) + dp(0, 1)) % k;
                    break;
                }

                dpacc = (int)((dpacc + ((ll)dp(0, 0) * dp(1, 1) + (ll)dp(0, 1) * dp(1, 0))) % k);
                break;
            default:
                if (Sf == 1)
                {
                    dpacc = (int)(((ll)dpacc + dp(0, 0) + dp(0, 1) + dp(0, 2)) % k);
                    break;
                }
                else if (Sf == 2)
                {
                    dpacc = (int)(((ll)dpacc + (ll)dp(0,0) * dp(1,1)
                                             + (ll)dp(1,0) * dp(0,1)
                                             + (ll)dp(0,0) * dp(1,2)
                                             + (ll)dp(1,0) * dp(0,2)
                                             + (ll)dp(0,1) * dp(1,2)
                                             + (ll)dp(1,1) * dp(0,2)) % k); 
                    break;
                }

                vector<int> vt = {0, 1, 2};

                do
                {
                    ll vall = 1;

                    for (int i = 0; i < 3; i++)
                        vall = (vall * dp(i, vt[i])) % k;
                    dpacc = (int)((dpacc + vall) % k);
                } while (next_permutation(all(vt)));
                break;
        }
        
        if (gnr != 3) 
        {
            swap(g[w][gnr], g[w].back());
            swap(parents[gnr], parents[isize(g[w]) - 1]);
        }

        #undef dpacc
        #undef dp
    }
    
    void dfs(int v, int pnr)
    {
        for (auto i : f[v])
        {
            if (i == seeParent(v, pnr, f))
                continue;
            dfs(i, isize(f[i]) - 1);
        }

        if (f[v].size() == 1)
        {
            for (int i = 1; i <= m; i++)
                for (int j = 0; j < isize(g[i]); j++)
                    dp[v][i][j] = 1;
            return;
        }

        for (int i = 1; i <= m; i++)
        {
            for (int j = 0; j < isize(g[i]); j++)
                parents[j] = getParent(g[i][j], i, g);

            for (int j = 0; j < isize(g[i]); j++)
                solveVert(v, i, j);
            if (v == 1)
                solveVert(v, i, 3);
        }
    }

    int solve()
    {
        if (k == 1) 
            return 0;
        if (n == 1)
            return m % k;
        if (n == 2)
            return (2 * (m - 1)) % k;

        dfs(1, z0);

        int r = 0;

        for (int i = 1; i <= m; i++)
            r = (r + dp[1][i][3]) % k;
        return r;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    cout << sol::solve() << '\n';
}