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

// fix powers

const int N = 1e6+5;
int typ[N], h[N];
pair<ii,ii> rang[N];
int n;

namespace nienormalna_czesc_zadania
{
    string s;
    int m; 

    vector<int> g[N];
    int parent[N], typ[N];

    int dec[2], inc[2];
    bool isX;
    int id;

    ii divide(vector<int>& curr)
    {
        vector<int> left, right;
        for (auto i : curr)
        {
            if (typ[i] != 4) continue;

            for (auto j : dec) left.push_back(g[i][j]);
            for (auto j : inc) right.push_back(g[i][j]);
        }

        ii res;

        if (left.empty() && right.empty())
        {
            res = {id, id + 1};
            ++id;
        }
        else
            res = {divide(left).fir, divide(right).sec};

        for (auto i : curr)
            if (isX) 
                rang[i].fir.fir = res.fir,
                rang[i].sec.fir = res.sec;
            else
                rang[i].fir.sec = res.fir,
                rang[i].sec.sec = res.sec;
        return res;
    }

    void read()
    {
        cin >> m >> s;

        int vert = 0;
        h[0] = m + 1;
        n = 0;

        for (auto i : s)
        {
            g[vert].push_back(++n);
            parent[n] = vert;
            h[n] = h[vert] - 1;
            typ[n] = (i-'0');

            if (typ[n] == 4) 
                vert = n;
            else 
                while (g[vert].size() == 4)
                    vert = parent[vert];
        }

        vector<int> start = {1};

        dec[0] = 0, dec[1] = 1;
        inc[0] = 2, inc[1] = 3;
        isX = false, id = 0;
        divide(start);

        start.clear();
        start.push_back(1);

        dec[0] = 0, dec[1] = 2;
        inc[0] = 1, inc[1] = 3;
        isX = true, id = 0;
        divide(start);

        vector<pair<pair<ii,ii>,int>> good;
        good.reserve(n);

        for (int i = 1; i <= n; i++)
            if (typ[i] == 1)
                good.push_back({rang[i], h[i]});
        
        n = len(good);
        for (int i = 1; i <= n; i++)
            rang[i] = good[i - 1].fir,
            h[i] = good[i - 1].sec;
    }
}

namespace fu
{
    vector<ii> nums[N];
    int fu[N];

    int find(int x)
    {
        if (fu[x] == x) return x;
        return fu[x] = find(fu[x]);
    }

    bool Union(int a, int b)
    {
        a = find(a), b = find(b);

        if (a == b) return false;
        if (len(nums[a]) > len(nums[b])) swap(a,b);

        fu[a] = b;
        for (auto i : nums[a]) 
            nums[b].push_back(i);
        return true;
    }

    void init()
    {
        for (int i = 1; i <= n; i++)
            fu::fu[i] = i, fu::nums[i].push_back({h[i], 1});
    }
};

namespace ordinary_solve
{
    #define BACK 0
    #define FRONT 1
    #define X 0
    #define Y 1

    vector<pair<ii,int>> edges[N][2][2];

    void join(int x, bool side)
    {
        #define too_old(old,nw) (old.sec < nw.fir)
        #define overlap(a, b) (!(a.sec <= b.fir || b.sec <= a.fir))
        #define BC edges[x][side][BACK]
        #define FN edges[x][side][FRONT]

        int i = 0, j = -1;

        while (i < len(BC))
        {
            while (j + 1 < len(FN))
            {
                if (too_old(BC[i].fir, FN[j + 1].fir)) break;

                j++;
                if (overlap(BC[i].fir, FN[j].fir))
                    fu::Union(BC[i].sec, FN[j].sec);
            }
            i++, j = max(j - 1, -1);
        }

        #undef BC
        #undef FN
        #undef overlap
        #undef too_old
    }

    void init()
    {        
        fu::init();
        int lX = 0, lY = 0;

        for (int i = 1; i <= n; i++)
        {
            lX = max(lX, rang[i].sec.fir),
            lY = max(lX, rang[i].sec.sec);
        
            edges[rang[i].sec.fir][X][BACK].push_back({{rang[i].fir.sec, rang[i].sec.sec}, i});
            edges[rang[i].fir.fir][X][FRONT].push_back({{rang[i].fir.sec, rang[i].sec.sec}, i});

            edges[rang[i].sec.sec][Y][BACK].push_back({{rang[i].fir.fir, rang[i].sec.fir}, i});
            edges[rang[i].fir.sec][Y][FRONT].push_back({{rang[i].fir.fir, rang[i].sec.fir}, i});
        }
        
        for (int i = 0; i <= lX; i++) 
        {
            sort(all(edges[i][X][BACK]));
            sort(all(edges[i][X][FRONT]));
            join(i, X);
        }
        for (int i = 0; i <= lY; i++) 
        {
            sort(all(edges[i][Y][BACK]));
            sort(all(edges[i][Y][FRONT]));
            join(i, Y);
        }
    }

    void normalize(int x)
    {
        map<int,int> lic;

        for (auto i : fu::nums[x]) lic[i.fir]++;

        for (auto it = lic.begin(); it != lic.end(); it++)
        {
            if (it->sec >= 4) lic[it->fir + 1] += it->sec / 4;
            it->sec %= 4;
        }

        fu::nums[x].clear();
        for (auto it = lic.rbegin(); it != lic.rend(); it++)
            if (it->sec != 0)
                fu::nums[x].push_back(*it);
    }

    bool comp(int a, int b)
    {
        bool neg = false;

        if (len(fu::nums[a]) > len(fu::nums[b]))
            swap(a,b), neg = true;
        
        for (int i = 0; i < len(fu::nums[a]); i++)
            if (fu::nums[a][i] != fu::nums[b][i])
                return neg ^ !!(fu::nums[a][i] < fu::nums[b][i]);
        return !neg;
    }

    ull power(ull x, ull y)
    {
        ull r = 1;

        while (y != 0)
        {
            if (y % 2) r = (r * x) % MODULL;
            x = (x * x) % MODULL;
            y /= 2;
        }

        return r;
    }

    void solve()
    {
        init();

        vector<int> can;

        for (int i = 1; i <= n; i++)
            if (fu::find(i) == i)
                can.push_back(i);
        
        cout << len(can) << '\n';

        int best = 0;

        for (auto i : can)
        {
            normalize(i);

            if (comp(best, i)) 
                best = i;
        }

        ull sum = 0;

        for (auto i : fu::nums[best])
            sum = (sum + power(4, i.fir) * i.sec) % MODLL;
        cout << sum << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    nienormalna_czesc_zadania::read();
    ordinary_solve::solve();
}