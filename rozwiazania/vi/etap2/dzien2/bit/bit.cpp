#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long

using namespace std;

bool visited[200][200];
int result[200][200];
bool t[200][200];
int n, m;

void BFS(int n, int m)
{
    queue<pair<int, pair<int, int>>> q;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (t[i][j] == 1)
                q.push({0, {i, j}});
        }
    }

    while (!q.empty())
    {
        pair<int, pair<int, int>> acc = q.front();
        q.pop();

        if (visited[acc.second.first][acc.second.second])
            continue;

        visited[acc.second.first][acc.second.second] = true;
        result[acc.second.first][acc.second.second] = acc.first;

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (j != 0 && i != 0)
                    continue;
                if (acc.second.first + i < 0 || acc.second.first + i >= n)
                    break;
                if (acc.second.second + j < 0 || acc.second.second + j >= m)
                    continue;
                if (visited[acc.second.first + i][acc.second.second + j])
                    continue;
                if (t[acc.second.first + i][acc.second.second + j] == 1)
                    continue;

                q.push({acc.first + abs(i) + abs(j), {acc.second.first + i, acc.second.second + j}});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        string a;
        cin >> a;

        for (int j = 0; j < m; j++)
        {
            t[i][j] = a[j] - 48;
        }
    }

    BFS(n, m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << result[i][j] << ' ';
        cout << '\n';
    }
}