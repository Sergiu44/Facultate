//Scrieti o metodă de sortare a unui s, ir de string-uri astfel încât toate anagramele să fie una
//lângă cealaltă.

#include <iostream>
#include <cstring>
using namespace std;
int n;
char str[100000][100];

bool anagrame(char *a, char *b) {
    if(strlen(a) != strlen(b)) {
        return false;
    } else {
        char aux[100];
        strcpy(aux, b);
        for(int i=0; i<strlen(a); ++i) {
            if(!strchr(b, a[i])) {
                return false;
            } else {
                strcpy(strchr(b,a[i]), strchr(b,a[i])+1);
            }
        }
        strcpy(b, aux);
        return true;
    }
}

int main() {
    cin>>n;
    cin.get();
    for(int i=0; i<n; ++i) {
        cin.getline(str[i],100);
    }
    for(int i = 0; i<n-1; ++i) {
        for(int j=i+1; j<n; ++j) {
            if(anagrame(str[i], str[j])) {
                swap(str[++i], str[j]);
            }
        }
    }
    for(int i=0; i<n; ++i) {
        cout<<str[i]<<endl;
    }

    return 0;
}