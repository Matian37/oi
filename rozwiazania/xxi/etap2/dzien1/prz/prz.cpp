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

struct chash
{
    size_t operator()(const int& a) const
    {
        const static int rng = (int)timeNow() ^ (int)(ull)(make_unique<char>().get());
        return a ^ rng;
    }
};



const int N = 1e6 + 5;

vector<int> M, L;
int t[N];
int n, k, m, l;

namespace pc
{
    int ind[N], dpm[N], last[N], dpl[N];

    void cmp()
    {
        dpm[n + 1] = dpm[0] = n + 1;

        for (int i = 0; i < N; i++)
            ind[i] = n + 1, last[i] = n + 1;
        for (int i = 0; i < m; i++)
            ind[M[i]] = i;
        
        for (int i = 1; i <= n; i++)
        {
            if (ind[t[i]] == n + 1)
                dpm[i] = n + 1;
            else if (t[i] == M.front())
                dpm[i] = i;
            else
                dpm[i] = dpm[last[M[ind[t[i]] - 1]]];

            last[t[i]] = i;
        }
        for (int i = 1; i <= n; i++)
        {
            if (dpm[i] != n + 1 && t[i] == M.back())
                continue;
            dpm[i] = dpm[i - 1];
        }

        dpl[0] = 0;
        for (int i = 0; i < N; i++)
            ind[i] = 0, last[i] = 0;
        for (int i = 0; i < l; i++)
            ind[L[i]] = i+1;

        for (int i = n; i >= 1; i--)
        {
            if (ind[t[i]] == 0)
                dpl[i] = 0;
            else if (t[i] == L.front())
                dpl[i] = i;
            else
                dpl[i] = dpl[last[L[ind[t[i]]-2]]];
            
            last[t[i]] = i;
        }
        for (int i = n; i >= 1; i--)
        {
            if (dpl[i] != 0 && t[i] == L.back())
                continue;
            dpl[i] = dpl[i + 1];
        }
    }
}

namespace fenwick
{
    int *t;
    int n;

    void init(int _n)
    {
        n=_n;
        t = new int[n + 5]();
    }

    void update(int v, int val)
    {
        while (v <= n)
        {
            t[v] = max(t[v], val);
            v += v & -v;
        }
    }

    int query(int v)
    {
        int val = 0;

        while (v >= 1)
        {
            val = max(val, t[v]);
            v -= v & -v;
        }

        return val;
    }
}

namespace sol
{
    void read()
    {
        cin >> n >> k;

        for (int i = 1; i <= n; i++)
            cin >> t[i];
        cin >> m >> l;

        for (int i = 0; i < m; i++)
        {
            int c;
            cin >> c;
            M.push_back(c);
        }

        for (int i = 0; i < l; i++)
        {
            int c;
            cin >> c;
            L.push_back(c);
        }
    }
    
    ii wstp[N];
    int good[N];

    void gen()
    {
        for (int i = 0; i < N; i++)
            wstp[i] = {n+1, 0};

        for (int i = 1; i <= n; i++)
            wstp[t[i]] = {min(wstp[t[i]].fir,i),
                          max(wstp[t[i]].sec,i)};
    }

    void solve()
    {
        pc::cmp();

        gen();

        fenwick::init(n);

        for (int i = 1; i <= k; i++)
        {
            if (wstp[i].fir == n + 1)
                continue;
            fenwick::update(wstp[i].fir, wstp[i].sec);
        }

        vector<int> v;

        for (int i = 1; i <= n; i++)
        {
            if (t[i] != M.back())
                continue;
            
            int a = pc::dpm[i],
                b = pc::dpl[i];
            
            if (a == n + 1 || b == 0)
                continue;
            
            a--;
            b++;

            if (fenwick::query(a) >= b)
                v.push_back(i);
        }

        cout << isize(v) << '\n';

        for (auto i : v)
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