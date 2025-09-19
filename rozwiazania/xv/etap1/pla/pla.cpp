//
// Mateusz Pietrowcow
//

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1000000000
#define INFL 1000000000000000000LL
#define Tak cout << "TAK" << '\n'
#define Nie cout << "NIE" << '\n'

using namespace std;

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<long long, long long> pll;
typedef pair<unsigned long long, unsigned long long> pull;

const int base = 1 << 18;

int tree[base * 2];
pair<int,int> blocks[250005];
vector<int> block[250005];

int n;

bool comp(const ii& a, const ii& b)
{
    return a.second < b.second;
}

void update(int pos, int v)
{
    pos += base;
    tree[pos] = v;
    pos /= 2;

    while (pos != 0)
    {
        tree[pos] = min(tree[pos], v);
        pos /= 2;
    }
}

int query(int a, int b)
{
    int r = INT32_MAX;

    a += base - 1;
    b += base + 1;

    while (a / 2 != b / 2)
    {
        if (a % 2 == 0) r = min(r, tree[a + 1]);
        if (b % 2 == 1) r = min(r, tree[b - 1]);
        a /= 2;
        b /= 2;
    }

    return r;
}

void init()
{
    for (int i = 0; i < base * 2; i++)
        tree[i] = INT32_MAX;
    for (int i = 0; i < n; i++)
        update(i, blocks[i].first);
}

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int trash;
        cin >> trash >> blocks[i].first;
        blocks[i].second = i;
    }
}

int dfs(int a, int b)
{
    if (a == b) return 1;

    int minn = query(a, b), r = 1;

    auto p = lower_bound(block[minn].begin(), block[minn].end(), a);

    int start = a;

    while (p != block[minn].end())
    {
        if (*p > b) break;
        else if (start == *p) start = *p + 1;
        else
        {
            r += dfs(start, *p - 1);
            start = *p + 1;
        }
        p++;
    }

    if (start != -1 && start <= b)
        r += dfs(start, b);

    return r;
}

void solve()
{
    sort(blocks, blocks + n);

    int oldV = blocks[0].first, num = 1;
    blocks[0].first = num;

    for (int i = 1; i < n; i++)
    {
        int temp = blocks[i].first;

        if (oldV == blocks[i].first) blocks[i].first = num;
        else {blocks[i].first = ++num; oldV = temp;}
    }

    sort(blocks, blocks + n, comp);

    for (int i = 0; i < n; i++)
        block[blocks[i].first].push_back(i);
    init();

    cout << dfs(0, n - 1);
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    read();
    solve();
}