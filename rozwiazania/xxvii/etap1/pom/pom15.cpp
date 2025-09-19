#include <bits/stdc++.h>

using namespace std;

int pref[100005], suff[100005];

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        string a, b, c;
        int k;
        cin >> a >> b >> k;

        c = a;

        int nierow = 0;

        for (int i = 0; i < a.size(); i++)
        {
            pref[i] = nierow;

            if (a[i] != b[i])
                nierow++;
        }

        int zwieksz = 0;

        for (int i = a.size() - 1; i >= 0; i--)
        {
            if (b[i] - 48 < 9)
                zwieksz++;
            suff[i] = zwieksz;
        }

        int sol = -1;

        for (int i = a.size() - 1; i >= 0; i--)
        {
            bool wiek = a[i] >= b[i];

            if (b[i] == '0')
                continue;

            if (pref[i] + wiek <= k && pref[i] + suff[i + 1] + 1 >= k)
            {
                sol = i;
                break;
            }
        }

        if (sol == -1)
        {
            cout << -1 << '\n';
            continue;
        }

        for (int i = 0; i < sol; i++)
        {
            if (c[i] != b[i])
            {
                c[i] = b[i];
                k--;
            }
        }

        if (k > 0 && c[sol] != b[sol] - 1)
        {
            c[sol] = b[sol] - 1;
            k--;
        }

        for (int i = sol + 1; i < a.size(); i++)
        {
            if (k == 0)
                break;

            if (c[i] != '9')
            {
                c[i] = '9';
                k--;
            }
        }

        cout << c << '\n';
    }
}