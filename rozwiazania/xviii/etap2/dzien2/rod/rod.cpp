//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

#pragma GCC optimize("Os")

using namespace std;

using ll = long long;
using uint = unsigned int;
using ull = unsigned long long;
using ii = pair<int,int>;
using uii = pair<uint,uint>;
using pll = pair<ll,ll>;
using pull = pair<ull,ull>;
#define int128 __int128_t
#define uint128 __uint128_t

#define pbds __gnu_pbds
#define cxx __gnu_cxx

#define MOD 1000000007
#define MODLL 1000000007LL
#define MODULL 1000000007ULL

// best primes in te galaxy
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

struct node
{
    int left,right,val,sajz;
    char h;

    node(int __val) : left(0), right(0), val(__val), sajz(1), h(1){};
};

const int N = 1e6+5;
node* val[N];
vector<node*> el;

struct avl
{
    int root = 0;

    inline int __size(int x)
    {
        if (x == 0) return 0;
        return val[x]->sajz;
    }

    inline int __h(int x)
    {
        if (x == 0) return 0;
        return val[x]->h;
    }

    inline int __bl(node *x)
    {
        return __h(x->right) - __h(x->left);
    }

    inline int size()
    {
        return __size(root);
    }

    int order_of_key(int x)
    {
        node* curr = val[root];

        int r = 0;

        while (curr != NULL)
        {
            if (x > curr->val) 
            {
                r += __size(curr->left) + 1;
                curr = val[curr->right];
            }
            else
                curr = val[curr->left];
        }

        return r;
    }

    void LR(node* curr, node* parent)
    {
        if (curr == NULL) return;

        node *nw = val[curr->right]; 
        node *T2 = val[nw->left]; 

        // Perform rotation 
        nw->left = curr->val; 
        curr->right = (T2 == NULL ? 0 : T2->val); 


        repair(curr);
        repair(nw);

        if (parent == NULL)
        {
            root = nw->val;
            return;
        }
        if (parent->val < nw->val)
            parent->right = nw->val;
        else
            parent->left = nw->val;
    }

    void RR(node* curr, node* parent)
    {
        if (curr == NULL) return;

        node *nw = val[curr->left]; 
        node *T2 = val[nw->right]; 

        // Perform rotation 
        nw->right = curr->val; 
        curr->left = (T2 == NULL ? 0 : T2->val); 

        repair(curr);
        repair(nw);

        if (parent == NULL)
        {
            root = nw->val;
            return;
        }
        if (parent->val < nw->val)
            parent->right = nw->val;
        else
            parent->left = nw->val;
    }

    inline void repair(node* curr)
    {
        curr->sajz = __size(curr->left) + __size(curr->right) + 1;
        curr->h = max(__h(curr->left), __h(curr->right)) + 1;
    }

    void __insert(node *curr, node* parent, node *x)
    {
        if (x->val < curr->val)
        {
            if (curr->left == 0)
                curr->left = x->val;
            else
                __insert(val[curr->left], curr, x);
        }
        else
        {
            if (curr->right == 0)
                curr->right = x->val;
            else
                __insert(val[curr->right], curr, x);
        }

        repair(curr);

        if (abs(__bl(curr)) <= 1) return;

        if (__bl(curr) < 0)
        {
            if (curr->left != 0)
                if (__bl(val[curr->left]) > 0) 
                    LR(val[curr->left], curr);
            RR(curr, parent);
        }
        else
        {
            if (curr->right != 0)
                if (__bl(val[curr->right]) < 0) 
                    RR(val[curr->right], curr);
            LR(curr, parent);
        }
    }

    inline void insert(int _x) // only for size 0
    {
        val[_x] = new node(_x);
        root = _x;
    }

    void insert(node *x)
    {
        x->h = x->sajz = 1;
        x->left = x->right = 0;
        __insert(val[root], NULL, x);
    }

    void __dfs(node* curr)
    {
        if (curr == NULL)
            return;
        el.push_back(curr);
        __dfs(val[curr->left]);
        __dfs(val[curr->right]);
    }

    vector<node*>& getElements()
    {
        el.clear();
        __dfs(val[root]);
        return el;
    }
};

namespace sol
{
    int n;

    void read()
    {
        cin >> n;
    }
    
    ll r;
    ll inw1 = 0, inw2 = 0;

    avl* dfs()
    {
        int val;
        cin >> val;

        if (val != 0)
        {
            avl* str = new avl();
            str->insert(val);
            return str;
        }

        auto a = dfs(), b = dfs();

        if (a->size() > b->size())
            swap(a,b);
        
        inw1 = inw2 = 0;

        auto el = a->getElements();
        free(a);

        for (auto i : el)
        {
            int w = b->order_of_key(i->val);
            inw1 += w; // right
            inw2 += b->size() - w;
        }
        for (auto i : el)
            b->insert(i);

        r += min(inw1, inw2);

        return b;
    }

    void solve()
    {
        dfs();
        cout << r << '\n';
    }
};
 
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    val[0] = NULL;
 
    sol::read();
    sol::solve();
}