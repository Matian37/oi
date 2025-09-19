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

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

#define MOD1 1000000007ULL
#define MOD2 1000000403ULL
#define MOD3 1000000787ULL
#define MOD4 1000001447ULL

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

const int N = 1e5 + 5;
const int K = 320;
const int BASE = 1 << 17;
const int LG = 18;

vector<ii> g[N];
vector<int> wstp[N], big;
int kuch[N], bigId[N];
int n, sq, r;

struct st
{
    ll* tree;
    int base;
    int p, k;

    st(){}

    void initStructure(int _base, int _p, int _k)
    {
        base = _base;
        p = _p;
        k = _k;
        tree = new ll[base * 2];
    }

    void init(int v, int a, int b)
    {
        if (v >= base) return;
        if (k < a|| b < p) return;

        int mid = (a + b) / 2;

        init(v * 2, a, mid);
        init(v * 2 + 1, mid + 1, b);

        if (k < mid + 1 || b < p)
            tree[v] = tree[v * 2];
        else
            tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
    }

    ll query(int a, int b)
    {
        a += base - 1;
        b += base + 1;

        ll val = tree[a + 1];

        while (a / 2 != b / 2)
        {
            if (a % 2 == 0) val = min(val, tree[a + 1]);
            if (b % 2 == 1) val = min(val, tree[b - 1]);
            a /= 2;
            b /= 2;
        }

        return val;
    }
};

namespace hld
{
    int parent[N], nxt[N], sajz[N], nr[N], h[N];

    st dist[K];

    void distDfs(int v, int p)
    {
        if (bigId[kuch[v]] != -1)
            hld::dist[bigId[kuch[v]]].tree[nr[v] + BASE] = 0;

        for (auto i : g[v])
        {
            if (i.fir == p) continue;

            for (int j = 0; j < isize(big); j++)
                hld::dist[j].tree[nr[i.fir] + BASE] = min(hld::dist[j].tree[nr[i.fir] + BASE], 
                                                          hld::dist[j].tree[nr[v] + BASE] + i.sec);

            distDfs(i.fir, v);

            for (int j = 0; j < isize(big); j++)
                hld::dist[j].tree[nr[v] + BASE] = min(hld::dist[j].tree[nr[i.fir] + BASE] + i.sec, 
                                                      hld::dist[j].tree[nr[v] + BASE]);
        }
    }

    int sajzDfs(int v, int p)
    {
        h[v] = h[p] + 1;
        sajz[v] = 1;

        for (auto i : g[v])
        {
            if (i.fir == p) continue;
            sajz[v] += sajzDfs(i.fir, v);
        }

        return sajz[v];
    }

    int cnt;

    void dfs(int v, int p)
    {
        nr[v] = cnt++;
        parent[v] = p;

        if (g[v].size() == 1 && p != 0) return;

        int heavy = (g[v].size() == 1 ? g[v][0].fir : -1);

        if (heavy == -1)
            heavy = (g[v][0].fir == p ? g[v][1].fir : g[v][0].fir);

        for (auto i : g[v])
            if (i.fir != p)
                if (sajz[heavy] < sajz[i.fir])
                    heavy = i.fir;

        nxt[heavy] = nxt[v];

        dfs(heavy, v);

        for (auto i : g[v])
        {
            if (i.fir == p || i.fir == heavy) continue;
            nxt[i.fir] = i.fir;
            dfs(i.fir, v);
        }
    }

    inline int nastp(int a)
    {
        return (nxt[a] == a ? max(1,parent[a]) : nxt[a]);
    }

