//Se dă un sir ordonat de string-uri sparse (există numeroase siruri vide). Să se scrie un
//algoritm eficient pentru căutarea unui sir dat.

#include <iostream>
#include <cstring>
using namespace std;

char word[20], str[100][20];
int n;
int binary_search(char str[100][20], int st, int dr, char *word) {
    if (st > dr) {
        return -1;
    }
    int mij = (st + dr) / 2;
    if(!strcmp(str[mij], word)) {
        if(strcmp(str[mij], str[mij-1])) {
            return mij;
        } else {
            return binary_search(str, st, mij-1, word);
        }
    } else {
        if(strcmp(str[mij], word) > 0) {
            return binary_search(str, st, mij-1, word);
        }
        if(strcmp(str[mij], word) < 0) {
            return binary_search(str, mij+1, dr, word);
        }
    }
}
int main() {
    cin>>n;
    cin.get();
    for(int i=0; i<n; ++i) {
        cin.getline(str[i], 20);
        if(!strlen(str[i])) {
            strcpy(str[i], str[i-1]);
        }
    }
    cin.getline(word, 20);
    cout<<binary_search(str, 0, n-1, word)<<endl;
    return 0;
}
