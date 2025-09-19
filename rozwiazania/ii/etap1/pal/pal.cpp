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

struct hashfn
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};

namespace sol
{
    const int N = 2e3 + 5;
    
    ii dp[N], prv[N];
    string s;

    bool isPalindrom(int a, int b)
    {
        while (a < b)
        {
            if (s[a] != s[b]) return false;
            a++;
            b--;
        }

        return true;
    }

    int n;

    void read()
    {
        cin >> s;

        n = isize(s);

        s = '_' + s;
    }
    
    void solve()
    {
        dp[0] = {0,0};

        for (int i = 1; i <= n; i++)
            dp[i] = {INF, -INF};

        for (int i = 1; i <= n; i++)
        {
            for (int j = i - 1; j >= 1; j -= 2)
            {
                if (!isPalindrom(j, i)) continue;

                if (dp[i].fir > dp[j - 1].fir + 1)
                {
                    dp[i].fir = dp[j - 1].fir + 1;
                    prv[i].fir = j - 1;
                }

                if (dp[i].sec < dp[j - 1].sec + 1)
                {
                    dp[i].sec = dp[j - 1].sec + 1;
                    prv[i].sec = j - 1;
                }
            }
        }

        if (dp[n].fir == INF)
        {
            cout << "NIE\n";
            return;
        }

        vector<string> result;

        int pos = n;

        while (pos != 0)
        {
            result.push_back(s.substr(prv[pos].fir + 1,pos-(prv[pos].fir + 1)+1));
            pos = prv[pos].fir;
        }

        for (int i = isize(result) - 1; i >= 0; i--)
            cout << result[i] << ' ';
        cout << '\n';

        vector<string> result2;

        pos = n;

        while (pos != 0)
        {
            result2.push_back(s.substr(prv[pos].sec + 1,pos-(prv[pos].sec + 1)+1));
            pos = prv[pos].sec;
        }

        for (int i = isize(result2) - 1; i >= 0; i--)
            cout << result2[i] << ' ';
        cout << '\n';
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