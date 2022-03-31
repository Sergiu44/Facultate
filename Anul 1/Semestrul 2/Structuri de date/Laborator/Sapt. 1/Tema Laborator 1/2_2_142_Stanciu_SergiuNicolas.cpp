//Scrieţi algoritmul pentru căutarea binară a unui element într-un şir ordonat, de n numere.

#include <iostream>

using namespace std;

int n, a[10000], x;

int binary_search(int x) {
    int left = 0, right = n-1;
    while(left<=right) {
        int mij = (left + right) / 2;
        if(a[mij] == x) {
            return true;
        } else {
            if(a[mij] < x) {
                left = mij + 1;
            } else {
                right = mij - 1;
            }
        }
    }
    return false;
}
int main()
{
    cin>>n>>x;
    for(int i=0; i<n; ++i){
        cin>>a[i];
    }
   string gasit = (binary_search(x) == true) ? "Da" : "Nu";
    cout<<gasit<<endl;
    return 0;
}