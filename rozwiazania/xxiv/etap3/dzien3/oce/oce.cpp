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

#define pbds __gnu_pbds
#define cxx __gnu_cxx
#define MOD 1'000'000'007
#define MODLL 1'000'000'007LL
#define MODULL 1'000'000'007ULL
#define INF 1'000'000'000
#define INFLL 1'000'000'000'000'000'000LL
#define INFULL 1'000'000'000'000'000'000ULL
#define timeNow() chrono::high_resolution_clock::now().time_since_epoch().count()
#define all(x) x.begin(),x.end()
#define isize(x) (int)(x.size())
#define uisize(x) (uint)(x.size())
#define fir first
#define sec second

template <typename X, typename Y, typename Z>
using hashmap = pbds::gp_hash_table<X,Y,Z,equal_to<X>,pbds::direct_mask_range_hashing<>,pbds::linear_probe_fn<>,pbds::hash_standard_resize_policy<pbds::hash_exponential_size_policy<>,pbds::hash_load_check_resize_trigger<>,true>>;
template <typename X, typename Y, typename Z>
using indexed_set = pbds::tree<X, Y, Z, pbds::rb_tree_tag, pbds::tree_order_statistics_node_update>;

const int N = 1e6 + 5;
const int base = 1 << 20;

namespace tree
{
    ll treeVal[base * 2], treeQ[base * 2];
    pair<ll, int> treeCnt[base * 2];

    void init(int v, int a, int b, int n)
    {
        if (a >= n) treeCnt[v] = {1, 0};
        else treeCnt[v].sec = (min(b, n - 1) - a + 1);

        if (v >= base) return;

        init(v * 2, a, (a + b) / 2, n);
        init(v * 2 + 1, (a + b) / 2 + 1, b, n);
    }

    void push(int v, int a, int b)
    {
        treeQ[v * 2] += treeQ[v];
        treeQ[v * 2 + 1] += treeQ[v];

        int mid = (a + b) / 2;

        treeVal[v * 2] += (mid - a + 1) * treeQ[v];
        treeVal[v * 2 + 1] += (mid - a + 1) * treeQ[v];

        treeCnt[v * 2].fir += treeQ[v];
        treeCnt[v * 2 + 1].fir += treeQ[v];

        treeQ[v] = 0;
    }

    int p, k;
    ll val;

    void __update(int v, int a, int b)
    {
        if (k < a || p > b) return;
        if (p <= a && b <= k)
        {
            treeVal[v] += (b - a + 1) * val;
            treeQ[v] += val;
            treeCnt[v].fir += val;

            return;
        }

        int mid = (a + b) / 2;

        push(v, a, b);

        __update(v * 2, a, mid);
        __update(v * 2 + 1, mid + 1, b);

        treeVal[v] = treeVal[v * 2] + treeVal[v * 2 + 1];

        if (treeCnt[v * 2].fir == treeCnt[v * 2 + 1].fir)
            treeCnt[v] = {treeCnt[v * 2].fir, treeCnt[v * 2].sec + treeCnt[v * 2 + 1].sec};
        else if (treeCnt[v * 2].first < treeCnt[v * 2 + 1].fir)
            treeCnt[v] = {treeCnt[v * 2].fir, treeCnt[v * 2].sec};
        else
            treeCnt[v] = {treeCnt[v * 2 + 1].fir, treeCnt[v * 2 + 1].sec};
    }

    void update(int a, int b, ll v)
    {
        p = a, k = b, val = v;
        __update(1, 0, base - 1);
    }

    int query()
    {
        return (treeCnt[1].fir == 0 ? treeCnt[1].sec : 0);
    }
}

namespace sol
{
    ll t[N];
    int n, q;

    void read()
    {
        cin >> n >> q;

        for (int i = 0; i < n; i++)
            cin >> t[i];
    }
    
    void solve()
    {
        tree::init(1, 0, base - 1, n);

        ll pref = 0;

        for (int i = 0; i < n; i++)
        {
            pref += t[i];
            tree::update(i, i, pref - ((ll)(i + 1) * (i + 2)) / 2);
        }
        
        cout << tree::query() << '\n';

        q--;

        while (q--)
        {
            int a, b;
            cin >> a >> b;
            a--;
            b--;

            tree::update(a, n - 1, t[b] - t[a]);
            tree::update(b, n - 1, t[a] - t[b]);

            swap(t[a], t[b]);

            cout << tree::query() << '\n';
        }
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