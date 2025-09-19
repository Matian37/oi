#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;


const int N = 1e6 + 5;
bool isPath = true;
int n;

namespace pth
{
    ull nxt[N], prev[N], cst[N], l[N], r[N];

    int solvePath()
    {
        for (int i = 2; i <= n; i++)
            prev[i] = nxt[i - 1];

        int j = 1;
        ull sum = cst[1];

        for (int i = 1; i <= n; i++)
        {
            while (j <= n)
            {
                if (nxt[j] < sum) break;
                sum += cst[++j];
            }
            r[i] = j;

            if (i == j)
            {
                j = i + 1;
                sum = cst[j];
            }
            else
                sum -= cst[i];
        }

        j = n;
        sum = cst[n];

        for (int i = n; i >= 1; i--)
        {
            while (j >= 1)
            {
                if (prev[j] < sum) break;
                sum += cst[--j];
            }
            l[i] = j;

            if (i == j)
            {
                j = i - 1;
                sum = cst[j];
            }
            else
                sum -= cst[i];
        }


        int result = 0, i = 1;

        while (i <= n)
        {
            i = r[i];
            int sr = i;

            while (i + 1 <= n)
            {
                if (l[i + 1] > sr) break;
                i++;
            }

            i++;
            result++;
        }

        return result;
    }
}

namespace gr
{
    vector<int> graph[N];
    int dp[N][2], b, w;

    void dfs(int v, int p, bool color)
    {
        if (!color) b++;
        else w++;

        for (auto i : graph[v])
        {
            if (i == p) continue;
            dfs(i, v, !color);
        }
    }

    int solveGraph()
    {
        dfs(1, -1, false);

        return min(b, w);
    }
}

void read()
{
    vector<pair<pair<int,int>, ull>> tmp;

    cin >> n;
    
    for (int i = 1; i <= n; i++)
        cin >> pth::cst[i];

    for (int i = 1; i <= n - 1; i++)
    {
        int a, b;
        ull w;
        cin >> a >> b >> w;

        if (a + 1 != b)
            isPath = false;
        tmp.push_back({{a,b},w});
    }

    if (isPath)
        for (int i = 0; i < n - 1; i++)
            pth::nxt[tmp[i].first.first] = tmp[i].second;
    else
        for (int i = 0; i < n - 1; i++)
        {
            gr::graph[tmp[i].first.first].push_back(tmp[i].first.second);
            gr::graph[tmp[i].first.second].push_back(tmp[i].first.first);
        }
}

void solvePath()
{

}

int main()
{
    read();

    if (isPath)
        cout << pth::solvePath();
    else
        cout << gr::solveGraph();
}