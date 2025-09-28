#include <bits/stdc++.h>
#include "glolib.h"

using namespace std;

const int N = 2e5+5;
set<int> ch[N];
int parent[N];
bool visited[N];

int vis_cnt = 0;

int get_moves_parent(int x)
{

    while (!visited[x])
    {
        visited[x] = true;
        vis_cnt += 1;
        ch[parent[x]].erase(x);
        x = parent[x];
    }

    return x;
}

int search_leaf(int x)
{
    while (ch[x].size())
        x = *ch[x].begin();
    return x;
}

int main()
{
    int n = daj_n();

    parent[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        int p = daj_przelozonego(i);
        parent[i] = p;
        ch[p].insert(i);
    }

    int leaf = [&]()
    {
        for (int i = 2; i <= n; i++)
            if (ch[i].empty())
                return i;
    }();

    get_moves_parent(leaf);
    int enemy = ruch(leaf);

    while (vis_cnt != n)
    {
        int p = get_moves_parent(enemy),
            mine = search_leaf(p);

        get_moves_parent(mine);
        enemy = ruch(mine);
    }
}