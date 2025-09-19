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
    const int N = 1e6+5;
    vector<int> ind[26];
    string s;
    int n;

    void read()
    {
        cin >> n >> s;

        for (int i = 0; i < n; i++)
            ind[s[i] - 'a'].push_back(i);
    }

    bool t[N];
    int end;

    inline void calc(char big, char small)
    {
        end = 1;

        int v = big - 'a', u = small - 'a';
        int i = 0, j = 0;

        while (true)
        {
            if (ind[v][i] < ind[u][j])
            {
                t[end++] = true, i++;
                if (i == len(ind[v])) break;
            }
            else
            {
                t[end++] = false, j++;
                if (j == len(ind[u])) break;
            }
        }

        while (i < len(ind[v])) t[end++] = true, i++;
        while (j < len(ind[u])) t[end++] = false, j++;
    }

    int solveCase(char big, char small)
    {
        if (big == small) 
            return 0;
        if (len(ind[big - 'a']) == 0 || len(ind[small - 'a']) == 0) 
            return 0;
        calc(big, small);

        int r = 0, dp0 = 0, dp1 = -INF, rdp0 = 0, rdp1 = -INF;

        for (int i = 1; i < end; i++)
        {
            if (t[i]) dp0++, dp1++, rdp1 = max(rdp0, rdp1) - 1, rdp0 = 0;
            else dp1 = max(dp0, dp1) - 1, dp0 = 0, rdp0++, rdp1++;
            r = max(r, dp1);
            r = max(r, rdp1);
        }

        return r;
    }
    
    void solve()
    {
        int r = 0;

        for (int i = 0; i < 26; i++)
            for (int j = i + 1; j < 26; j++)
                r = max(r, solveCase('a' + i, 'a' + j));
        cout << r << '\n';
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