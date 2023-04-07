#include <bits/stdc++.h>
#define INF 9999999999
using namespace std;

struct Point
{
    double x, y;

    Point()
    {
        this->x = 0;
        this->y = 0;
    }

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};

namespace points
{
    enum LOCATION
    {
        INSIDE,
        OUTSIDE,
        BOUNDARY
    };

    enum INTERSECTION
    {
        NO,
        YES,
        COLLINEAR
    };
}

double determinant(Point a, Point b, Point c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

points::INTERSECTION checkIntersection(Point a, Point b, Point c, Point &d)
{
    double det1 = determinant(a, b, c);
    double det2 = determinant(a, b, d);
    if (det1 * det2 > 0)
    {
        return points::NO;
    }
    else if (det1 * det2 == 0)
    {
        if (det1 == 0)
        {
            if (c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x))
            {
                return points::COLLINEAR;
            }
            else
            {
                return points::NO;
            }
        }
        else
        {
            if (det1 < 0)
            {
                return points::NO;
            }
            else if (det1 > 0)
            {
                if (c.y > min(a.y, b.y) && c.y < max(a.y, b.y))
                {
                    return points::YES;
                }
            }
        }
    }
    else
    {
        if (c.y > min(a.y, b.y) && c.y < max(a.y, b.y))
        {
            return points::YES;
        }
        else if (c.y == min(a.y, b.y) || c.y == max(a.y, b.y))
        {
            //            d = Point(d.x, d.y+1);
            return points::YES;
        }
        else if (c.y < min(a.y, b.y) || c.y > max(a.y, b.y))
        {
            return points::NO;
        }
        return points::NO;
    }
}

points::LOCATION checkLocation(vector<Point> &polygon, Point pt, double minY, double maxY)
{
    int counter = 0;
    if (pt.y > maxY || pt.y < minY)
    {
        return points::OUTSIDE;
    }
    Point aux = {INF, pt.y};
    int i = 0;
    for (; i < polygon.size() - 1; ++i)
    {
        points::INTERSECTION res = checkIntersection(polygon[i], polygon[i + 1], pt, aux);
        switch (res)
        {
        case points::COLLINEAR:
            return points::BOUNDARY;
        case points::YES:
            ++counter;
            break;
        case points::NO:
            break;
        }
    }
    if (i < polygon.size())
    {
        points::INTERSECTION res = checkIntersection(polygon[polygon.size() - 1], polygon[0], pt, aux);
        switch (res)
        {
        case points::COLLINEAR:
            return points::BOUNDARY;
        case points::YES:
            ++counter;
            break;
        case points::NO:
            break;
        }
    }
    if (counter % 2)
    {
        return points::LOCATION::INSIDE;
    }
    return points::OUTSIDE;
}

int n, m;
int main()
{
    vector<Point> pts;
    vector<Point> extra_pts;
    vector<points::LOCATION> res;
    cin >> n;
    pts.resize(n, {});

    double minY = 0, maxY = 0;
    for (int i = 0; i < n; ++i)
    {
        cin >> pts[i].x >> pts[i].y;
        if (pts[i].y > maxY)
        {
            maxY = pts[i].y;
        }
        if (pts[i].y < minY)
        {
            minY = pts[i].y;
        }
    }

    cin >> m;
    extra_pts.resize(m, {});
    for (int i = 0; i < m; ++i)
    {
        cin >> extra_pts[i].x >> extra_pts[i].y;
        res.push_back(checkLocation(pts, extra_pts[i], minY, maxY));
    }
    for (auto &re : res)
    {
        switch (re)
        {
        case points::OUTSIDE:
            cout << "OUTSIDE\n";
            break;
        case points::INSIDE:
            cout << "INSIDE\n";
            break;
        case points::BOUNDARY:
            cout << "BOUNDARY\n";
            break;
        }
    }
    return 0;
}