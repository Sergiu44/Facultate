#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node *right;
}*root;

void insert(int ,Node*&);
void RSD(Node*&);
void deleteNode(int value, Node*& root);

int value;
int main() {

    insert(1, root);
    insert(2, root);
    insert(3, root);
    insert(4, root);
    insert(5, root);
    RSD(root);
    cout<<endl;

    cin>>value;
    deleteNode(value, root);
    RSD(root);
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

void deleteNode(int value, Node*& root) {
    Node* parent = NULL;
    Node* aux = root;

    // Searching Node in Tree by value and setting the parent Node
    while (aux != NULL && aux->value != value)
    {
        parent = aux;

        if (value < aux->value) {
            aux = aux->left;
        }
        else {
            aux = aux->right;
        }
    }
    if(aux == NULL) {
        return;
    }
    // Cazul 1: cand nu mai avem nod-uri in subordine
    if(aux->left == NULL && aux->right == NULL) {
        if(aux != root) {
            if(parent->left == aux) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        } else {
            root = NULL;
        }
        delete aux;
    }
    // Cazul 2: exista nod in stanga si in dreapta
    else if(aux->left && aux->right) {
        Node* succ = aux->right;
        while (succ->left != NULL) {
            succ = succ->left;
        }
        int val = succ->value;
        deleteNode(succ->value, root);
        aux->value = val;
    }
    // Cazul 3: exista un nod in stnaga sau in dreapta
    else {
        Node* sub = aux->left ? aux->left : aux->right;
        if(aux != root) {
            if(aux == parent->left) {
                parent->left = sub;
            } else {
                parent->right = sub;
            }
        } else {
            root = sub;
        }
        delete aux;
    }
}
void RSD(Node*& root) {
    if (root == NULL)
        return;
    cout << root->value << " ";
    RSD(root->left);
    RSD(root->right);
}