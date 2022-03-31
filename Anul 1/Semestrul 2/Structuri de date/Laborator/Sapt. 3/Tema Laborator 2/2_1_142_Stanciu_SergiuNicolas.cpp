//Să se scrie algoritmul pentru sortarea unui şir de numere folosind metoda Heapsort. Structura
//de Heap va fi implementată ca un arbore binar într-una din cele două forme care urmează :
//  a) max - Heap – arbore binar în care fiecare nod are cheia mai mare decât oricare dintre
//     fiii săi

#include <iostream>
using namespace std;

void heapify(int[], int, int);
void heapSort(int[], int);
void print(int[], int);

int v[100], n;

int main() {
    cin>>n;
    for(int i=0; i<n; ++i) {
        cin>>v[i];
    }
    heapSort(v,n);
    print(v,n);
    return 0;
}

void print(int v[100], int n)
{
    for (int i = 0; i < n; ++i)
        cout<<v[i]<<" ";
    cout<<endl;
}

void heapify(int v[100], int n, int indice) {
    int max = indice;
    int left = 2*indice + 1;
    int right = 2*indice + 2;

    // Verificam daca elementul din stanga e mai mare
    if(left < n && v[left] > v[max])
        max = left;

    // Verificam daca elementul din dreapta e mai mare
    if(right < n && v[right] > v[max])
        max = right;

    // Verificam daca elementul maxim nu e parinte
    if(max != indice) {
        swap(v[indice], v[max]);

        // Facem heapify pe cealalta parte de subarbore
        heapify(v,n,max);
    }
}

void heapSort(int v[100], int n) {
    for(int i=n/2 -1; i>=0; --i)
        heapify(v,n,i);

    for(int i=n-1; i>0; --i) {
        swap(v[0], v[i]);
        heapify(v,i,0);
    }
}
