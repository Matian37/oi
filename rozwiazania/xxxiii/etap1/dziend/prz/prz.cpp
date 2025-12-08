//
// Mateusz Pietrowcow
//
 
#include <algorithm>
#include <bits/stdc++.h>
#include <bits/extc++.h>

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
#define self(x,y,z) y = x(y,z)


template <typename X, typename Y, typename Z>
using gp_hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using gp_hashmap_safe = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;

template <typename X, typename Y, typename Z>
using cc_hashmap = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using cc_hashmap_safe = pbds::cc_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mod_range_hashing<>,pbds::hash_standard_resize_policy<pbds::hash_prime_size_policy,pbds::hash_load_check_resize_trigger<>,true>>;

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


constexpr int N = 1e6+5;

inline char charify(int x)
{
    return char(x + 'a');
}

using edge = pair<int,char>;

vector<edge> g[N];
edge parent[N];
bool word[N];
int n = 1;

#define ROOT 1

namespace trie
{
    int t[N][26];

    inline int _ensure(int v, int p, int c)
    {
        if (v == 0)
        {
            v = ++n;
            g[p].push_back({v, charify(c)});
        }
        return v;
    }

    void add(string& s)
    {
        int v = ROOT, p = 0;

        while (p < len(s))
        {
            int val = s[p++] - 'a';
            int nxt = _ensure(t[v][val], v, val);

            t[v][val] = nxt;
            parent[nxt] = {v, charify(val)};
            
            v = nxt;
        }
        word[v] = true;
    }
}

int ones[N][2];
ll dp[N][2];

namespace gen
{
    using Seq = list<char>*;

    // Order must persist! A should be done before B
    Seq merge(Seq a, Seq b)
    {
        if (a->size() < b->size())
        {
            while (!a->empty())
            {
                b->push_front(a->back());
                a->pop_back();
            }
            return b;
        }

        while (!b->empty())
        {
            a->push_back(b->front());
            b->pop_front();
        }
        return a;
    }

    vector<edge> gen(int v)
    {
        struct info
        {
            ll diff;
            int vert;
            char c;
        };

        vector<info> turn1;
        for (auto i : g[v])
            turn1.push_back({dp[i.fir][1] - dp[i.fir][0], i.fir, i.sec});

        sort(all(turn1), [&](const info& a, const info& b)
        {
            return a.diff > b.diff;
        });

        vector<edge> vec;
        for (int i = 0; i < len(turn1); i++)
            vec.push_back({turn1[i].vert, turn1[i].c});
        return vec;
    }

    string root_path(int v)
    {
        string s = "";

        while (v != 1)
        {
            s += parent[v].sec;
            v = parent[v].fir;
        }

        reverse(all(s));

        return s;
    }

    Seq construct(int v, bool in_root)
    {
        vector<edge> ch = gen(v);

        Seq res_seq = new list<char>;

        for (int i = 0; i < len(ch); i++)
        {
            auto curr = ch[i];
            bool one = len(ch) - 1 - i < ones[v][in_root];

            auto seq = construct(curr.fir, one);

            // WORD CASE
            if (word[curr.fir])
            {
                if (!one || len(g[curr.fir]) != 0)
                    seq->push_front('T');
                seq->push_front('E');
            }

            // GOING IN
            seq->push_front(curr.sec);

            // GET OUT
            if (i != len(ch) - 1 || !in_root)
            {
                if (!one)
                    seq->push_back('B');
                else
                {
                    for (auto j : root_path(v))
                        seq->push_back(j);
                }
            }

            // add to res_seq
            self(merge, res_seq, seq);
        }

        return res_seq;
    }
}

namespace sol
{
    int w;

    void read()
    {
        cin >> w;

        for (int i = 0; i < w; i++)
        {
            string s;
            cin >> s;
            trie::add(s);
        }
    }

    ll res = 0;
    // vertex, in_root
    
    void dfs(int v, int d)
    {
        int lng = len(g[v]);

        if (word[v])
        {
            if (lng != 0)
                res += 2;
            else
            {
                res += 1;
                dp[v][0] = 1;
                dp[v][1] = 0;
                return;
            }
        }

        vector<ll> turn1;
        ll sum = 0;

        for (auto i : g[v])
        {
            dfs(i.fir, d+1);
            sum += dp[i.fir][0];
            turn1.push_back(dp[i.fir][1] - dp[i.fir][0]);
        }
        sort(all(turn1), greater<ll>());

        dp[v][0] = dp[v][1] = INFLL;
        for (int i = 0; i <= lng; i++)
        {
            ll can = sum + ll(i) * (d - 1) + (2 * lng);
            if (can < dp[v][0])
                dp[v][0] = can, ones[v][0] = i;

            if (i != 0)
            {
                can = sum + ll(i - 1) * (d - 1) + (2 * lng - 1);
                
                if (can < dp[v][1])
                    dp[v][1] = can, ones[v][1] = i;
            }

            if (i != lng)
            {
                sum += turn1.back();
                turn1.pop_back();
            }
        }
    }

    void solve()
    {
        dfs(ROOT, 0);
        auto seq = gen::construct(ROOT, 1);

        cout << res + dp[ROOT][1] << '\n';
        for (auto i : *seq)
            cout << i;
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