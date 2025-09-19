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

#define F(x,y) f[x+K][y]
#define ROSNACY 0
#define MALEJACY 1
#define LEFT 0
#define RIGHT 1
#define DOWN 0
#define UP 1

const int N = 1e5 + 5, K = 2e5 + 5;

bitset<K> removedSq;
set<ii> f[K * 3][2];
ii t[N];
int n, m, k;
bool swapped;

namespace geo
{
    inline int getB(ii acc, bool typ)
    {
        return acc.sec + (typ == ROSNACY ? -1 : 1) * acc.fir;
    }

    inline void addLine(int b, bool typ, int x, int id)
    {
        F(b,typ).insert({x, id});
    }

    inline void remLine(int b, bool typ, int x, int id)
    {
        F(b, typ).erase({x, id});
    }

    void addSquare(int i)
    {
        addLine(getB({t[i].fir, t[i].sec + 1}, ROSNACY), ROSNACY, t[i].fir, i);
        addLine(getB({t[i].fir, t[i].sec + 1}, MALEJACY), MALEJACY, t[i].fir, i);
        addLine(getB({t[i].fir, t[i].sec - 1}, ROSNACY), ROSNACY, t[i].fir, i);
        addLine(getB({t[i].fir, t[i].sec - 1}, MALEJACY), MALEJACY, t[i].fir, i);
    }

    void remSquare(int i)
    {
        remLine(getB({t[i].fir, t[i].sec + 1}, ROSNACY), ROSNACY, t[i].fir, i);
        remLine(getB({t[i].fir, t[i].sec + 1}, MALEJACY), MALEJACY, t[i].fir, i);
        remLine(getB({t[i].fir, t[i].sec - 1}, ROSNACY), ROSNACY, t[i].fir, i);
        remLine(getB({t[i].fir, t[i].sec - 1}, MALEJACY), MALEJACY, t[i].fir, i);
        removedSq[i] = true;
    }

    int jump(ii& acc, bool& sideX, bool& sideY)
    {
        int val = (sideX == LEFT ? acc.fir : 2 * n - acc.fir);
            val = min(val, sideY == DOWN ? acc.sec : 2 * m - acc.sec);
        
        acc.fir += (sideX == LEFT ? -1 : 1) * val;
        acc.sec += (sideY == DOWN ? -1 : 1) * val;

        if (acc.fir == 0 || acc.fir == 2 * n) sideX = !sideX;
        if (acc.sec == 0 || acc.sec == 2 * m) sideY = !sideY;

        return val;
    }

    int getCollision(ii& acc, bool& sideX, bool& sideY)
    {
        bool typ = sideX ^ sideY;
        int b = getB(acc, typ);

        if (F(b, typ).empty()) return -1;

        if (sideX == LEFT)
        {
            auto it = F(b, typ).upper_bound({acc.fir, INT32_MAX});

            if (it == F(b, typ).begin())
                return -1;
            it = prev(it);

            if (sideY == UP && it != F(b,typ).begin())
                if (prev(it)->fir == it->fir)
                    return prev(it)->sec;
            return it->second;
        }

        auto it = F(b, typ).lower_bound({acc.fir,-1});

        if (it == F(b, typ).end()) return -1;

        if (sideY == DOWN && next(it) != F(b,typ).end())
            if (next(it)->fir == it->fir)
                return next(it)->sec;
        return it->second;
    }

    pair<set<ii>::iterator,set<ii>::iterator> getAllCollisions(ii& acc, bool& sideX, bool& sideY)
    {
        bool typ = sideX ^ sideY;
        int b = getB(acc, typ);

        if (F(b, typ).empty()) 
            return {F(b, typ).end(), F(b, typ).end()};

        if (sideX == LEFT)
        {
            auto it = F(b, typ).upper_bound({acc.fir, INT32_MAX});
            return {F(b, typ).begin(), it};
        }

        auto it = F(b, typ).lower_bound({acc.fir,-1});
        return {it, F(b, typ).end()};
    }

    ii positions[] = {{-1,0},{1,0},{0,-1},{0,1}};

    int jump(ii& acc, bool& sideX, bool& sideY, ii box)
    {
        ii best = {-2, -2};
        bool typ = sideX ^ sideY;
        int b = getB(acc, typ),  val = INT32_MAX;

        for (auto i : positions)
        {
            ii tmp = box;

            tmp.fir += i.fir;
            tmp.sec += i.sec;

            if (getB(tmp, typ) != b) continue;
            
            int d = abs(acc.fir - tmp.fir);

            if (val > d) best = i, val = d;
        }

        acc.fir = box.fir + best.fir;
        acc.sec = box.sec + best.sec;

        if (best.sec == 0) sideX = !sideX;
        else sideY = !sideY;

        return val;
    }
}

    ii rstart;
    bool rsideX, rsideY;

namespace graph
{
    struct info
    {
        int x, y;
        bool sideX, sideY;
    };

