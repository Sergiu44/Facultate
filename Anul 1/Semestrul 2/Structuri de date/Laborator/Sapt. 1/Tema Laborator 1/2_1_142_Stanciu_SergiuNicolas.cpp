//Scrieţi algoritmul pentru căutarea secvenţială a unui element într-un şir de n numere.

#include <iostream>

using namespace std;

int n, a[10000], x;

int main()
{
    cin>>n>>x;
    bool gasit = false;
    for(int i=0; i < n; ++i) {
        cin >> a[i];
        if(x == a[i]) {
            gasit = true;
        }
    }
    if(gasit) cout<<"Da"<<endl; else cout<<"Nu"<<endl;
    return 0;
}