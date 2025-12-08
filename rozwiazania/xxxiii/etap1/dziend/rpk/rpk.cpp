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

template<typename T>
using V2D = vector<vector<T>>;
using MOVE = pair<ii, ii>;
using SMOVE = pair<int, ii>;

inline int signum(int x)
{
    return (x > 0) - (x < 0);
}

inline ii operator+(ii a, ii b)
{
    return {a.fir + b.fir, a.sec + b.sec};
}

constexpr int N = 105, K = 2505;

#define UP ii{-1, 0}
#define LEFT ii{0, -1}
#define RIGHT ii{0, 1}
#define DOWN ii{1, 0}

#define dist(x, y, p) (abs((x)-(p).first)+abs((y)-(p).second))

constexpr int get_id(ii a)
{
    if (a.fir == -1) return 0;
    if (a.fir == 1) return 3;
    if (a.sec == -1) return 1;
    return 2;
}

namespace pzl
{
    vector<MOVE> res;
    ii pos[K];
    V2D<int> p;
    int m;

    #define ARR(x, y) x[y.fir][y.sec]
    #define START ii{len(p) - 1, len(p) - 1}

    // COST: 1
    inline void do_move(ii a, ii b)
    {
        if (ARR(p, a) != 0)
            swap(a, b);

        #ifdef LOCAL
        assert(ARR(p, b) != 0);
        #endif
        res.push_back({a, b});

        swap(ARR(p, a), ARR(p, b));

        pos[ARR(p, a)] = a;
        pos[ARR(p, b)] = b;
    }

    // COST: 1
    inline void zero_move(ii& curr, ii dir)
    {
        ii nxt = curr + dir;
        
        int &v = ARR(p, curr), &w = ARR(p, nxt);

        res.push_back({curr, nxt});

        if (v == w)
            pos[v] = nxt;
        else
            swap(pos[v], pos[w]),
            swap(v, w);
        curr = nxt;
    }

    // COST: |Delta X| + |Delta Y|
    inline void zero_goto(ii& curr, ii dest, bool firstY = false)
    {
        #ifdef LOCAL
        assert(ARR(p, curr) == 0);
        #endif 

        auto dx = curr.fir < dest.fir ? DOWN : UP;
        auto dy = curr.sec < dest.sec ? RIGHT : LEFT;

        if (firstY)
            while (curr.sec != dest.sec)
                zero_move(curr, dy);

        while (curr.fir != dest.fir)
            zero_move(curr, dx);

        while (curr.sec != dest.sec)
            zero_move(curr, dy);
    }

    static const ii offset[] = {
        RIGHT, // UP
        DOWN, // LEFT
        RIGHT + DOWN, // RIGHT
        RIGHT + DOWN // DOWN
    };

    static const ii cycle_plan[][4] = {
        {UP, LEFT, DOWN, RIGHT}, // UP
        {LEFT, UP, RIGHT, DOWN}, // LEFT
        {UP, LEFT, DOWN, RIGHT}, // RIGHT
        {LEFT, UP, RIGHT, DOWN} // DOWN
    };

    static const ii nxt_plan[] = {UP, LEFT, RIGHT, DOWN};
    static const ii prv_plan[] = {DOWN, RIGHT, LEFT, UP};

    // COST: 2 * (Delta El_X + DElta El_Y) + 12
    void move_el(ii el, ii dir, int l)
    {
        if (l == 0)
            return;

        const int id = get_id(dir);
        ii curr = START, _offset = offset[id];
        bool reverse = false;

        if (el.sec + _offset.sec == m)
        {
            _offset = LEFT + (dir == DOWN ? DOWN : ii{0,0});
            reverse = true;
        }

        zero_goto(curr, el + _offset, reverse);

        for (int _ = 0; _ < l; _++)
        {
            for (int i = 0; i < 4; i++)
            {
                auto curr_move = cycle_plan[id][i];

                if (reverse)
                    if (curr_move == LEFT || curr_move == RIGHT)
                        curr_move = (curr_move == LEFT ? RIGHT : LEFT);

                zero_move(curr, curr_move);
            }

            if (_ != l - 1)
                zero_move(curr, nxt_plan[id]);
        }

        for (int i = 0; i < l - 1; i++)
            zero_move(curr, prv_plan[id]);

        zero_goto(curr, START);
    }

