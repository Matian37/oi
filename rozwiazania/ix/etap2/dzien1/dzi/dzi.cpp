#include <bits/stdc++.h>

using namespace std;

const int N = 2005;
bool t[N][N];
int n;

void read()
{
    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> t[i][j];
}

int up[N][2], ind[N], fu[N], ranks[N], minim[N];
bool active[N];

#define ind(x,y) ((x)*n+(y))

int find(int a)
{
    if (fu[a] == a) return a;
    return fu[a] = find(fu[a]);
}

void Union(int a, int b)
{
    a = find(a), b = find(b);

    if (a == b) return;
    if (ranks[a] < ranks[b]) swap(a, b);

    fu[b] = a;
    ranks[a] += ranks[b];
    minim[a] = min(minim[b], minim[a]);
}

int solve()
{
    int best = 0;

    for (int i = 0; i < n; i++)
    {
        int curr = i % 2, prev = (i + 1) % 2;

        iota(fu, fu+n, 0);
        fill(ranks, ranks+n, 1);
        fill(active, active+n, false);

        for (int j = 0; j < n; j++)
        {
            if (i == 0) {
                up[j][curr] = minim[j] = 0;
                continue;
            }
            if (t[i - 1][j]) {
                up[j][curr] = minim[j] = 0;
                continue;
            }

            minim[j] = up[j][curr] = up[j][prev] + 1;
        }

        iota(ind, ind+n, 0);
        sort(ind, ind+n, [&](const int& a, const int& b)
        {
            return up[a][curr] > up[b][curr];
        });


        for (int _j = 0; _j < n; _j++)
        {
            int j = ind[_j];
            if (t[i][j]) continue;

            if (j != 0)
                if (active[j - 1])
                    Union(j - 1, j);

            if (j != n - 1)
                if (active[j + 1])
                    Union(j + 1, j);

            int fupos = find(j);
            best = max(best, ranks[fupos] * (minim[fupos] + 1));
            active[j] = true;
        }
    }

    return best;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    read();
    cout << solve() << '\n';
}