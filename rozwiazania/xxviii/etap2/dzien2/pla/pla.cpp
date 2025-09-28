//
// Mateusz Pietrowcow
//
 
#pragma GCC optimize("O3,fast-math,unroll-loops")

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
using ld = double;
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

const int N = 1e6+5;

string calc(int start, int end, int k)
{
    int lg = __lg(k);

    ull mian = 1ULL<<(lg+1),
        #define kth (2 * (k - (1 << __lg(k))) + 1)
        lic = mian * start + (ull)(end - start) * kth;

    ull gcd = __gcd(lic, mian);
    lic /= gcd, mian /= gcd;

    //cerr << (ld)lic/(ld)mian << '\n';
    return to_string(lic) + '/' + to_string(mian);
}

struct cmp
{
    bool operator()(const pair<ii,int>& a, const pair<ii,int>& b) const
    {
        ld A = (ld)a.fir.fir / (1<<a.sec), B = (ld)b.fir.fir / (1<<b.sec);

        if (A != B) return A < B;
        return a.fir.sec > b.fir.sec;
    }
};

struct fast_set
{
    priority_queue<pair<ii,int>, vector<pair<ii,int>>, cmp> value;
    list<ii> t[32];

    __attribute__((always_inline)) void pop()
    {
        auto curr = value.top();
        value.pop();

        t[curr.sec].pop_front();
        if (t[curr.sec].size()) 
            value.push({t[curr.sec].front(), curr.sec});

        t[curr.sec + 1].push_back(curr.fir);
        if (t[curr.sec + 1].size() == 1) 
            value.push({t[curr.sec + 1].front(), curr.sec + 1});
    }

    __attribute__((always_inline)) pair<pair<ld,int>,int> top()
    {
        auto curr = value.top();

        return {{(ld)curr.fir.fir / (1<<curr.sec), curr.fir.sec}, curr.sec};
    }

    __attribute__((always_inline)) void push(int val, int start)
    {
        if (t[0].empty()) value.push({{val, start}, 0});
        t[0].push_back({val, start});
    }
};

int zap[N], ord[N];
int wsk = 0;
string rozw[N];

namespace sol
{
    fast_set ranges;
    ii rang[N];
    // ile juz bylo, ile zrobil
    int n, X, z;

    void read()
    {
        cin >> n >> X >> z;
        n--;

        int last;
        cin >> last;

        for (int i = 0; i < n; i++)
        {
            int c;
            cin >> c;
            rang[i] = {c-last, last};
            last = c;
        }

        sort(rang, rang+n, [&](const ii& a, const ii& b)
        {
            if (a.fir != b.fir) return a.fir > b.fir;
            return a.sec < b.sec;
        });

        for (int i = 0; i < n; i++)
            ranges.push(rang[i].fir, rang[i].sec);
    }
    
    struct stan
    {
        ll first;
        int second, third;
    };
    // ile po wykonaniu, kto, ile razy

    hashmap<int,int,chash> id;

    string query(int c, stan& curr, stan& last)
    {
        int k = (1 << (curr.third)) - 1;
            k += (c - (int)last.fir);
        int nr = curr.second;
        return calc(rang[nr].sec, rang[nr].sec + rang[nr].fir, k);
    }

    void init()
    {
        id.resize(5*n);
        for (int i = 0; i < n; i++)
            id[rang[i].sec] = i;
        
        stan last = {0,0,0}, curr;
        
        while (last.fir < (ll)INF)
        {
            auto val = ranges.top();
            ranges.pop();

            curr = {(1LL<<val.sec) + last.fir, id[val.fir.sec], val.sec};

            while (wsk < z)
            {
                if (curr.fir < zap[wsk]) break;
                rozw[ord[wsk]] = query(zap[wsk], curr, last);
                wsk++;
            }
            last = curr;
        }
    }

    void solve()
    {
        for (int i = 0; i < z; i++)
            cin >> zap[i];

        iota(ord,ord+z,0);
        sort(ord,ord+z,[&](const int& a, const int& b){return zap[a] < zap[b];});
        sort(zap,zap+z);

        init();

        for (int i = 0; i < z; i++)
            cout << rozw[i] << '\n';
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