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

constexpr int N = 1e5+5;
constexpr int BASE = 1 << 17;
constexpr int VERT = 4 * (1<<17);
int base;

namespace tree
{
    vector<ii> g[VERT];
    int val[VERT];
    int nr;

    void __init(int v)
    {
        if (v >= base) return;

        __init(v * 2);
        g[v * 2].push_back({v, 0});
        __init(v * 2 + 1);
        g[v * 2 + 1].push_back({v, 0});
    }

    void init()
    {
        __init(1);
    }

    void update(int x, int vl)
    {
        x += base;
        val[x] = vl;
        x /= 2;

        while (x != 0)
        {
            val[x] = max(vl, val[x]);
            x /= 2;
        }
    }

    vector<int> getQuery(int a, int b)
    {
        a += base - 1;
        b += base + 1;

        vector<int> sol;

        while (a / 2 != b / 2)
        {
            if (a % 2 == 0) sol.push_back(a + 1);
            if (b % 2 == 1) sol.push_back(b - 1);
            a /= 2;
            b /= 2;
        }

        return sol;
    }

    void addQuery()
    {
        int l, r, k;
        cin >> l >> r >> k;

        vector<ii> rang;
        vector<int> deeper;
        rang.reserve(k+1);
        deeper.reserve(k);

        int last = l - 1;
        for (int i = 0; i < k; i++)
        {
            int c;
            cin >> c;

            deeper.push_back(c);

            if (last + 1 <= c - 1)
                rang.push_back({last + 1, c - 1});
            last = c;
        }
        if (last + 1 <= r)
            rang.push_back({last + 1, r});

        ++nr;
        for (auto i : rang)
            for (auto j : getQuery(i.fir, i.sec))
                g[j].push_back({nr, 0});
        for (auto i : deeper)
            g[nr].push_back({i + base, 1});
    }
}

namespace toposort
{
    int wsk[VERT];

    bool solve()
    {
        #define g tree::g
        #define n tree::nr
        #define val tree::val

        for (int i = 1; i <= n; i++)
            for (auto j : g[i])
                wsk[j.fir]++;
        
        queue<int> q;

        for (int i = 1; i <= n; i++)
            if (wsk[i] == 0)
                q.push(i);
        
        int done = 0;

        while (len(q))
        {
            auto acc = q.front();
            q.pop();
            done++;

            if (val[acc] == 0)
                val[acc] = 1;

            for (auto i : g[acc])
            {
                val[i.fir] = max(val[i.fir], val[acc] + i.sec);
                wsk[i.fir]--;

                if (wsk[i.fir] == 0)
                    q.push(i.fir);
            }
        }


        return done == n;

        #undef g
        #undef n
        #undef val
    }
}

namespace sol
{
    int t[N];
    int s, n, q;

    void read()
    {
        cin >> n >> s >> q;

        base = 1 << (__lg(n) + 1);
        tree::nr = 2 * base - 1;

        while (s--)
        {
            int p, c;
            cin >> p >> c;
            t[p] = c;
            tree::update(p, c);
        }
    }
    
    void solve()
    {

        tree::init();

        while (q--)
            tree::addQuery();

        bool res = toposort::solve();
        
        if (!res)
        {
            cout << "NIE\n";
            return;
        }  
        
        res = [&]()
        {
            for (int i = 1; i <= n; i++)
            {
                if (tree::val[i + base] < 1 || tree::val[i + base] > 1'000'000'000)
                    return false;
                if (t[i] == 0 || (tree::val[i + base] == t[i])) continue;
                else return false;
            }

            return true;
        }();

        if (!res)
        {
            cout << "NIE\n";
            return;
        }

        cout << "TAK\n";
        for (int i = 1; i <= n; i++)
            cout << tree::val[i + base] << ' ';
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