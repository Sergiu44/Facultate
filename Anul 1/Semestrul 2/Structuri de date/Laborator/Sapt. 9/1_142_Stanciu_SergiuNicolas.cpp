#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node *right;
}*root;

void insert(int ,Node*&);
void RSD(Node*&);
void SRD(Node*&);
void SDR(Node*&);
int main() {

    insert(1, root);
    insert(2, root);
    insert(3, root);
    insert(4, root);
    insert(5, root);

    cout<<"Pre-ordine: ";
    RSD(root);
    cout<<endl;
    cout<<"In-ordine: ";
    SRD(root);
    cout<<endl;
    cout<<"Post-ordine: ";
    SDR(root);
    cout<<endl;

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
void SRD(Node*& root) {
    if (root == NULL)
        return;
    SRD(root->left);
    cout << root->value << " ";
    SRD(root->right);
}
void SDR(Node*& root) {
    if (root == NULL)
        return;
    SDR(root->left);
    SRD(root->right);
    cout << root->value << " ";
}