    // COST: 2*(M-start), where 0 <= start, M = n/2
    //       n-2*start
    void cycle(int start, bool clockwise)
    {
        ii curr = START;

        if (clockwise)
            zero_move(curr, UP);

        for (int i = 0; i < m-start-1; i++)
            zero_move(curr, LEFT);

        zero_move(curr, clockwise ? DOWN : UP);

        for (int i = 0; i < m-start-1; i++)
            zero_move(curr, RIGHT);

        if (!clockwise)
            zero_move(curr, DOWN);
    }

    // COST: 0
    inline bool ok_rot()
    {
        int last = 0;

        for (int i = m - 2; i < m; i++)
        {
            for (int j = m - 2; j < m; j++)
            {
                int val = (p[i][j] == 0 ? INT32_MAX : p[i][j]);

                if (last > val)
                    return false;
                
                self(max, last, val);
            }
        }

        return true;
    }

    ii find_zero(int a)
    {
        for (int i = a; i < m; i++)
        {
            for (int j = m - 2; j < m; j++)
            {
                if (p[j][i] == 0)
                    return {j, i};
            }
        }
        exit(1);
    }

    // MAXCOST: 20
    bool solve_box()
    {
        int cz = 0;

        for (int i = m-2; i < m; i++)
            for (int j = m-2; j < m; j++)
                cz += (p[i][j] == 0);

        if (cz == 1)
        {
            int cnt = 5;

            while (cnt--)
            {
                if (ok_rot())
                    break;

                ii curr = START;

                for (auto dir : {UP, LEFT, DOWN, RIGHT})
                    zero_move(curr, dir);
            }
            
            return cnt != -1;
        }
        else if (cz == 2)
        {
            ii curr = {m-2, m-1};

            if (ARR(p, curr) == 0)
                do_move(curr, curr+LEFT);
            curr.sec--;

            if (ARR(p, curr) == 0)
                do_move(curr, curr+DOWN);
            curr.fir++;

            if (p[m-2][m-2] < p[m-2][m-1])
                return true;

            curr = {m-2, m-1};

            do_move(curr, curr+DOWN);
            curr.fir++;

            do_move(curr, curr+LEFT);
            curr.sec--;

            do_move({m-2,m-2}, {m-2, m-1});

            do_move(curr, curr+UP);
            curr.fir--;

            return true;
        }
        else if (cz == 3)
        {
            ii curr = {-1, -1};

            for (int i = 0; i < 4; i++)
            {
                ii _curr = {m - 2 + i / 2, m - 2 + i % 2};
                
                if (ARR(p, _curr) == 0)
                    continue;

                curr = _curr;
                break;
            }

            while (curr.fir != m - 2)
            {
                ii old = curr;
                curr.fir--;
                do_move(old, curr);
            }
            while (curr.sec != m - 2)
            {
                ii old = curr;
                curr.sec--;
                do_move(old, curr);
            }

            return true;
        }
        else
        {
            #ifdef LOCAL
            assert(cz == 4);
            #endif
            return true;
        }
    }

