#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

#define pbds __gnu_pbds
#define fir first
#define sec second

using ll = unsigned long long;
using ull = unsigned long long;
using ii = pair<int,int>;

#define all(x) (x).begin(),(x).end()

ii moves[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

namespace sol
{
    const int N = 1e3+5;
    bool col[N], row[N]; // good
    int X, Y, z;

    void read()
    {
        cin >> X >> Y >> z;

        for (int i = 1; i <= X; i++)
        {
            char c;
            cin >> c;
            col[i] = (c == '+');
        }

        for (int i = 1; i <= Y; i++)
        {
            char c;
            cin >> c;
            row[i] = (c == '+');
        }
    }

    bitset<N> visited[N];

    int bfs(ull _budget)
    {
        for (int i = 1; i <= X; i++)
            for (int j = 1; j <= Y; j++)
                visited[i][j] = false;

        queue<pair<ii, int>> q;

        for (int i = 1; i <= X; i++)
        {
            for (int j = 1; j <= Y; j++)
            {
                if (!col[i] && !row[j]) continue;
                q.push({{i, j}, 0});
            }
        }

        ull budget = _budget;
        int cnt = 0;

        while (int(q.size()))
        {
            auto curr = q.front();
            q.pop();

            if (visited[curr.fir.fir][curr.fir.sec])
                continue;
            if (curr.sec > budget)
                break;

            budget -= curr.sec;
            cnt++;
            visited[curr.fir.fir][curr.fir.sec] = true;

            for (ii i : moves)
            {
                ii pos = {curr.fir.fir + i.fir, curr.fir.sec + i.sec};

                if (pos.fir <= 0 || pos.sec <= 0)
                    continue;
                if (pos.fir > X || pos.sec > Y)
                    continue;
                if (visited[pos.fir][pos.sec])
                    continue;
                
                q.push({pos, curr.sec + 1});
            }
        }

        return cnt;
    }

    void solve()
    {
        while (z--)
        {
            char type;
            cin >> type;

            ull c;
            cin >> c;

            if (type == 'Z')
            {
                cout << bfs(c) << '\n';
            }
            else if (type == 'N')
            {
                col[c] = !col[c];
            }
            else
            {
                row[c] = !row[c];
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    sol::read();
    sol::solve();
}