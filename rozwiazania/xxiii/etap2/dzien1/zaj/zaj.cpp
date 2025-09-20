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

namespace sol
{
    const int N = 15005;

    int t1[N], t2[N];

    int n, m;

    void read()
    {
        cin >> n >> m;

        map<int,int> id;

        for (int i = 1; i <= n; i++)
            {cin >> t1[i]; id[t1[i]] = 1;}
        
        for (int i = 1; i <= m; i++)
            {cin >> t2[i]; id[t2[i]] = 1;}
        
        int lic = 0;

        for (auto& i : id)
            i.second = lic++;

        for (int i = 1; i <= n; i++)
            t1[i] = id[t1[i]];
        
        for (int i = 1; i <= m; i++)
            t2[i] = id[t2[i]];

    }

    vector<int> wstp1[2 * N], wstp2[2 * N];
    int dp[N][2], lt[N], last1[N], last2[N];

    void solve()
    {
        for (int i = 1; i <= m; i++)
        {
            if (wstp2[t2[i]].size() == 0) last2[i] = 0;
            else last2[i] = wstp2[t2[i]].back();
            wstp2[t2[i]].push_back(i);
        }
        for (int i = 1; i <= n; i++)
        {
            if (wstp1[t1[i]].size() == 0) last1[i] = 0;
            else last1[i] = wstp1[t1[i]].back();
            wstp1[t1[i]].push_back(i);
        }

        int best = 0;

        for (int i = 1; i <= n; i++)
        {
            bool acc = i & 1, prev = !acc;

            for (int j = 1; j <= m; j++)
            {
                dp[j][acc] = max(dp[j][prev], dp[j - 1][acc]);

                if (t1[i] == t2[j])
                {
                    if (last1[i] != 0 && last2[j] != 0)
                        dp[j][acc] = max(dp[j][acc], lt[j] + 2);
                    lt[j] = dp[max(0, last2[j] - 1)][prev];
                }

                best = max(best, dp[j][acc]);
            }
        }

        cout << best << '\n';
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