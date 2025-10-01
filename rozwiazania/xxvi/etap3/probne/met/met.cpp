//
// Mateusz Pietrowcow
//
 
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


namespace sol
{
    const int N = 3e6+5;
    vector<int> g[N];
    int wsk[N];
    int n, k;

    void read()
    {
        cin >> n >> k;

        for (int i = 0; i < n - 1; i++)
        {
            int a, b;
            cin >> a >> b;

            g[a].push_back(b);
            g[b].push_back(a);
            wsk[a]++, wsk[b]++;
        }
    }

    int leaves[N];
    bitset<N> marked;

    queue<ii> l;

    void rem_leaf(int v, int depth)
    {
        n--;
        marked[v] = true;

        for (auto i : g[v])
        {
            if (marked[i]) continue;

            wsk[i]--;

            if (wsk[i] <= 1)
                l.push({i, depth+1}), 
                leaves[depth+1]++, 
                marked[i] = true;
        }

        wsk[v] = 0;
    }

    
    void print(int depth)
    {
        if (leaves[depth] > k)
            return;

        vector<int> verts;

        while (l.size())
        {
            if (l.front().sec != depth)
                break;
            verts.push_back(l.front().fir);
            l.pop();
        }

        if (len(verts) == 1)
            verts.push_back(g[verts[0]][0]);

        cout << depth << ' ' << len(verts) << '\n';

        sort(all(verts));
        for (auto i : verts)
            cout << i << ' ';

        exit(0);
    }

    void solve()
    {
        for (int i = 1; i <= n; i++)
        {
            if (wsk[i] != 1) continue;
            l.push({i, 0}), leaves[0]++;
        }

        int depth = 0;
        while (n)
        {
            print(depth);

            while (len(l)) 
            {
                auto curr = l.front();

                if (curr.sec != depth)
                    break;
                l.pop();

                rem_leaf(curr.fir, curr.sec);
            }

            depth += 1;
        }

        cerr << "FAILED\n";
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