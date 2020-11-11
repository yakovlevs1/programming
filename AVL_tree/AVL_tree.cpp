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
        unsigned short diff; // diff(x) = h(L) - h(R)
        bool operator==(const Node& x) {
            return (this->key == x.key);
        }
    };
    void insert_node(Node* z) {
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr) {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else x = x->right;
        }
        z->p = y;
        if (y == nullptr) //дерево было пустым
            root = z;
        else {
            if (z->key < y->key)
                y->left = z;
            else y->right = z;
        }
    }
    void inorder_tree_walk(Node* x) {
        if (x != nullptr) {
            inorder_tree_walk(x->left);
            cout << x->key << " ";
            inorder_tree_walk(x->right);
        }
    }
    void transplant(Node* u, Node* v) {
        if (u->p == nullptr) {
            root = v;
        }
        else if (u == u->p->left) {
            u->p->left = v;
        }
        else u->p->right = v;
        if (v != nullptr) {
            v->p = u->p;
        }
    }
    void left_rotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->p = x;
        }
        y->p = x->p;
        if (x->p == nullptr) {
            root = y;
        }
        else if (x == x->p->left) {
            x->p->left = y;
        }
        else { x->p->right = y; }
        y->left = x;
        x->p = y;
    }
    void right_rotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->p = x;
        }
        y->p = x->p;
        if (x->p == nullptr) {
            root = y;
        }
        else if (x == x->p->left) {
            x->p->left = y;
        }
        else { x->p->right = y; }
        y->right = x;
        x->p = y;
    }
    void big_left_rotate(Node* x) {
        right_rotate(x->right);
        left_rotate(x);
    }
    void big_right_rotate(Node* x) {
        left_rotate(x->left);
        right_rotate(x);
    }
    int depth_ = 0;
    int capacity_ = 0;
public:
    Node* root = nullptr;
    Tree() {}
    void insert(int u) {
        Node* z = new Node; 
        z->key = u; z->left = nullptr; z->right = nullptr; z->p = nullptr; z->diff = 0;
        insert_node(z);
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
    void node_delete(Node* z) { //Cormen
        if (z->left == nullptr)
            transplant(z, z->right);
        else if (z->right == nullptr)
            transplant(z, z->left);
        else {
            Node* y = minimum(z->right);
            if (y->p != z) {
                transplant(y, y->right);
                y->right = z->right;
                y->right->p = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->p = y;
        }
    }
    void erase(Node* v) {                // neerc.ifmo.ru
        Node* par = v->p;
        if (v->left == nullptr and v->right == nullptr) {         // первый случай: удаляемый элемент не имеет потомков
            if (par->left == v)
                par->left = nullptr;
            if (par->right == v)
                par->right = nullptr;
        }
        else if (v->left == nullptr or v->right == nullptr) {     // второй случай: удаляемый элемент имеет одного потомка
            if (v->left == nullptr) {
                if (par->left == v) {
                    par->left = v->right;
                }
                else {
                    par->right = v->right;
                }
                v->right->p = par;
            }
            else {
                if (par->left == v) {
                    par->left = v->left;
                }
                else {
                    par->right = v->left;
                }
                v->left->p = par;
            }
        }
        else {                                         // третий случай: удаляемый элемент имеет двух потомков
            Node* next = successor(v);
            v->key = next->key;
            if (next->p->left == next) {
                next->p->left = next->right;
                if (next->right != nullptr) {
                    next->right->p = next->p;
                }
            }
            else {
                next->p->right = next->left;
                if (next->left != nullptr)
                    next->right->p = next->p;
            }

        }
    }
    Node* deletee(Node* r, int z) {
        if (r == nullptr)
            return r;
        if (z < r->key) {
            r->left = deletee(r->left, z);
        }
        else if (z > r->key)
            r->right = deletee(r->right, z);
        else if (r->left != nullptr and r->right != nullptr) {
            r->key = minimum(r->right)->key;
            r->right = deletee(r->right, r->key);
        }
        else {
            if (r->left != nullptr)
                r = r->left;
            else if (r->right != nullptr)
                r = r->right;
            else
                r = nullptr;
        }
        return r;
    }
    void print_breadth_first_search() {
        std::queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            if (q.front()->left != nullptr) {
                q.push(q.front()->left);
            }
            if (q.front()->right != nullptr) {
                q.push(q.front()->right);
            }
            cout << q.front()->key << " ";
            q.pop();
        }
    }
    void inorder_tree_walk() {
        inorder_tree_walk(root);
    }
    int depth() {
        return depth_;
    }
};

int main() {
    int a;
    Tree t;
    while (cin) {
        cin >> a;
        if (cin)
            t.insert(a);
    }
   
    t.inorder_tree_walk();
    t.deletee(t.root, 81);
    cout << endl;
    t.print_breadth_first_search();
    return 0;

}