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

namespace sol
{
    const int N = 2e5 + 5;
    int t[N];
    int n;

    void read()
    {
        cin >> n;

        for (int i = 1; i <= n; i++)
            cin >> t[i];
    }

    pll h[N], rh[N], power[N], divpower[N];
    ll p;

    ll fastpot(ll a, ll b, ll m)
    {
        ll r = 1;

        while (b != 0)
        {
            if (b % 2 == 1)
                r = (r * a) % m;
            a = (a * a) % m;
            b /= 2;
        }

        return r;
    }

    void init()
    {
        mt19937 rng(timeNow());

        p = uniform_int_distribution<int>(2 * (n + 1), MOD1 - 2)(rng);

        power[0] = {1,1};
        divpower[0] = {1,1};
        divpower[1] = {fastpot(p,MOD1-2,MOD1),fastpot(p,MOD2-2,MOD2)};

        for (int i = 1; i <= n; i++)
        {
            #define hcomp(x,y) h[i].x = (h[i - 1].x * p + t[i]) % y
            #define pcomp(x,y) power[i].x = (power[i - 1].x * p) % y
            #define dcomp(x,y) divpower[i].x = (divpower[i - 1].x * divpower[1].x) % y;

            hcomp(fir,MOD1);
            hcomp(sec,MOD2);
            pcomp(fir,MOD1);
            pcomp(sec,MOD2);
            dcomp(fir,MOD1);
            dcomp(sec,MOD2);
        }

        for (int i = 1; i <= n; i++)
        {
            #define rhcomp(x,y) rh[i].x = (rh[i - 1].x + power[i - 1].x * t[i]) % y

            rhcomp(fir,MOD1);
            rhcomp(sec,MOD2);
        }
    }

    pll query(int a, int b)
    {
        pll r = h[b], rr = rh[b];

        #define comput(x,y) r.x = (y + (r.x - h[a - 1].x * power[b - a + 1].x) % y) % y
        #define rcomput(x,y) rr.x = (y + ((rr.x - rh[a - 1].x) * divpower[a - 1].x) % y) % y;

        comput(fir,MOD1);
        comput(sec,MOD2);
        rcomput(fir,MOD1);
        rcomput(sec,MOD2);

        if (r > rr) swap(r, rr);

        return {(r.fir << 32) + rr.fir, (r.sec << 32) + rr.sec};
    }

    pll v[N];
    int wsk = 0;

    void solve()
    {
        init();

        int best = 0;
        vector<int> sol;

        for (int i = 1; i <= n; i++)
        {
            wsk = 0;

            for (int j = 1; j <= n - i + 1; j += i)
            {
                v[wsk]=(query(j,j+i-1));
                wsk++;
            }

            sort(v,v+wsk);

            int m = 1;

            for (int j = 1; j < wsk; j++)
                if (v[j - 1] != v[j])
                    m++;
            
            if (m > best)
            {
                best = m;
                sol.clear();
                sol.push_back(i);
            }
            else if (m == best)
                sol.push_back(i);
        }

        cout << best << ' ' << isize(sol) << '\n';

        for (auto i : sol)
            cout << i << ' ';
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