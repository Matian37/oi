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
#define INFLL 1'000'000'000'000'000'0000ULL
#define INFULL 1'000'000'000'000'000'0000ULL
#define timeNow() (chrono::high_resolution_clock::now().time_since_epoch().count())
#define all(x) x.begin(),x.end()
#define len(x) (int)(x.size())
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second
#define self(x,y,z) x = z(x,y)

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
    struct jakimcudemcpp17niemaunit128irekuremcjazuzywa200mbpamieci
    {
        string a = "0";

        void operator+=(ll x)
        {
            string b = to_string(x);
            reverse(all(b));

            while (b.size() < a.size())
                b.push_back('0');
            while (b.size() > a.size())
                a.push_back('0');
            
            int rem = 0;

            for (int i = 0; i < len(b); i++)
            {
                int sum = a[i] - '0' + b[i] - '0' + rem;
                rem = sum / 10;
                a[i] = ('0' + sum % 10);
            }

            if (rem != 0)
                a.push_back(char(rem + '0'));

            while (a.back() == '0' && len(a) > 1)
                a.pop_back();
        }
    };

    const int N = 1'000'005;
    vector<int> g[N];
    int n;
    ll wg[N];
    ull sum;

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> wg[i];
        
        for (int i = 1; i <= n; i++)
        {
            int c;
            cin >> c;
            wg[i] -= c;
            sum += wg[i];
        }

        for (int i = 2; i <= n; i++)
        {
            int a, b;
            cin >> a >> b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int sajz[N], nr[N], parent[N];
    int token;
    jakimcudemcpp17niemaunit128irekuremcjazuzywa200mbpamieci r;

    void initDfs(int v, int p)
    {
        sajz[v] = 1;
        parent[v] = p;

        for (auto i : g[v])
        {
            if (i == p) continue;
            initDfs(i, v);
            sajz[v] += sajz[i];
        }

        nr[++token] = v;
    }

    void compute(int v)
    {
        sort(all(g[v]), [](const int& a, const int& b)
        {
            return wg[a] < wg[b];
        });

        int p = parent[v];
        ll q = 0;

        for (auto i : g[v])
        {
            if (i == p) continue;

            wg[i] += q;

            if (wg[i] >= 0)
            {
                r += (wg[i] * sajz[i]);
                wg[v] += wg[i];
                wg[i] = 0;
                continue;
            }

            wg[v] -= -wg[i] * len(g[v]);
            wg[p] += -wg[i];
            q += -wg[i];
            r += (-wg[i]);
            wg[i] = 0;
        }
    }

    void solve()
    {
        if (sum != 0)
        {
            cout << "NIE\n";
            return;
        }

        initDfs(1, 0);

        for (int i = 1; i <= n; i++)
            compute(nr[i]);
        
        cout << "TAK\n";
        reverse(all(r.a));
        cout << r.a << '\n';
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