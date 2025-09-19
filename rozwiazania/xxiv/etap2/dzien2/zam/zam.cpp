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
#define self(x,y,z) x = z(x,y)

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using hashmapsafe = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

#ifdef LOCAL
const int N = 100;
#else
const int N = 1e6+1;
#endif

namespace gr
{
    vector<int> g[N];
    bitset<N> visited;

    inline void addEdge(int a, int b)
    {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int bfs(int s, int k)
    {
        queue<ii> q;

        q.push({s,1});

        while (q.size())
        {
            auto acc = q.front();
            q.pop();

            if (visited[acc.fir]) continue;
            if (acc.fir == k) return acc.sec;
            visited[acc.fir] = true;

            for (auto i : g[acc.fir])
            {
                if (visited[i]) continue;
                q.push({i, acc.sec + 1});
            }
        }

        return -1;
    }
}

namespace edgeConnect
{
    struct info
    {
        int a, b, id;

        bool operator<(const info& c) const
        {
            if (a != c.a) return a < c.a;
            if (b != c.b) return b < c.b;
            return id < c.id;
        }
    };

    void connect(set<info>& a, set<info>& b)
    {
        if (b.empty()) return;

        for (auto& i : a)
        {
            auto it = b.lower_bound({i.b, i.b, 0});

            if (it == b.begin()) return;
            it--;

            while (true)
            {
                if (it->a >= i.b || it->b <= i.a) break;

                gr::addEdge(i.id, it->id);

                if (it == b.begin()) break;
                it--;
            }
        }
    }

    map<int, set<info>> L, R;

    void initEdges(int n, pair<ii,ii>* sq)
    {
        for (int i = 0; i < n; i++)
        {
            L[sq[i].fir.fir].insert({sq[i].fir.sec, sq[i].sec.sec, i});
            R[sq[i].sec.fir].insert({sq[i].fir.sec, sq[i].sec.sec, i});
        }

        for (auto& i : L)
            connect(i.second, R[i.first]);

        L.clear();
        R.clear();

        for (int i = 0; i < n; i++)
        {
            L[sq[i].fir.sec].insert({sq[i].fir.fir, sq[i].sec.fir, i});
            R[sq[i].sec.sec].insert({sq[i].fir.fir, sq[i].sec.fir, i});
        }

        for (auto& i : L)
            connect(i.second, R[i.first]);
    }
}

namespace points
{
    struct event
    {
        int x, a, b, id;
    };

    struct rang
    {
        int a, b, id;

        bool operator<(const rang& A) const
        {
            if (b != A.b) return b < A.b;
            return a < A.a;
        }
    };

    vector<event> t;
    set<rang> curr;

    void initPoints(int n, int m, pair<ii,ii>* sq, ii* p)
    {
        t.reserve(2*n+m);

        for (int i = 0; i < n; i++)
        {
            t.push_back({sq[i].fir.fir, sq[i].fir.sec, sq[i].sec.sec, i});
            t.push_back({sq[i].sec.fir, sq[i].fir.sec, sq[i].sec.sec, i});
        }

        for (int i = 0; i < m; i++)
            t.push_back({p[i].fir, p[i].sec, p[i].sec, INF});
        
        sort(all(t), [&](const event& a, const event& b)
        {
            if (a.x != b.x) return a.x < b.x;
            
            int ra = (a.id == INF ? 2 : sq[a.id].sec.fir != a.x), 
                rb = (b.id == INF ? 2 : sq[b.id].sec.fir != b.x);
            return ra < rb;
        });

        for (auto& i : t)
        {
            if (i.id == INF)
            {
                auto it = curr.lower_bound({0, i.a, 0});

                if (it == curr.end()) continue;
                if (it->a > i.a || it->b < i.a) continue;

                gr::visited[it->id] = true;
            }
            else if (sq[i.id].sec.fir == i.x)
                curr.erase({sq[i.id].fir.sec, sq[i.id].sec.sec, i.id});
            else
                curr.insert({sq[i.id].fir.sec, sq[i.id].sec.sec, i.id});
        }
    }
}

namespace sol
{
    pair<ii,ii> sq[N];
    ii p[N];

    int n, m;
    int sid, eid;

    inline bool inside(ii a, int c)
    {
        if (a.fir < sq[c].fir.fir) return false;
        if (a.fir > sq[c].sec.fir) return false;
        if (a.sec < sq[c].fir.sec) return false;
        if (a.sec > sq[c].sec.sec) return false;
        return true;
    }

    void read()
    {
        cin >> n >> m;
        cin >> n >> m;

        ii start, endd;
        cin >> start.fir >> start.sec >> endd.fir >> endd.sec;

        for (int i = 0; i < n; i++)
        {
            cin >> sq[i].fir.fir >> sq[i].fir.sec >> sq[i].sec.fir >> sq[i].sec.sec;
            
            ii c1 = {min(sq[i].fir.fir, sq[i].sec.fir), min(sq[i].fir.sec, sq[i].sec.sec)}, 
               c2 = {max(sq[i].fir.fir, sq[i].sec.fir), max(sq[i].fir.sec, sq[i].sec.sec)};
            
            sq[i].fir = c1;
            sq[i].sec = c2;
        }
        for (int j = 0; j < m; j++)
            cin >> p[j].fir >> p[j].sec;

        for (int i = 0; i < n; i++)
        {
            if (inside(start, i)) sid = i;
            if (inside(endd, i)) eid = i;
        }
    }

    void solve()
    {
        edgeConnect::initEdges(n, sq);
        points::initPoints(n, m, sq, p);
        cout << gr::bfs(sid, eid) << '\n';
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