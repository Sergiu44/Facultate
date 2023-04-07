#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

long long checkDet(pair<long long, long long> x, pair<long long, long long> y, pair<long long, long long> z)
{
    return (y.first * z.second) + (x.first * y.second) + (z.first * x.second) - (x.second * y.first) - (z.first * y.second) - (x.first * z.second);
}

int main()
{
    stack<long long> pts;
    long long n;
    cin >> n;
    pair<long long, long long> aux;
    long long mini = 999999999999999999, startIndex = 0;
    vector<pair<long long, long long>> points;
    for (long long i = 0; i < n; ++i)
    {
        cin >> aux.first >> aux.second;
        if (aux.first < mini)
        {
            mini = aux.first;
            startIndex = i;
        }
        points.push_back(aux);
    }
    long long auxIdx = startIndex + n;
    pts.push(auxIdx % n);
    pts.push((--auxIdx) % n);
    pts.push((--auxIdx) % n);
    if (n > 3)
    {
        do
        {
            if (pts.size() >= 3)
            {
                long long z = pts.top();
                pts.pop();
                long long y = pts.top();
                pts.pop();
                long long x = pts.top();
                long long resDet = checkDet(points[x], points[y], points[z]);
                if (resDet >= 0)
                {
                    pts.push(z);
                }
                else
                {
                    pts.push(y);
                    pts.push(z);
                    --auxIdx;
                    pts.push(auxIdx % n);
                }
            }
            else
            {
                --auxIdx;
                pts.push(auxIdx % n);
            }
        } while (((auxIdx - 1) % n) != startIndex);

        if (pts.size() >= 3)
        {
            long long y = pts.top();
            pts.pop();
            long long x = pts.top();

            while (pts.size() >= 2 && checkDet(points[x], points[y], points[startIndex % n]) >= 0)
            {
                y = pts.top();
                pts.pop();
                x = pts.top();
            }
            pts.push(y);
        }
    }
    else
    {
        if (checkDet(points[(startIndex + 2) % n], points[(startIndex + 1) % n], points[(startIndex) % n]) >= 0)
        {
            pts.pop();
        }
    }

    cout << pts.size() << endl;
    while (!pts.empty())
    {
        cout << points[pts.top()].first << " " << points[pts.top()].second << endl;
        pts.pop();
    }
    return 0;
}