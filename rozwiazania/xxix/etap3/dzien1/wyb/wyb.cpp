#include <bits/stdc++.h>

using namespace std;

constexpr int K = 5;

int temp[K];

inline void update_table(char* A, char* B, int* cnt)
{
    for (int i = 0; i < K; i++)
    {
        temp[i] = 0;
        A[i] = B[A[i]];
    }
    for (int i = 0; i < K; i++)
        temp[B[i]] += cnt[i]; 
    for (int i = 0; i < K; i++)
        cnt[i] = temp[i];
}

inline __attribute__((always_inline)) void move_table(char* A, char st, char en)
{
    for (int i = 0; i < K; i++)
        if (A[i] == st)
            A[i] = en;
}

namespace tree
{
    constexpr int base = 1 << 20;
    char changes[base * 2][K], to_push[base * 2][K];
    int cnt[base * 2][K];

    void init(string& s)
    {
        function<void(int)> _init = [&](int v) -> void
        {
            for (int i = 0; i < K; i++)
                changes[v][i] = to_push[v][i] = i;

            if (v >= base)
            {
                if (v - base >= int(s.size()))
                    return;
                cnt[v][s[v - base] - 'a'] = 1;
                return;
            }

            _init(v*2);
            _init(v*2+1);

            for (int i = 0; i < K; i++)
                cnt[v][i] = cnt[v*2][i] + cnt[v*2+1][i];
        };

        _init(1);
    }

    void push(int v)
    {
        if (v >= base) return;

        update_table(changes[v * 2], to_push[v], cnt[v * 2]);
        update_table(changes[v * 2 + 1], to_push[v], cnt[v * 2 + 1]);
        update_table(to_push[v * 2], to_push[v], temp);
        update_table(to_push[v * 2 + 1], to_push[v], temp);

        for (int i = 0; i < K; i++)
            to_push[v][i] = i;
    }

    void update(int k, char _A, char _B)
    {
        char st = _A - 'a', en = _B - 'a';

        function<void(int)> _update = [&](int v)
        {
            if (k == 0) return;

            if (cnt[v][st] <= k)
            {
                move_table(changes[v], st, en);
                move_table(to_push[v], st, en);

                cnt[v][en] += cnt[v][st];
                k -= cnt[v][st];
                cnt[v][st] = 0;

                return;
            }

            push(v);
            _update(v * 2);
            _update(v * 2 + 1);

            for (int i = 0; i < K; i++)
                cnt[v][i] = cnt[v * 2][i] + cnt[v * 2 + 1][i];
        };

        _update(1);
    }

    void print_res(string& s)
    {
        function<void(int,int,int)> _dfs = [&](int v, int a, int b){
            if (a >= int(s.size())) return;
            if (v >= base)
            {
                cout << char('a' + changes[v][s[v - base] - 'a']);
                return;
            }

            int mid = (a + b) / 2;

            push(v);
            _dfs(v * 2, a, mid);
            _dfs(v * 2 + 1, mid+1, b);
        };

        _dfs(1, 0, base - 1);

        cout << '\n';
    }
}

namespace sol
{
    int n, m;
    string s;

    void read()
    {
        cin >> n >> m >> s;
    }

    void solve()
    {
        tree::init(s);

        //for (int i = 0; i < K; i++)
        //    cout << tree::cnt[1][i] << ' ';
        // tree::print_res(s);

        while (m--)
        {
            int k;
            char a, b;
            cin >> k >> a >> b;
            tree::update(k, a, b);
            //for (int i = 0; i < K; i++)
            //    cout << tree::cnt[1][i] << ' ';
            //tree::print_res(s);
        }

        tree::print_res(s);
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