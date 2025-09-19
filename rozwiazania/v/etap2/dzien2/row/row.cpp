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
#define itr iterator

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



const int N = 1e4 + 5;

pair<char, int> t[N][2];
int pref[27];
int k, L, R;

inline int get(char a, int pos)
{
    if (a < 'a') return pref[k] + (a == '0' ? 0 : 1);
    return pref[a - 'a'] + pos;
}

namespace graph
{
    vector<int> g[N];
    bitset<N> visited;

    inline void add(int a, int b)
    {
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int dfs(int v)
    {
        int sajz = 1;
        visited[v] = true;

        for (auto i : g[v])
        {
            if (visited[i]) continue;
            sajz += dfs(i);
        }

        return sajz;
    }

    int solve()
    {
        visited &= 0;

        int v0 = dfs(get('0',0)), v1;

        if (visited[get('1', 0)]) return -1;
        
        v1 = dfs(get('1',0));

        int c = 0;

        for (int i = pref[k] + 1; i >= 0; i--)
        {
            if (visited[i]) continue;
            dfs(i);
            c++;
        }

        return c;
    }
}

namespace sol
{
    int dl[27];
    int sl, sr;
    string l, r;

    void numerate(bool side, int& sum, string& s)
    {
        for (auto i : s)
        {
            if (i < 'a')
            {
                t[sum++][side] = {i, 0};
                continue;
            }

            int v = dl[i - 'a'];

            for (int j = 0; j < v; j++)
                t[sum++][side] = {i, j};
        }
    }

    void read()
    {
        sl = sr = 0;

        cin >> k;

        for (int i = 1; i <= k; i++)
        {
            cin >> dl[i - 1];
            pref[i] = pref[i - 1] + dl[i - 1];
        }   
        
        cin >> L >> l;

        numerate(0, sl, l);

        cin >> R >> r;

        numerate(1, sr, r);
    }

    int solve()
    {
        read();

        for (int i = 0; i <= pref[k] + 1; i++)
            graph::g[i].clear();

        if (sl != sr) return -1;

        for (int i = 0; i < sl; i++)
            graph::add(get(t[i][0].fir, t[i][0].sec), 
                       get(t[i][1].fir, t[i][1].sec));

        int c = graph::solve();

        return c;
    }
};

string s = "1";

void mult()
{
    #define getInt(x) ((x)-'0')
    #define getChar(x) char(x + (int)'0')

    int rest = 0;

    for (auto& i : s)
    {
        int val = 2 * getInt(i) + rest;

        i = getChar(val % 10);
        rest = val / 10;
    }

    if (rest != 0)
        s.push_back(getChar(rest));

    #undef getInt
    #undef getChar
}

string& __str__()
{
    reverse(all(s));
    return s;
}
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    int __t;
    cin >> __t;

    while (__t--)
    {
        //cerr << sol::solve() << '\n';

        int c = sol::solve();

        if (c == -1)
        {
            cout << "0\n";
            continue;
        }

        s = "1";

        while (c--)
            mult();
        cout << __str__() << '\n';
    }
}