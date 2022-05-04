#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node *right;
}*root;

void insert(int ,Node*&);
void RSD(Node*&);
void traversalKeys(int, int, Node*&);

int key1, key2;
int main() {

    insert(1, root);
    insert(10, root);
    insert(5, root);
    insert(22, root);
    insert(0, root);

    cout<<"Prima valoare: "; cin>>key1;
    cout<<"A doua valoare: "; cin>>key2;

    traversalKeys(key1, key2, root);
    return 0;
}
void insert(int value, Node *&root) {
    if (root == NULL) {
        root = new Node;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    } else {
        if (value < root->value)
            insert(value, root->left);
        else
            insert(value, root->right);
    }
}
void RSD(Node*& root) {
    if (root == NULL)
        return;
    cout << root->value << " ";
    RSD(root->left);
    RSD(root->right);
}
void traversalKeys(int key1, int key2, Node*& root) {
    // Verificam daca exista root
    if(root == NULL) {
        return;
    }
    if(key1 < root->value)
        traversalKeys(key1, key2, root->left);

    if (key1 <= root->value && key2 >= root->value )
        cout<<root->value<<" ";
    traversalKeys(key1, key2, root->right);
}