    // COST: 583350 + 1375*eps
    // MAX COST (propably not possible): 624600
    vector<MOVE>* calc(V2D<int>& _p, int k)
    {
        res.clear();
        p = _p;
        m = len(p);

        if (k == len(p)*len(p))
        {
            bool sorted = [&]()
            {
                for (int i = 0; i < len(p)*len(p); i++)
                    if (p[i / len(p)][i % len(p)] != i+1)
                        return false;
                return true;
            }();

            if (sorted)
                return &res;
            return nullptr;
        }

        for (int i = 0; i < m*m; i++)
        {
            int x = i / m, y = i % m;
            pos[p[x][y]] = {x, y};
        }

        // MAXCOST: 12000000
        // d=199,
        // sum i: 1 -> 50 [i * (d + eps - i)] = 83330 + 1275 * eps
        for (int i = 1; i <= min(m*(m-2), k); i++)
        {
            int y = (i - 1) % m, x = (i - 1) / m;

            if (pos[i] == ii{x, y})
                continue;

            x += (y == m - 1);

            auto dy = pos[i].sec < y ? RIGHT : LEFT;
            auto dx = pos[i].fir < x ? DOWN : UP;

            if (pos[i].fir == m - 1)
                move_el(pos[i], dx, 1);

            move_el(pos[i], dy, abs(y-pos[i].sec));
            move_el(pos[i], dx, abs(x-pos[i].fir));

            // fix case when y = m - 1
            if (y != m - 1)
                continue;

            ii zero = START;

            ii p1 = {zero.fir, pos[i].sec + 2 * LEFT.sec}, 
               p2 = {pos[i].fir + UP.fir, pos[i].sec + 2 * LEFT.sec};

            zero_goto(zero, p1);
            zero_goto(zero, p2);
            zero_move(zero, RIGHT);

            for (auto dir : {RIGHT, DOWN, LEFT, UP})
                zero_move(zero, dir);

            zero_move(zero, LEFT);
            zero_goto(zero, p1);
            zero_goto(zero, START);
        }

        int rem = k-m*(m-2);

        // MAXCOST: m = 50
        // cycle_cost * usages_per_el * elements
        // n*n/2*n + n*eps
        // 500000 + 100*eps
        for (int i = 0; i < min(m - 2, rem); i++)
        {
            int up = m*(m-2) + i + 1, down = up + m;

            if (up > k)
                break;

            while (pos[up] != ii{m-2, i})
                cycle(i, pos[up].first == m - 1);

            if (down > k)
            {
                auto zp = find_zero(i);

                if (zp == ii{m - 1, i})
                    continue;

                down = K - 1;
                p[zp.fir][zp.sec] = K - 1;
                pos[K - 1] = zp;
            }
            else if (pos[down] == ii{m-1, i})
                continue;

            while (pos[down] != ii{m-2, i+1})
                cycle(i+1, pos[down].first == m - 1);

            ii curr = START;

            zero_move(curr, UP);
            zero_move(curr, UP);
            zero_goto(curr, ii{m-3, i});

            for (auto dir : {DOWN, RIGHT, DOWN, LEFT, UP, UP})
                zero_move(curr, dir);

            zero_goto(curr, START+UP+UP);
            zero_move(curr, DOWN);
            zero_move(curr, DOWN);

            if (down == K-1)
                ARR(p, pos[down]) = 0;
        }

        // COST: 20
        bool ok = solve_box();

        if (!ok)
            return nullptr;

        return &res;
    }
}

namespace sol
{
    int n, k, m;

    V2D<int> idx(ii p[])
    {
        bitset<K> visited;
        V2D<int> gr(m, vector<int>(m, 0));

        for (int nr = 0; nr < m*m; nr++)
        {
            int rnr = -1, x = 2 * (nr / m), y = 2 * (nr % m);

            for (int j = 1; j <= k; j++)
            {
                if (visited[j])
                    continue;

                if (rnr == -1)
                {
                    rnr = j;
                    continue;
                }

                int dcurr = dist(x, y, p[j]), 
                    dbest = dist(x, y, p[rnr]);

                if (dcurr < dbest)
                    rnr = j;
                else if (dcurr == dbest && p[j].sec > p[rnr].sec)
                    rnr = j;
            }

            if (rnr == -1)
                continue;

            visited[rnr] = true;
            gr[x / 2][y / 2] = rnr;
        }

        return gr;
    }

    // MAX COST: DeltaY
    inline void _move_Y(int rc, int y, ii& old, vector<SMOVE>& moves)
    {
        int mv = old.sec < y ? 1 : -1;
        while (old.sec != y)
        {
            old.sec += mv;
            moves.push_back({rc, old});
        }
    }

    // MAX COST: DeltaX
    inline void _move_X(int rc, int x, ii& old, vector<SMOVE>& moves)
    {
        int mv = old.fir < x ? 1 : -1;
        while (old.fir != x)
        {
            old.fir += mv;
            moves.push_back({rc, old});
        }
    }

    // MAX COST: 245000
    vector<SMOVE> gen_idx_moves(V2D<int>& p, ii* pos, int* rind)
    {
        vector<SMOVE> moves;

        for (int i = 0; i < len(p); i++)
        {
            for (int j = 0; j < len(p); j++)
            {
                if (p[i][j] == 0)
                    continue;

                int x = 2 * i, y = 2 * j;

                int c =  p[i][j], rc = rind[c];
                ii& old = pos[rc];

                if (old.sec >= y)
                {
                    _move_X(rc, x, old, moves);
                    _move_Y(rc, y, old, moves);
                }
                else
                {
                    if (y - 1 == old.sec)
                    {
                        old = old + ii{-1, 1};
                        moves.push_back({rc, old});
                    }

                    _move_Y(rc, y, old, moves);
                    _move_X(rc, x, old, moves);
                }
            }
        }

        return moves;
    }

