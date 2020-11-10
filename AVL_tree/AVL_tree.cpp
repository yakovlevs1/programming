#include <iostream>
#include <vector>
#include <queue>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class Tree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node* p; //parent
    };
    int depth_ = 0;
    int capacity_ = 0;
public:
    Node root;
    Tree() {
        root.left = nullptr;
        root.right = nullptr;
        root.p = nullptr;
    }
    Tree(int x) {
        root.key = x;
        root.left = nullptr;
        root.right = nullptr;
        root.p = nullptr;
    }
    void insert(int u) {
        Node z;
        z.key = u; z.left = nullptr; z.right = nullptr; z.p = nullptr;
        insert_node(z);
    }
    void insert_node(Node z) {
        Node* y = nullptr;
        Node* x = &root;
        while (x != nullptr) {
            y = x;
            if (z.key < x->key)
                x = x->left;
            else x = x->right;
        }
        z.p = y;
        if (y == nullptr)
            root = z;
        else {
            if (z.key < y->key)
                y->left = &z;
            else y->right = &z;
        }
    }
    Node* search(Node* x, int k) { //поиск узла с заданным ключом, nullptr если не найден
        while (x != nullptr and k != x->key) {
            if (k < x->key)
                x = x->left;
            else x = x->right;
        }
        return x;
    }
    Node* minimum(Node* x) { //минимум дерева (x = root) или поддерева
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }
    Node* maximum(Node* x) { //максимум дерева (x = root) или поддерева
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }
    Node* successor(Node* x) { //следующий за x элемент
        if (x->right != nullptr) {
            return minimum(x->right);
        }
        Node* y = x->p;
        while (y != nullptr and x == y->right) {
            x = y;
            y = y->p;
        }
        return y;
    }
    Node* preccessor(Node* x) {
        if (x->left != nullptr) {
            return maximum(x->left);
        }
        Node* y = x->p;
        while (y != nullptr and x == y->left) {
            x = y;
            y = y->p;
        }
        return y;
    }

    void print_breadth_first_search() {
        std::queue<Node> q;
        q.push(root);
        while (!q.empty()) {
            if (q.front().left != nullptr) {
                q.push(*(q.front().left));
            }
            if (q.front().right != nullptr) {
                q.push(*(q.front().right));
            }
            cout << q.front().key << " ";
            q.pop();
        }
    }
    void inorder_tree_walk(Node* x) {
        if (x != nullptr) {
            inorder_tree_walk(x->left);
            cout << x->key << " ";
            inorder_tree_walk(x->right);
        }
    }
    void inorder_tree_walk() {
        inorder_tree_walk(&root);
    }
    int depth() {
        return depth_;
    }

};

int main() {
    int a;
    Tree t;
    int a;
    while (cin) {
        cin >> a;
        if (cin)
            t.push(a);
    }
    t.inorder_tree_walk(&t.root);
    return 0;

}