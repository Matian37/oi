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
#define inRange(x,a,b) (a <= x && x <= b)
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

const int L = 1e2+5;
const int N = 1e3+5;

pll power[L];
ll p;

struct hss
{
    pll h;
    int t[L], n;

    void update(int x, char c)
    {
        int diff = ((c-'a'+1)-t[x]);

        t[x] += diff;

        #define doh(pos, mod) h.pos = (mod + (h.pos + diff * power[n-x].pos) % mod) % mod

        doh(fir, MOD1);
        doh(sec, MOD2);
    }

    inline pll query()
    {
        return h;
    }
};

namespace hamap
{
    map<pll,list<int>> el;

    list<int>::iterator place[N];
    int best[N];

    inline void add(int x, pll hs)
    {
        el[hs].push_back(x);
        place[x] = prev(el[hs].end());
    }

    inline void rem(int x, pll hs)
    {
        el[hs].erase(place[x]);
    }

    inline void update(pll hs)
    {
        auto it = el.find(hs);

        for (auto i : it->second)
            best[i] = max(best[i], len(it->second));
    }
}

namespace sol
{
    hss t[N];

    int n, l, m;

    void init()
    {
        power[0] = {1,1};
        
        mt19937 rng(timeNow() ^ (ull)make_unique<char>().get());
        p = uniform_int_distribution<int>(27, MOD1-27)(rng);

        for (int i = 1; i <= l; i++)
        {
            #define dopower(pos,mod) power[i].pos = (power[i - 1].pos * p) % mod

            dopower(first, MOD1);
            dopower(second, MOD2);
        }
    }

    void read()
    {
        cin >> n >> l >> m;

        init();

        for (int i = 1; i <= n; i++)
        {
            string s;
            cin >> s;

            t[i].n = l;

            for (int j = 1; j <= l; j++)
                t[i].update(j, s[j - 1]);
        }
    }

    void solve()
    {
        for (int i = 1; i <= n; i++)
            hamap::add(i, t[i].h);
        
        for (auto& i : hamap::el)
            for (auto j : i.second)
                hamap::best[j] = len(i.second);

        while (m--)
        {
            int p1, w1, p2, w2;
            cin >> p1 >> w1 >> p2 >> w2;

            char x = (char)(t[p1].t[w1]+(int)'a'-1), y = (char)(t[p2].t[w2]+(int)'a'-1);

            hamap::rem(p1, t[p1].h);

            if (p2 != p1)
                hamap::rem(p2, t[p2].h);

            t[p1].update(w1, y);
            t[p2].update(w2, x);

            hamap::add(p1, t[p1].h);
            hamap::update(t[p1].h);

            if (p2 != p1)
            {
                hamap::add(p2, t[p2].h);
                hamap::update(t[p2].h);
            }
        }

        for (int i = 1; i <= n; i++)
            cout << hamap::best[i] << '\n';
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