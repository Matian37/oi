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
using hashmap_bit = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmap_prime = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
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

const int base = 1 << 19;

struct tree
{
    int tree[base * 2];

    void update(int v, int c)
    {
        v += base;

        while (v != 0)
        {
            tree[v] += c;
            v /= 2;
        }
    }

    int query(int a, int b)
    {
        if (a > b) return 0;

        a += base - 1;
        b += base + 1;

        int r = 0;

        while (a / 2 != b / 2)
        {
            if (a % 2 == 0) r += tree[a + 1];
            if (b % 2 == 1) r += tree[b - 1];
            a /= 2;
            b /= 2;
        }

        return r;
    }
};

tree lic[2][2];

namespace sol
{
    const int N = 5e5+5;
    vector<int> g[N];
    int n;

    void read()
    {
        cin >> n;

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
        }
    }

    int sajz[N], dist[2][N];
    int can1 = 1, can2 = 1;

    void distDfs(int v, int p, int* d)
    {
        d[v] = d[p] + 1;

        for (auto i : g[v])
            if (i != p)
                distDfs(i, v, d);
    }

    int sajzDfs(int v, int p)
    {
        sajz[v] = 1;

        for (auto i : g[v])
        {
            if (i == p) continue;
            sajz[v] += sajzDfs(i, v);
        }

        return sajz[v];
    }

    ull result = 0;
    bool color[N][2];

    void update(int x, bool typ, int c)
    {
        #define who() (dist[0][x] <= dist[1][x] ? 0 : 1)


        int change = 0, d = min(dist[0][x], dist[1][x]), a, b;
        bool did = false;


        if (color[x][!typ])
        {
            did = true;
            lic[!typ][who()].update(d, -1);
        }

        if (!typ) a = (can1 == can2 ? d : d + 1), b = base - 1;
        else a = 0, b = (can1 == can2 ? d : d - 1);

        if (can1 == can2)
            change += lic[!typ][0].query(a, b);
        else
        {
            change += lic[!typ][0].query(a, b);
            change += lic[!typ][1].query(a, b);

            if (d != 0)
                change += lic[!typ][who()].query(d,d);
        }
        result += c * change;

        if (did)
            lic[!typ][who()].update(d, 1);

        lic[typ][who()].update(d, c);
        color[x][typ] = (c == 1);
    }

    ull query()
    {
        return result;
    }
    
    void solve()
    {
        sajzDfs(1, 0);

        for (int i = 2; i <= n; i++)
            if (sajz[can1] > sajz[i] && sajz[i] >= (n+1) / 2)
                can1 = i;
        for (int i = 2; i <= n; i++)
            if (sajz[can2] > sajz[i] && sajz[i] >= n / 2 + 1)
                can2 = i;
            
        dist[0][0] = dist[1][0] = -1;
        distDfs(can1, 0, dist[0]);
        distDfs(can2, 0, dist[1]);

        int s1, s2, q;
        cin >> s1 >> s2 >> q;

        for (int i = 0; i < s1; i++)
        {
            int c;
            cin >> c;
            update(c, false, 1);
        }
        for (int i = 0; i < s2; i++)
        {
            int c;
            cin >> c;
            update(c, true, 1);
        }

        cout << query() << '\n';
        while (q--)
        {
            char typ, op;
            int vert;
            cin >> typ >> op >> vert;

            update(vert, typ=='B', (op == '+' ? 1 : -1));

            cout << query() << '\n';
        }
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