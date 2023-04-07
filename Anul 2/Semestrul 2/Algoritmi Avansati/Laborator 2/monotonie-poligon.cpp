#include <bits/stdc++.h>

using namespace std;

struct Point
{
    int x, y;
};

long long n;

bool checkMonotony(vector<Point> &pts, bool xAxis)
{
    // startIndex - lowest point in the x/y axis
    // endIndex - highest point in the x/y axis
    long long startIndex = 0, endIndex = 0;
    if (xAxis)
    {
        for (long long i = 0; i < pts.size(); ++i)
        {
            if (pts[i].x < pts[startIndex].x)
            {
                startIndex = i;
            }
            if (pts[i].x > pts[endIndex].x)
            {
                endIndex = i;
            }
        }
        for (long long i = startIndex; i < ((startIndex < endIndex) ? endIndex : (endIndex + n)); ++i)
        {
            if (pts[i % n].x > pts[(i + 1) % n].x)
                return false;
        }
        for (long long i = ((startIndex < endIndex) ? (startIndex + n) : startIndex); i > endIndex; --i)
        {
            if (pts[i % n].x > pts[(i - 1) % n].x)
                return false;
        }
    }
    else
    {
        for (int i = 0; i < pts.size(); ++i)
        {
            if (pts[i].y < pts[startIndex].y)
            {
                startIndex = i;
            }
            if (pts[i].y > pts[endIndex].y)
            {
                endIndex = i;
            }
        }
        for (long long i = startIndex; i < ((startIndex < endIndex) ? endIndex : (endIndex + n)); ++i)
        {
            if (pts[i % n].y > pts[(i + 1) % n].y)
            {
                return false;
            }
        }
        for (long long i = ((startIndex < endIndex) ? (startIndex + n) : startIndex); i > endIndex; --i)
        {
            if (pts[i % n].y > pts[(i - 1) % n].y)
            {
                return false;
            }
        }
    }
    return true;
}

int main()
{
    vector<Point> points;

    cin >> n;
    points.resize(n, {});

    for (int i = 0; i < n; ++i)
    {
        cin >> points[i].x >> points[i].y;
    }

    cout << (checkMonotony(points, true) ? "YES\n" : "NO\n");
    cout << (checkMonotony(points, false) ? "YES" : "NO");

    return 0;
}