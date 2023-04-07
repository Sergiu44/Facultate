#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

long long orientare_puncte(pair<long long, long long> x, pair<long long, long long> y)
{
    return x.first * y.second - y.first * x.second;
}

int inside(long long a, long long b, vector<pair<long long, long long>> &P, long long n)
{
    pair<long long, long long> p1, p2, pq;
    p1.first = P[P.size() - 1].first - P[0].first;
    p1.second = P[P.size() - 1].second - P[0].second;

    p2.first = P[1].first - P[0].first;
    p2.second = P[1].second - P[0].second;

    pq.first = a - P[0].first;
    pq.second = b - P[0].second;

    if (!(orientare_puncte(p1, pq) <= 0 && orientare_puncte(p2, pq) >= 0))
        return 0;

    long long st = 1, dr = n - 1;
    while (st <= dr)
    {
        long long mij = (st + dr) / 2;
        pair<long long, long long> c;
        c.first = P[mij].first - P[0].first;
        c.second = P[mij].second - P[0].second;

        if (orientare_puncte(c, pq) < 0)
            dr = mij - 1;
        else
            st = mij + 1;
    }

    pair<long long, long long> l_l1, lq;
    l_l1.first = P[st].first - P[st - 1].first;
    l_l1.second = P[st].second - P[st - 1].second;

    lq.first = a - P[st - 1].first;
    lq.second = b - P[st - 1].second;

    if (orientare_puncte(l_l1, lq) == 0)
        return 2;
    if (orientare_puncte(l_l1, lq) > 0)
        return 1;
    return 0;
}

void start(vector<pair<long long, long long>> &P, long long &n)
{
    long long min_i = 0;
    for (int i = 0; i < n; i++)
    {
        if (P[i].first < P[min_i].first || (P[i].first == P[min_i].first && P[i].second > P[min_i].second))
        {
            min_i = i;
        }
    }

    rotate(P.begin(), P.begin() + min_i, P.end());
}

void citire(long long &n, long long &m, vector<pair<long long, long long>> &P)
{
    vector<int> res;
    cin >> n;
    P.resize(n);
    long long x, y;
    for (int i = 0; i < n; i++)
        cin >> P[i].first >> P[i].second;

    start(P, n); // vom lua varful minim
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        res.push_back(inside(x, y, P, n));
    }
    for (auto &rez : res)
    {
        if (rez == 1)
            cout << "INSIDE" << endl;
        else if (rez == 2)
            cout << "BOUNDARY" << endl;
        else
            cout << "OUTSIDE" << endl;
    }
}

int main()
{

    long long n, m;
    vector<pair<long long, long long>> P;
    citire(n, m, P);

    return 0;
}