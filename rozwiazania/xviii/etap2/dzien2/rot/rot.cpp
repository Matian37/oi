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
    int val;
    int sajz, h;
    node *left, *right;

    node(int __val) : val(__val), sajz(1), h(1), left(NULL), right(NULL){};
};

struct avl
{
    node *root = NULL;

    inline int __size(node* x)
    {
        if (x == NULL) return 0;
        return x->sajz;
    }

    inline int __h(node*x)
    {
        if (x == NULL) return 0;
        return x->h;
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
        node* curr = root;

        int r = 0;

        while (curr != NULL)
        {
            if (x > curr->val) 
            {
                r += __size(curr->left) + 1;
                curr = curr->right;
            }
            else
                curr = curr->left;
        }

        return r;
    }

    void LR(node* curr, node* parent)
    {
        if (curr == NULL) return;

        node *nw = curr->right; 
        node *T2 = nw->left; 

        // Perform rotation 
        nw->left = curr; 
        curr->right = T2; 


        repair(curr);
        repair(nw);

        if (parent == NULL)
        {
            root = nw;
            return;
        }
        if (parent->val < nw->val)
            parent->right = nw;
        else
            parent->left = nw;
    }

    void RR(node* curr, node* parent)
    {
        if (curr == NULL) return;

        node *nw = curr->left; 
        node *T2 = nw->right; 

        // Perform rotation 
        nw->right = curr; 
        curr->left = T2; 

        repair(curr);
        repair(nw);

        if (parent == NULL)
        {
            root = nw;
            return;
        }
        if (parent->val < nw->val)
            parent->right = nw;
        else
            parent->left = nw;
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
            if (curr->left == NULL)
                curr->left = x;
            else
                __insert(curr->left, curr, x);
        }
        else
        {
            if (curr->right == NULL)
                curr->right = x;
            else
                __insert(curr->right, curr, x);
        }

        repair(curr);

        if (abs(__bl(curr)) <= 1) return;

        if (__bl(curr) < 0)
        {
            if (curr->left != NULL)
                if (__bl(curr->left) > 0) 
                    LR(curr->left, curr);
            RR(curr, parent);
        }
        else
        {
            if (curr->right != NULL)
                if (__bl(curr->right) < 0) 
                    RR(curr->right, curr);
            LR(curr, parent);
        }
    }

    inline void insert(int _x) // only for size 0
    {
        root = new node(_x);
    }

    void insert(node *x)
    {
        x->h = x->sajz = 1;
        x->left = x->right = NULL;
        __insert(root, NULL, x);
    }

    vector<node*> el;

    void __dfs(node* curr)
    {
        if (curr == NULL)
            return;
        el.push_back(curr);
        __dfs(curr->left);
        __dfs(curr->right);
    }

    vector<node*>& getElements()
    {
        el.clear();
        __dfs(root);
        return el;
    }
};

namespace sol
{
    const int N = 2e5+5, V = 4e5+5;

    struct info
    {
        int val, left, right;
    };
    
    info vert[V];
    int nr = 1, n;

    void readDfs(int v)
    {
        cin >> vert[v].val;

        if (vert[v].val != 0)
        {
            vert[v].left = vert[v].right = -1;
            return;
        }

        vert[v].left = ++nr;
        readDfs(nr);

        vert[v].right= ++nr;
        readDfs(nr);
    }

    void read()
    {
        cin >> n;

        readDfs(1);
    }
    
    ll r;

    avl* dfs(int v)
    {
        if (vert[v].left == -1)
        {
            avl* str = new avl();
            str->insert(vert[v].val);

            return str;
        }

        auto a = dfs(vert[v].left), b = dfs(vert[v].right);

        if (a->size() > b->size())
            swap(a,b);
        
        ll inw1 = 0, inw2 = 0;

        auto el = a->getElements();

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
        dfs(1);
        cout << r << '\n';
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