    void read_pos(ii t[])
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                int c;
                cin >> c;

                if (c != 0) 
                    t[c] = {i, j};
            }   
        }
    }

    vector<SMOVE> res;
    int ind[K], rind[K];
    ii st[K], en[K], _cp[K];

    void read()
    {
        cin >> n >> k;

        m = (n+1)/2;

        read_pos(st);
        read_pos(en);

        bool ok = [&]()
        {
            for (int i = 1; i <= k; i++)
                if (st[i] != en[i])
                    return false;
            return true;
        }();

        if (ok)
        {
            cout << "TAK\n0\n";
            exit(0);
        }
    }

    inline void rmove(int c, ii dir)
    {
        st[c] = st[c] + dir;
        res.push_back({c, st[c]});
    }

    void print()
    {
        cout << "TAK\n";
        cout << len(res) << '\n';
        for (auto i : res)
            cout << i.fir << ' ' << 1 + i.sec.fir << ' ' << 1 + i.sec.sec << '\n';
        exit(0);
    }

    // MAX COST: 791200+eps
    void solve()
    {
        V2D<int> start = idx(st), end = idx(en);

        // convert positions into grouped ones
        int cnt = 0;
        for (auto& i : end)
        {
            for (auto& j : i)
            {
                if (j == 0)
                    continue;

                ind[j] = ++cnt;
                rind[ind[j]] = j;
                j = ind[j];
            }
        }
        for (auto& i : start)
            for (auto& j : i)
                if (j != 0)
                    j = ind[j];

        // add moves (from start to group position)
        // MAX COST: sum of distances <=> 83300
        for (auto i : gen_idx_moves(start, st, rind))
            res.push_back(i);
                
        // add moves (before grouped)
        auto moves = pzl::calc(start, k);

        if (moves == nullptr && m*m-1==k && n % 2 == 0)
        {
            int ld = rind[start[m - 1][m - 2]], 
                pg = rind[start[m - 2][m - 1]], 
                lg = rind[start[m - 2][m - 2]];

            #define repeat(X, Y, K) for (int _ = 0; _ < K; _++) rmove(X, Y)
            repeat(ld, DOWN, 1);
            repeat(pg, RIGHT, 1);
            repeat(lg, DOWN + RIGHT, 2);
            repeat(pg, LEFT, 3);
            repeat(lg, UP, 2);
            repeat(ld, UP, 1);

            swap(start[m - 2][m - 2], start[m - 2][m - 1]);
            moves = pzl::calc(start, k);
        }

        if (moves == nullptr)
        {
            cout << "NIE\n";
            exit(0);
        }

        // MAX COST: 624600+eps
        for (auto [curr, nxt] : *moves)
        {
            int c = ARR(start, nxt);

            if (c == 0 || c == K-1)
                continue;

            int rid = rind[c];
            ii& rpos = st[rid];

            int dx = signum(curr.fir - nxt.fir);
            int dy = signum(curr.sec - nxt.sec);

            for (int l = 0; l < 2; l++)
            {
                rpos.fir += dx;
                rpos.sec += dy;
                res.push_back({rid, rpos});
            }

            swap(ARR(start, curr), ARR(start, nxt));
        }

        #ifdef LOCAL
        assert(start == end);
        #endif

        // add moves (de-grouping)
        // MAX COST: sum of distances <=> 83300
        copy(en, en+k+1, _cp);
        auto mvs = gen_idx_moves(end, en, rind);

        vector<SMOVE> tmp;
        for (auto i : mvs)
        {
            tmp.push_back({i.fir, _cp[i.fir]});
            _cp[i.fir] = i.sec;
        }

        reverse(all(tmp));
        for (auto& i : tmp)
            res.push_back(i);

        print();
    }
};

#ifndef DEBUG
int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
 
    sol::read();
    sol::solve();
}
#else 
int main()
{
    V2D<int> x = {
        {3, 1},
        {2, 0},
    };

    cout << len(x) << '\n';
    for (int i = 0; i < len(x); i++)
    {
        for (int j = 0; j < len(x); j++)
            cout << x[i][j] << ' ';
        cout << '\n';
    }
    
    auto res = *pzl::calc(x, 3);
    cout << len(res) << '\n';
    for (auto [a, b] : res)
        cout << a.fir << ' ' << a.sec << " " << b.fir << ' ' << b.sec << '\n';
}
#endif