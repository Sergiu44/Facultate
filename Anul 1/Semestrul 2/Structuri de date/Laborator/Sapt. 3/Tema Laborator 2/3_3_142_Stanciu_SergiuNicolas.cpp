//Să se optimizeze procedura de sortare rapidă, folosind următoarea tehnică: subşirurile de
//dimensiune <= 11 elemente se sortează cu inserţia directă.

#include <iostream>
using namespace std;

int partition(int*, int, int);
void quickSort(int*, int, int);
void directInsertion(int*, int, int);
void print(int*, int);

int ord, n;
int main() {
    cout<<"Numarul de numere: ";
    cin>>n;
    cout<<"Pentru ordine crescatoare, apasati 1;";
    cout<<"\nPentru ordine descrescatoare, apasati -1;\n";
    cin>>ord;
    cout<<"\nInserati vectorul de "<<n<<" elemente:\n";
    int* v = new int[n-1];
    for(int i=0; i<n; ++i) {
        cin>>v[i];
    }
    quickSort(v,0,n-1);
    cout<<"Vectorul ordonat "<<(ord == -1 ? "descrescator este:\n" : "crescator este:\n");
    print(v,n);
    return 0;
}

void print(int* v, int size) {
    for(int i = 0; i < size; ++i) {
        cout<<v[i]<<" ";
    }
    cout<<endl;
    delete[] v;
}

int partition(int* v, int i, int j) {
    int element = v[j];
    int indice = i - 1;

    for(int k = i; k <= j - 1; ++k) {
        if((v[k] <= element && ord == 1) || (v[k] >= element && ord == -1)) {
            ++indice;
            swap(v[indice],v[k]);
        }
    }
    swap(v[indice+1], v[j]);
    return (indice+1);
}

void quickSort(int* v, int i, int j) {
    if(i < j && j-i+1 > 11) {
        int pivot = partition(v,i,j);
        quickSort(v,i,pivot-1);
        quickSort(v,pivot+1, j);
    }
    else if(i < j && j-i+1 <=11) {
        directInsertion(v,i,j);
    }
}


void directInsertion(int* v, int i, int j) {
    for(int k=i+1; k<=j; ++k) {
        int aux = k;
        while(v[k] < v[k-1] && k>0 && ord==1) {
            swap(v[k],v[k-1]);
            --k;
        }
        while(v[k] > v[k-1] && k>0 && ord==-1) {
            swap(v[k],v[k-1]);
            --k;
        }
        k = aux;
    }
}