#include <bits/stdc++.h>
#include "cyklib.hpp"

using namespace std;

#define cs(x) circular_shift(x)

using ii = pair<int,int>;
using ull = long long;

#define fir first
#define sec second

ull pos;

ii init()
{
	ull last = cs(0);
	pos = cs(1);

	int r = 0;

	if (last == pos)
	{
		give_answer(1);
		exit(0);
	}
	else if (last < pos)
	{
		for (int i = 1; true; i *= 2)
		{
			last = pos, pos = cs(i);

			if (last >= pos)
			{
				r += i;
				break;
			}
		}
	}
	else r++;

	last = pos, pos = cs(1);

	if (last > pos)
		return {1, r};
	r++;

	for (int i = 1; true; i *= 2)
	{
		last = pos, pos = cs(i);

		r += i;
		if (last >= pos)
			break;
	}
	
	return {1, r};
}

bool isSmaller(int x)
{
	ull inw[] = {pos, cs(x / 2), cs(x / 2)};
	pos = inw[2];

	int r = 0;

	for (int i = 0; i < 3; i++)
		for (int j = i + 1; j < 3; j++)
			if (inw[i] > inw[j])
				r++;
	return (r + 1) % 2;
}

int main() 
{
	auto r = init();

	while (r.sec - r.fir + 1 > 2)
	{
		int mid = (r.fir + r.sec) / 2;
		mid += mid % 2;

		if (isSmaller(mid)) r.fir = mid + 1;
		else r.sec = mid;
	}

	if (cs(0) == cs(r.fir))
		give_answer(r.fir);
	else
		give_answer(r.sec);
}