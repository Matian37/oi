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
    string s;
    int n;

    void read()
    {
        cin >> n >> s;

        for (auto& i : s)
            if (i == 'S')
                i = 'A';
    }

    const int N = 1e6+5;

    int prefA[N], prefB[N], prefC[N];

    bool isGood(int a, int b)
    {
        int _a = prefA[b] - prefA[a - 1],
            _b = prefB[b] - prefB[a - 1], 
            _c = prefC[b] - prefC[a - 1];
        return (_a != _b && _b != _c && _a != _c);
    }

    void solve()
    {
        if (n <= 2)
        {
            cout << "NIE\n";
            return;
        }

        for (int i = 1; i <= n; i++)
        {
            prefA[i] = prefA[i - 1];
            prefB[i] = prefB[i - 1];
            prefC[i] = prefC[i - 1];

            switch (s[i - 1])
            {
                case 'A':
                    prefA[i]++;
                    break;
                case 'B':
                    prefB[i]++;
                    break;
                case 'C':
                    prefC[i]++;
                    break;
                default:
                    cerr << "shit";
                    break;
            }
        }

        int best = 0;

        for (int i = 1; i <= 3; i++)
            for (int j = i; j <= n; j++)
                if (isGood(i,j))
                    best = max(best,j-i+1);

        for (int i = n; i >= n - 4; i--)
            for (int j = i; j >= 1; j--)
                if (isGood(j,i))
                    best = max(best,i-j+1);
        
        cout << (best == 0 ? "NIE" : to_string(best)) << '\n';
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