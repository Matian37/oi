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

#define INF 1'000'000'009
#define INFLL 1'000'000'000'000'000'009LL
#define INFULL 1'000'000'000'000'000'009ULL
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

const int N = 5e5+5;
ii rp[N], rk[N];
int n;

namespace sol
{
    void read()
    {
        int m;
        cin >> m >> n;
        for (int i = 1; i <= n; i++)
        {
            cin >> rk[i].fir >> rk[i].sec;
            rp[i] = rk[i];
        }

        sort(rp+1,rp+n+1);
        sort(rk+1,rk+n+1, [&](const ii& a, const ii& b)
        {
            if (a.sec != b.sec)
                return a.sec < b.sec;
            return a.fir < b.fir;
        });
    }
    
    vector<ii> nz, ranges, segments;

    bool collide(ii a, ii b)
    {
        return !(a.sec <= b.fir || b.sec <= a.fir);
    }

    bool collideTwo(ii x)
    {
        int low = 0, high = len(nz) - 1, med;

        while (low != high)
        {
            med = (low + high) / 2;
            if (nz[med].sec < x.fir) low = med + 1;
            else high = med;
        }

        if (!collide(x, nz[low])) return false;
        if (low + 1 == len(nz)) return false;
        if (!collide(x, nz[low+1])) return false;
        return true;
    }

    int machen()
    {
        nz.clear();
        ranges.clear();
        segments.clear();

        int c = 0, last = -1;

        for (int i = 1; i <= n; i++)
            if (last <= rk[i].fir)
                last = rk[i].sec, c++, nz.push_back(rk[i]);

        for (int i = 1; i <= n; i++)
        {
            int low = 0, high = len(nz)-1, med;

            while (low != high)
            {
                med = (low + high) / 2;
                if (nz[med].fir < rp[i].fir) low = med + 1;
                else high = med;
            }

            if (rp[i].fir <= nz[low].fir && nz[low].sec <= rp[i].sec)
                continue;
            ranges.push_back(rp[i]);
        }

        vector<pair<int,bool>> events;

        for (auto i : ranges)
            events.push_back({i.fir, true}),
            events.push_back({i.sec, false});
        for (auto i : nz)
            events.push_back({i.fir, true}),
            events.push_back({i.sec, false});
        sort(all(events));

        segments.push_back({0,0});

        int lic = 1;

        for (int i = 1; i < len(events); i++)
        {
            if (events[i].fir - events[i-1].fir != 0 && lic != 0)
                segments.push_back({events[i-1].fir, events[i].fir});
            lic += (events[i].sec ? 1 : -1);
        }

        return c;
    }
    
    int dp[2*N];

    map<int,int> psid, ksid, pid;

    void solve()
    {
        psid.clear();
        ksid.clear();
        pid.clear();

        cout << machen() << ' ';

        fill(dp,dp+len(segments)+5,0);


        for (int i = len(ranges) - 1; i >= 0; i--)
        {
            pid[ranges[i].fir] = i+1;
        }
        for (int i = 1; i < len(segments); i++)
            psid[segments[i].fir] = i, ksid[segments[i].sec] = i;

        dp[len(segments)] = 0; // 0
        dp[len(segments)+1] = 1; // 0
        dp[len(segments)+2] = 1; // 0
        dp[len(segments)+3] = 0; // 0

        psid[nz.back().sec] = ksid[INF] = len(segments)+1;
        psid[INF] = ksid[INF+1] = len(segments)+2;

        nz.push_back({nz.back().sec,INF+1});
        int ms = nz.back().sec;
        
        for (int i = len(segments)-1, j = len(nz)-2; i > 0; i--)
        {
            while (segments[i].sec <= nz[j].fir)
            {
                ms = nz[j].sec;
                j--;
            }

            ll d = (segments[i].sec - segments[i].fir);

            int a = psid[nz[j+1].fir], b = ksid[ms];

            if (nz[j].sec <= segments[i].fir)
            {
                dp[i] = 0;
                goto nxt;
            }

            if (a > b)
            {
                dp[i] = 0;
                goto nxt;
            }

            dp[i] = (d*(dp[a]-dp[b+1])) % MOD;

            nxt:

            dp[i] = (dp[i] + dp[i + 1]) % MOD;

            if (pid[segments[i].fir] != 0)
                ms = min(ms, ranges[pid[segments[i].fir]-1].sec);
        }

        ll res = 0;

        for (int i = 1; i < len(segments); i++)
        {
            if (nz[0].sec <= segments[i].fir) break;
            res = (res + MOD + (dp[i] - dp[i+1]) % MOD) % MOD;
        }

        cout << res << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int z;
    cin >> z;

    while (z--)
    {
        sol::read();
        sol::solve();
    }
}