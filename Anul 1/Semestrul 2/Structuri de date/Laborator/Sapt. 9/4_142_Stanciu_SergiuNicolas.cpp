#include <iostream>

using namespace std;

struct Node {
    string word;
    Node* left;
    Node *right;
}*root;

void insert(string ,Node*&);
void descPrint(Node*&);
string newWord;
int n;
int main() {
    cout<<"Numarul de cuvinte care vor fi citite: ";
    cin>>n;
    for(int i=0; i<n; ++i) {
        cin>>newWord;
        insert(newWord, root);
    }
    descPrint(root);

    return 0;
}

void insert(string word, Node *&root) {
    if (root == NULL) {
        root = new Node;
        root->word = word;
        root->left = NULL;
        root->right = NULL;
    } else {
        if (word < root->word)
            insert(word, root->left);
        else
            insert(word, root->right);
    }
}
void descPrint(Node*& root){
    if(root != NULL){
        descPrint(root->right);
        cout<<root->word<<endl;
        descPrint(root->left);
    }
}