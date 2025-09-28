#include <bits/stdc++.h>

using namespace std;

pair<int, int> t[1000002];

deque<int> dqMaks;

void push(int i)
{
    while (dqMaks.size())
    {
        if (t[dqMaks.back()].first > t[i].first)
            break;
        dqMaks.pop_back();
    }

    dqMaks.push_back(i);
}

void pop(int i)
{
    if (dqMaks.size())
        if (dqMaks.front() == i)
            dqMaks.pop_front();
}

int getMax()
{
    if (dqMaks.empty())
        return INT32_MIN;
    return t[dqMaks.front()].first;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> t[i].first >> t[i].second;

    int i = 0, j = 1, k = t[i].first, c = 1, maks = 1;
    push(i);

    while (i < n)
    {
        while (j < n)
        {
            if (k > t[j].second)
                break;
            push(j);

            if (k <= getMax())
                k = getMax();
            j++;
            c++;
        }

        pop(i++);
        maks = max(maks, c--);

        if (c == 0)
        {
            if (j < n)
            {
                k = t[j].first;
                c++;
                push(j++);
            }
            else
                break;
        }
        else
            k = getMax();
    }

    cout << maks;
}