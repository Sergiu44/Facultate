#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node *right;
}*root;

void insert(int ,Node*&);
Node* LCA(Node*&, Node*, Node*);
int main() {

    insert(1, root);
    insert(10, root);
    insert(5, root);
    insert(22, root);
    insert(0, root);

    cout<<LCA(root, root->right->left, root->right->right)->value<<endl;

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
Node* LCA(Node*& root, Node* p, Node* q) {
    if(!root || root == p || root == q) {
        return root;
    }
    Node* x = LCA(root->left, p, q);
    Node* y = LCA(root->right, p, q);

    if((x && y) || root == p || root == q) {
        return root;
    } else {
        return x ? x : y ? y : NULL;
    }
}