    ll query(int a, int b, int typ)
    {
        ll result = INFLL;

        typ = bigId[typ];

        while (nastp(a) != nastp(b))
        {
            if (h[nastp(a)] < h[nastp(b)]) swap(a, b);

            int c = nr[nastp(a)], d = nr[a];

            if (c > d) swap(c, d);

            if (nxt[a] != a) result = min(result, dist[typ].query(c, d));
            else result = min({result, dist[typ].tree[c + BASE], dist[typ].tree[d + BASE]});
            a = nastp(a);
        }

        if (a == b) return min(result, dist[typ].tree[nr[a] + BASE]);

        if (nxt[a] == a && nxt[b] == b)
            return min({result, dist[typ].tree[nr[a] + BASE],
                                dist[typ].tree[nr[b] + BASE],
                                dist[typ].tree[nr[parent[a]] + BASE]});

        if (nxt[a] == a) result = min(result,dist[typ].tree[nr[a] + BASE]), a = parent[a];
        if (nxt[b] == b) result = min(result,dist[typ].tree[nr[b] + BASE]), b = parent[b];

        if (nr[a] > nr[b]) swap(a, b);

        return min(result, dist[typ].query(nr[a], nr[b]));
    }

    void init()
    {
        sajzDfs(1, 0);
        nxt[1] = 1;
        dfs(1, 0);

        for (int i = 0; i < isize(big); i++)
        {
            dist[i].initStructure(BASE, 0, n - 1);

            for (int j = 0; j < n; j++)
                dist[i].tree[j + BASE] = INFLL;
        }

        distDfs(1, 0);
        distDfs(1, 0);

        for (int i = 0; i < isize(big); i++)
            dist[i].init(1, 0, BASE - 1);
    }
}

namespace lca
{
    int spt[2 * N][LG], latest[N];
    ll pref[N];
    int m = 0;

    void dfs(int v, int p)
    {
        latest[v] = m;
        spt[m++][0] = v;

        for (auto i : g[v])
        {
            if (i.fir == p) continue;

            pref[i.fir] = pref[v] + i.sec;

            dfs(i.fir, v);

            latest[v] = m;
            spt[m++][0] = v;
        }
    }

    inline int minn(int a, int b)
    {
        return (hld::h[a] < hld::h[b] ? a : b);
    }

    void init()
    {
        dfs(1, 0);

        for (int i = 1; i <= __lg(m); i++)
        {
            int pot = 1 << i;

            for (int j = 0; j < m - pot + 1; j++)
                spt[j][i] = minn(spt[j][i - 1], spt[j + pot / 2][i - 1]);
        }
    }

    int __lca(int a, int b)
    {
        a = latest[a];
        b = latest[b];

        if (a > b) swap(a,b);

        int lg = __lg(b - a + 1);

        return minn(spt[a][lg], spt[b - (1 << lg) + 1][lg]);
    }

    inline ll dist(int a, int b)
    {
        return pref[a] + pref[b] - 2LL * pref[__lca(a, b)];
    }
}

namespace sol
{

    void read()
    {
        cin >> n >> r;

        sq = (int)sqrt(n);

        for (int i = 1; i <= n; i++)
        {
            cin >> kuch[i];
            wstp[kuch[i]].push_back(i);
        }

        for (int i = 0; i < n - 1; i++)
        {
            int a, b, c;
            cin >> a >> b >> c;
            g[a].push_back({b, c});
            g[b].push_back({a, c});
        }
    }

    void init()
    {
        big.reserve(sq);

        for (int i = 1; i <= r; i++)
        {
            if (isize(wstp[i]) > sq)
            {
                bigId[i] = isize(big);
                big.push_back(i);
            }
            else bigId[i] = -1;
        }

        hld::init();
        lca::init();
    }
    
    void solve()
    {
        init();

        int q;
        cin >> q;

        while (q--)
        {
            int a, b, r;
            cin >> a >> b >> r;

            if (isize(wstp[r]) == 0)
            {
                cout << "-1\n";
                continue;
            }

            if (isize(wstp[r]) <= sq)
            {
                ll result = INFLL;

                for (auto i : wstp[r])
                    result = min(result, lca::dist(a,i) + lca::dist(b,i));
                
                cout << result << '\n';

                continue;
            }

            cout << lca::dist(a, b) + 2LL * hld::query(a, b, r) << '\n';
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