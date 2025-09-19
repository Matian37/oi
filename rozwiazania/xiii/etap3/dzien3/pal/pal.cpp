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

struct hashfn
{
    size_t operator()(const ii& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return ((((ll)a.fir) << 32) + a.sec) ^ rng;
    }
};


const int N = 2e6 + 5;


ll p;

struct HASH
{
    int h1, h2;

    HASH() : h1(0), h2(0){};
    HASH(int _h1, int _h2) : h1(_h1), h2(_h2){};

    void mult()
    {
        h1 = (h1 * p) % MOD1;
        h2 = (h2 * p) % MOD2;
    }

    void add(ll val)
    {
        h1 = (h1 + val) % MOD1;
        h2 = (h2 + val) % MOD2;
    }

    void add(ll val, HASH& powerTable)
    {
        h1 = (h1 + (val * powerTable.h1) % MOD1) % MOD1;
        h2 = (h2 + (val * powerTable.h2) % MOD2) % MOD2;
    }

    void addUj(ll val)
    {
        h1 = (h1 + (MOD1 + val % MOD1) % MOD1) % MOD1;
        h2 = (h2 + (MOD2 + val % MOD2) % MOD2) % MOD2;
    }

    void addUj(ll val, HASH& powerTable)
    {
        ll val1, val2;

        val1 = val * -powerTable.h1;
        val2 = val * -powerTable.h2;

        h1 = (h1 + (MOD1 + val1 % MOD1) % MOD1) % MOD1;
        h2 = (h2 + (MOD2 + val2 % MOD2) % MOD2) % MOD2;
    }

    void addChar(char a)
    {
        int val = a - 'a' + 1;

        this->mult();
        this->add(val);
    }

    void addCharR(char a, int i, HASH* powerTable)
    {
        ll val = a - 'a' + 1;

        this->add(val, powerTable[i]); 
    }

    bool operator==(HASH& b)
    {
        if (this->h1 != b.h1) return false;
        return this->h2 == b.h2;
    }
};

HASH powerTable[N];

namespace sol
{
    int n;
    vector<string> t;

    void read()
    {
        cin >> n;

        t.reserve(n);

        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            
            string s;
            cin >> s;

            t.push_back(s);
        }
    }

    unordered_map<ii,int,hashfn> hashes;
    
    void init()
    {
        mt19937 rng(timeNow());
        p = uniform_int_distribution<int>(27, MOD1 - 2)(rng); 

        powerTable[0] = HASH(1,1);

        for (int i = 1; i < N; i++)
        {
            powerTable[i] = powerTable[i - 1];
            powerTable[i].mult();
        }

        for (int i = 0; i < n; i++)
        {
            HASH h(0,0);
            
            for (auto j : t[i])
                h.addChar(j);
            hashes[{h.h1,h.h2}]++;
        }
    }

    vector<HASH> tmp;

    void solve()
    {
        init();

        tmp.resize(N);

        ull result = 0;

        for (int i = 0; i < n; i++)
        {
            HASH h(0,0), rh(0,0), suff(0,0);

            for (int j = isize(t[i]) - 1; j >= 0; j--)
            {
                suff.addChar(t[i][j]);
                tmp[j] = suff;
            }

            result += hashes[{suff.h1, suff.h2}];

            for (int j = 0; j < isize(t[i]) - 1; j++)
            {
                h.addChar(t[i][j]);
                rh.addCharR(t[i][j], j, powerTable);

                if (h == rh) 
                    result += 2 * hashes[{tmp[j + 1].h1, tmp[j + 1].h2}];
            }

        }

        cout << result << '\n';
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