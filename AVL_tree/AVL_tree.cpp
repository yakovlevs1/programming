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
        short diff; // diff(x) = h(L) - h(R)
        bool operator==(const Node& x) {
            return (this->key == x.key);
        }
    };
    
    void inorder_tree_walk(Node* x) {
        if (x != nullptr) {
            inorder_tree_walk(x->left);
            cout << x->key << " ";
            inorder_tree_walk(x->right);
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
    bool insert_node(Node* z) {
        Node* y = nullptr;
        Node* x = root;
        while (x != nullptr) { //поиск места
            y = x;
            if (z->key < x->key)
                x = x->left;
            else if (z->key > x->key)
                x = x->right;
            else if (z->key == x->key)
                return false;
        }
        z->p = y;
        if (y == nullptr) { //дерево было пустым
            root = z;
            capacity_++;
            return true;
        }
        else {
            if (z->key < y->key)
                y->left = z;
            else y->right = z;
            balance_tree_insert(z);
            capacity_++;
            return true;
        }
    }
    void balance_tree_insert(Node* z) {
        while (z->p != nullptr) {
            if (z == z->p->left) { //если пришли слева
                z->p->diff += 1;
            }
            else { z->p->diff -= 1; }
            if (z->p->diff == 0)
                break;
            else if (z->p->diff == 1 or z->p->diff == -1) {
                z = z->p;
                continue;
            }
            else { 
                if (z->p->diff == 2 and z->diff == 1) {
                    right_rotate(z->p);
                    z->diff = 0;
                    z->right->diff = 0;
                }
                else if (z->p->diff == 2 and z->diff == 0) {
                    right_rotate(z->p);
                    z->diff = 1;
                    z->right->diff = -1;
                }
                else if (z->p->diff == 2 and z->diff == -1) {
                    if (z->right != nullptr) {
                        if (z->right->diff == 1) {
                            big_right_rotate(z->p);
                            z->p->diff = 0;
                            z->diff = 0;
                            z->p->right->diff = 0;
                        }
                    }
                    if (z->right != nullptr) {
                        if (z->right->diff == -1) {
                            big_right_rotate(z->p);
                            z->p->diff = 0;
                            z->diff = 1;
                            z->p->right->diff = 0;
                        }
                    }
                    if (z->right != nullptr) {
                        if (z->right->diff == 0) {
                            big_right_rotate(z->p);
                            z->p->diff = 0;
                            z->diff = 0;
                            z->p->right->diff = 0;
                        }
                    }
                }
                else if (z->p->diff == -2 and z->diff == -1) {
                    left_rotate(z->p);
                    z->diff = 0;
                    z->left->diff = 0;
                }
                else if (z->p->diff == -2 and z->diff == 0) {
                    left_rotate(z->p);
                    z->diff = -1;
                    z->left->diff = 1;
                }
                else if (z->p->diff == -2 and z->diff == 1) {
                    if (z->left != nullptr) {
                        if (z->left->diff == 1) {
                            big_left_rotate(z->p);
                            z->p->diff = 0;
                            z->diff = -1;
                            z->p->left->diff = 0;
                        }
                    }
                    if (z->left != nullptr) {
                        if (z->left->diff == -1) {
                            big_left_rotate(z->p);
                            z->p->diff = 0;
                            z->diff = 0;
                            z->p->left->diff = 1;
                        }
                    }
                    if (z->left != nullptr) {
                        if (z->left->diff == 0) {
                            big_left_rotate(z->p);
                            z->p->diff = 0;
                            z->diff = 0;
                            z->p->left->diff = 0;
                        }
                    }
                }
            z = z->p;
            }
            
        }
    }
    void balance_tree_erase(Node* z) {
        while (z->p != nullptr) {
            //Пересчёт
            if (z == z->p->left) { //если пришли слева
                z = z->p;
                z->diff -= 1;
            }
            else {                 //если пришли справа
                z = z->p;
                z->diff += 1;
            }
            if (z->diff == 1 or z->diff == -1)
                break;
            else if (z->diff == 0) {
                continue;
            }
            else {
                if (z->diff == 2 and z->left->diff == 1) {
                    right_rotate(z);
                    z->diff = 0;
                    z->p->diff = 0;
                }
                else if (z->diff == 2 and z->left->diff == 0) {
                    right_rotate(z);
                    z->diff = 1;
                    z->p->diff = -1;
                }
                else if (z->diff == 2 and z->left->diff == -1) {
                    if (z->left->right->diff == 1) {
                        big_right_rotate(z);
                        z->diff = -1;
                        z->p->diff = 0;
                        z->p->left->diff = 0;
                    }
                    if (z->left->right->diff == -1) {
                        big_right_rotate(z);
                        z->diff = 0;
                        z->p->diff = 0;
                        z->p->left->diff = 1;
                    }
                    if (z->left->right->diff == 0) {
                        big_right_rotate(z);
                        z->p->diff = 0;
                        z->diff = 0;
                        z->p->right->diff = 0;
                    }

                }
                else if (z->diff == -2 and z->right->diff == -1) {
                    left_rotate(z);
                    z->diff = 0;
                    z->p->diff = 0;
                }
                else if (z->diff == -2 and z->right->diff == 0) {
                    left_rotate(z);
                    z->diff = 0;
                    z->p->diff = 1;
                }
                else if (z->diff == -2 and z->right->diff == 1) {
                    if (z->right->left->diff == 1) {
                        big_left_rotate(z);
                        z->diff = 1;
                        z->p->diff = 0;
                        z->p->right->diff = 0;
                    }
                    if (z->right->left->diff == -1) {
                        big_left_rotate(z);
                        z->diff = 0;
                        z->p->diff = 0;
                        z->p->right->diff = -1;
                    }
                    if (z->right->left->diff == 0) {
                        big_left_rotate(z);
                        z->diff = 0;
                        z->p->diff = 0;
                        z->p->right->diff = 0;
                    }
                }

            }
        }
    }
    Node* search(Node* x, int k) const { //поиск узла в поддереве с корнем x с заданным ключом, nullptr если не найден
        while (x != nullptr and k != x->key) {
            if (k < x->key)
                x = x->left;
            else x = x->right;
        }
        return x;
    }
    Node* minimum(Node* x) const { //минимум дерева (x = root) или поддерева
        while (x->left != nullptr) {
            x = x->left;
        }
        return x;
    }
    Node* maximum(Node* x) const { //максимум дерева (x = root) или поддерева
        while (x->right != nullptr) {
            x = x->right;
        }
        return x;
    }
    Node* successor(Node* x) const { //следующий за x элемент
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
    Node* preccessor(Node* x) const {
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
    Node* erase(Node* r, int z) {
        if (r == nullptr)
            return r;
        if (z < r->key) {
            r->left = erase(r->left, z);
        }
        else if (z > r->key)
            r->right = erase(r->right, z);
        else if (r->left != nullptr and r->right != nullptr) {
            r->key = minimum(r->right)->key;
            r->right = erase(r->right, r->key);
        }
        else {
            balance_tree_erase(r);
            capacity_--;
            if (r->left != nullptr)
                r = r->left;
            else if (r->right != nullptr)
                r = r->right;
            else
                r = nullptr;
        }
        return r;
    }
    int depth_ = 0;
    unsigned long long int capacity_ = 0;
public:
    Node* root = nullptr;
    Tree() {}
    bool insert(int const u) {
        Node* z = new Node; 
        z->key = u; z->left = nullptr; z->right = nullptr; z->p = nullptr; z->diff = 0;
        return insert_node(z);
    }
    bool find(int const k) const {
        if (search(root, k) == nullptr) {
            return false;
        }
        else return true;
    }
    bool erase(int z) {
        if (find(z) == false)
            return false;
        else {
            erase(root, z);
            return true;
        }
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

    using size_type = unsigned long long int;
    size_type size() const {
        return capacity_;
    }
    using iterator = Node*;
    iterator front() const {
        return minimum(root);
    }
    iterator back() const {
        return maximum(root);
    }
    iterator next(iterator it) const { // получение итератора на следующий элемент 
        return successor(it);
    }
    iterator prev(iterator it) const {// получение итератора на предыдущий. элемент
        return preccessor(it);
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
    cout << t.next(t.front())->key;
    cout << endl;
    t.print_breadth_first_search();
    return 0;

}