#include <bits/stdc++.h>

using namespace std;

int t[1000005];
deque<pair<int, int>> spel, niespel;

void push(int i, int s)
{
    if (t[i] < t[s])
    {
        while (spel.size())
        {
            if (spel.back().first > t[i])
                break;
            spel.pop_back();
        }
        spel.push_back({t[i], i});
    }
    else
    {
        while (niespel.size())
        {
            if (niespel.back().first > t[i])
                break;
            niespel.pop_back();
        }
        niespel.push_back({t[i], i});
    }
}

void repair(int i)
{
    while (spel.size())
    {
        if (spel.front().first < t[i])
            break;

        int temp = spel.front().second;
        spel.pop_front();
        push(temp, i);
    }

    while (niespel.size())
    {
        if (niespel.back().first >= t[i])
            break;

        int temp = niespel.back().second;
        niespel.pop_back();
        push(temp, i);
    }
}

void pop(int i)
{
    if (spel.size())
        if (spel.front().second == i)
            spel.pop_front();
    if (niespel.size())
        if (niespel.front().second == i)
            niespel.pop_front();
}

int getMax()
{
    if (!spel.empty())
    {
        return spel.front().second;
    }
    else
    {
        return niespel.front().second;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n, z;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> t[i];

    cin >> z;

    while (z--)
    {
        int k, c = 0, i = 0, j = 1;
        cin >> k;

        while (i < n - 1)
        {

            while (j - i <= k && j <= n - 1)
                push(j++, i);

            int maks = getMax(), temp = i;

            while (temp <= maks)
                pop(temp++);

            if (t[maks] >= t[i])
            {
                c++;
                i = maks;
                spel = niespel;
                niespel.clear();
            }
            else
            {
                i = maks;
                repair(maks);
            }

            j = max(i + 1, j);
        }

        cout << c << '\n';

        niespel.clear();
        spel.clear();
    }
}