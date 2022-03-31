//Să se scrie un program pentru ordonarea descrescătoare a unui şir de
//n numere folosind sortarea prin selecţie (Selection Sort).

#include <iostream>

using namespace std;

int n, a[10000];
int main()
{
    cin>>n;
    for(int i=0; i<n; ++i){
        cin>>a[i];
    }

   for(int i=0; i<n-1; ++i) {
       int max_indice = i;
       for(int j=i+1; j<n; ++j) {
           if(a[j] > a[min_id]) {
               max_indice = j;
           }
       }
       swap(a[i], a[max_indice]);
   }

    for(int i=0; i<n; ++i) {
        cout<<a[i]<<" ";
    }

    return 0;
}