    vector<int> bcll[K];
    set<int> edges[2];
    int id[K][2];
    ull pref[K];
    info rid[K];

    inline ull dist(int a, int b)
    {
        if (a <= b) return pref[b - 1] - pref[a - 1];

        int df0 = (a <= n ? 0 : n), dfn = (df0 == 0 ? n : 2 * n);
        return (pref[dfn] - pref[a - 1]) + (pref[b - 1] - pref[df0]);
    }

    void init()
    {
        int lic = 0;

        ii org = (!swapped ? ii{n, 0} : rstart);
        ii acc = org;
        
        bool sideX = LEFT, sideY = UP;

        if (swapped)
            sideX = rsideX, sideY = rsideY;

        do
        {
            ++lic;

            id[acc.fir][sideX ^ sideY] = lic;
            rid[lic] = {acc.fir, acc.sec, sideX, sideY};
            pref[lic] = pref[lic - 1];

            do
            {
                auto tmp = geo::getAllCollisions(acc, sideX, sideY);
            
                while (tmp.fir != tmp.sec)
                {
                    bcll[lic].push_back(tmp.fir->sec);
                    tmp.fir++;
                }

                pref[lic] += geo::jump(acc, sideX, sideY);
            } while (acc.sec != 0);

            if (bcll[lic].size())
                edges[0].insert(lic);
        } 
        while (acc != org);
        
        acc = org;
        sideX = RIGHT, sideY = UP;

        if (swapped)
            sideX = rsideX, sideY = !rsideY;

        do
        {
            ++lic;

            id[acc.fir][sideX ^ sideY] = lic;
            rid[lic] = {acc.fir, acc.sec, sideX, sideY};
            pref[lic] = pref[lic - 1];

            do
            {
                auto tmp = geo::getAllCollisions(acc, sideX, sideY);
            
                while (tmp.fir != tmp.sec)
                {
                    bcll[lic].push_back(tmp.fir->sec);
                    tmp.fir++;
                }
                
                pref[lic] += geo::jump(acc, sideX, sideY);
            } while (acc.sec != 0);

            if (bcll[lic].size())
                edges[1].insert(lic);
        } 
        while (acc != org);
    }
}

namespace sol
{
    void read()
    {
        cin >> n >> m >> k;

        if (n < m) swap(n, m), swapped = true;

        for (int i = 0; i < k; i++)
        {
            cin >> t[i].fir >> t[i].sec;

            t[i].fir = 2 * t[i].fir - 1;
            t[i].sec = 2 * t[i].sec - 1;

            if (swapped) swap(t[i].fir, t[i].sec);
        }

        sort(t, t + k);

        for (int i = 0; i < k; i++)
            geo::addSquare(i);
    }

    int getEdge(int nr, int gr)
    {
        auto it = graph::edges[gr].lower_bound(nr);

        while (true)
        {
            if (it == graph::edges[gr].end())
                it = graph::edges[gr].begin();
            
            while (graph::bcll[*it].size())
            {
                if (!removedSq[graph::bcll[*it].back()]) break;
                graph::bcll[*it].pop_back();   
            }

            if (graph::bcll[*it].size()) 
                return *it;

            it++;
            graph::edges[gr].erase(prev(it));
        }

        return -1;
    }
    
    ull solve()
    {
        ii acc = (!swapped ? ii{n, 0} : ii{0, m});
        bool sideX = LEFT, sideY = UP;
        ull cost = 0;

        if (swapped)
        {
            sideX = RIGHT, sideY = DOWN;
            
            while (acc.sec != 0)
            {
                int cll = geo::getCollision(acc, sideX, sideY);

                if (cll != -1) 
                {
                    cost += geo::jump(acc, sideX, sideY, t[cll]);
                    geo::remSquare(cll);
                    k--;

                    if (k == 0)
                        break;
                }
                else cost += geo::jump(acc, sideX, sideY);
            }

            rstart = acc;
            rsideX = sideX;
            rsideY = sideY;

            if (k == 0) return cost;
        }

        int nr;
        bool gr;

        graph::init();

        while (k != 0)
        {
            nr = graph::id[acc.fir][sideX ^ sideY];
            gr = nr > n;

            int it = getEdge(nr, gr);

            cost += graph::dist(nr, it);

            nr = it;

            acc.fir = graph::rid[nr].x;
            acc.sec = graph::rid[nr].y;
            sideX = graph::rid[nr].sideX;
            sideY = graph::rid[nr].sideY;

            do
            {
                int cll = geo::getCollision(acc, sideX, sideY);

                if (cll != -1) 
                {
                    cost += geo::jump(acc, sideX, sideY, t[cll]);
                    geo::remSquare(cll);
                    k--;
                    if (k == 0) 
                        break;
                }
                else cost += geo::jump(acc, sideX, sideY);
            }
            while (acc.sec != 0);

            if (k == 0)     
                break;
        }

        return cost;
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    cout << sol::solve() << '\n';
}