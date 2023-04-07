#include <iostream>
#include <utility>
#include <vector>

using namespace std;

long checkDet(pair<long, long> x, pair<long, long> y, pair<long, long> z)
{
    return y.first * z.second + x.first * y.second + z.first * x.second - x.second * y.first - z.first * y.second - x.first * z.second;
}
int main()
{
    long n;
    vector<string> results;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        pair<long, long> x, y, z;
        cin >> x.first >> x.second >> y.first >> y.second >> z.first >> z.second;

        if (checkDet(x, y, z) == 0)
        {
            results.emplace_back("TOUCH");
        }
        else if (checkDet(x, y, z) < 0)
        {
            results.emplace_back("RIGHT");
        }
        else
        {
            results.emplace_back("LEFT");
        }
    }

    for (auto &res : results)
    {
        cout << res << endl;
    }
    return 0;
}