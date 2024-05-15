#ifndef __CONCAT_STRING_TREE_H__
#define __CONCAT_STRING_TREE_H__

#include "main.h"

static int id1;
class AVLTreeNode {
public:
    int id;

    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode() {
        this->id = 0;
        this->right = NULL;
        this->left = NULL;

    }
    AVLTreeNode(int id) {
        if (id1 >= 10000000) {
            throw overflow_error("Id is overflow!");
        }
        id1++;
        this->id = max(id, id1);
        this->left = NULL;
        this->right = NULL;
    }
    ~AVLTreeNode() {
    };
};
class Parentstree {

public:
    AVLTreeNode* roott;
    int len;
public:
    Parentstree() {
        this->roott = new AVLTreeNode();
        this->len = 1;
    };
    ~Parentstree() {
        delete this->roott;
        this->roott = nullptr;
    };
    int height(AVLTreeNode* r) {
        if (r == NULL)
            return -1;
        else {
            /* compute the height of each subtree */
            int lheight = height(r->left);
            int rheight = height(r->right);

            /* use the larger one */
            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }

    // Get Balance factor of node N  
    int getBalanceFactor(AVLTreeNode* n) {
        if (n == NULL)
            return -1;
        return height(n->left) - height(n->right);
    }

    AVLTreeNode* rightRotate(AVLTreeNode* y) {
        AVLTreeNode* x = y->left;
        AVLTreeNode* T2 = x->right;

        // Perform rotation  
        x->right = y;
        y->left = T2;

        return x;
    }

    AVLTreeNode* leftRotate(AVLTreeNode* x) {
        AVLTreeNode* y = x->right;
        AVLTreeNode* T2 = y->left;

        // Perform rotation  
        y->left = x;
        x->right = T2;

        return y;
    }
    bool findid(AVLTreeNode* root, int id) {
        if (root == NULL) {
            return 0;
        }
        else {
            AVLTreeNode* temp = root;
            while (temp != NULL) {
                if (id == temp->id) {
                    break;
                }
                else if (id < temp->id) {
                    temp = temp->left;
                }
                else {
                    temp = temp->right;
                }
            }
            if (temp != NULL) return 1;
            else return 0;
        }
    }

    AVLTreeNode* insert(AVLTreeNode* r, int val) {
        if (r == NULL) {
            AVLTreeNode* new_node = new AVLTreeNode();
            new_node->id = val;
            r = new_node;
            r->left = r->right = nullptr;
            this->len++;
            return r;
        }

        if (val < r->id) {
            r->left = insert(r->left, val);
        }
        else if (val > r->id) {
            r->right = insert(r->right, val);
        }
        else {
            return r;
        }

        int bf = getBalanceFactor(r);
        // Left Left Case  
        if (bf > 1 && val < r->left->id)
            return rightRotate(r);

        // Right Right Case  
        if (bf < -1 && val > r->right->id)
            return leftRotate(r);

        // Left Right Case  
        if (bf > 1 && val > r->left->id) {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }

        // Right Left Case  
        if (bf < -1 && val < r->right->id) {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
        /* return the (unchanged) node pointer */
        return r;

    }
    AVLTreeNode* maxValueNode(AVLTreeNode* r)
    {
        AVLTreeNode* current = r;
        while (current->right != NULL)
            current = current->right;

        return current;
    }
    AVLTreeNode* deleteNode(AVLTreeNode* r, int key) {
        if (r == NULL)
            return r;
        if (key > r->id)
            r->right = deleteNode(r->right, key);
        else if (key < r->id)
            r->left = deleteNode(r->left, key);
        else {
            if (r->left == NULL || r->right == NULL) {
                AVLTreeNode* temp;
                if (r->right != NULL)
                    temp = r->right;
                else {
                    temp = r->left;
                }
                if (temp == NULL) {
                    temp = r;
                    r = NULL;
                }
                else
                    *r = *temp;
                free(temp);
            }
            else {
                AVLTreeNode* temp = maxValueNode(r->left);
                r->id = temp->id;
                r->left = deleteNode(r->left, temp->id);
            }
        }
        if (r == NULL) return r;
        int bf = getBalanceFactor(r);
        // Left Left Imbalance/Case or Right rotation 
        if (bf == 2 && getBalanceFactor(r->left) >= 0)
            return rightRotate(r);
        // Left Right Imbalance/Case or LR rotation 
        else if (bf == 2 && getBalanceFactor(r->left) == -1) {
            r->left = leftRotate(r->left);
            return rightRotate(r);
        }
        // Right Right Imbalance/Case or Left rotation	
        else if (bf == -2 && getBalanceFactor(r->right) <= -0)
            return leftRotate(r);
        // Right Left Imbalance/Case or RL rotation 
        else if (bf == -2 && getBalanceFactor(r->right) == 1) {
            r->right = rightRotate(r->right);
            return leftRotate(r);
        }
        this->len--;
        return r;
    }
public:
    int size() const {
        return len;
    };
    string toStringPreOrder(AVLTreeNode* r) const {
        stringstream ss;
        if (r != nullptr) {
            ss << "(id=";
            ss << r->id << ");";
            ss << toStringPreOrder(r->left);
            ss << toStringPreOrder(r->right);
        }
        return ss.str();
    }
    string toStringPreOrder() const {
        string str = "ParentsTree[" + toStringPreOrder(this->roott);
        str.pop_back();
        str += "]";
        return str;
    };
};

class ConcatStringTree {
public:
    class Treenode {
    public:
        string data;
        int id;
        int leftlength;
        int length;
        Treenode* left;
        Treenode* right;
        Parentstree* Ptree;
    public:
        Treenode() {
            Ptree = new Parentstree();
            this->id = this->Ptree->roott->id;
            this->data = "";
            this->left = NULL;
            this->right = NULL;
            this->leftlength = 0;
            this->length = 0;
        }
        Treenode(string data) {
            Ptree = new Parentstree();
            this->id = this->Ptree->roott->id;
            this->data = data;
            this->left = NULL;
            this->right = NULL;
            this->leftlength = 0;
            this->length = data.length();
        }
        Treenode(const Treenode& a) {
            data = a.data;
            left = a.left;
            right = a.right;
            leftlength = a.leftlength;
            length = a.length;
            id = a.Ptree->roott->id;
        }
        ~Treenode() {
            delete this->Ptree;
            this->Ptree = nullptr;
        };
    };
public:
    Treenode* root;
public:
    ConcatStringTree() {
        this->root = new Treenode();
        if (id1 >= 10000000) {
            throw overflow_error("Id is overflow!");
        }
        id1++;
        this->root->id = this->root->Ptree->roott->id;
        this->root->Ptree->roott->id = id1;
    };
    int empty(Treenode* root) {
        if (root == NULL)
            return -1;
        else {
            /* compute the height of each subtree */
            int lheight = empty(root->left);
            int rheight = empty(root->right);

            /* use the larger one */
            if (lheight > rheight)
                return (lheight + 1);
            else return (rheight + 1);
        }
    }
    void removeTreeNode(Treenode* root) {
        if (!root) return;
        else if (empty(root)) {
            if (root->left) {
                root->left->Ptree->deleteNode(root->Ptree->roott, root->id);
                removeTreeNode(root->left);
            }
            if (root->right)
            {
                root->right->Ptree->deleteNode(root->Ptree->roott, root->id);
                removeTreeNode(root->right);
            }
            delete root;
        }
    }
    void destroythisid(Treenode* r) {
        if (r->left) {
            if (r->left->Ptree->roott != NULL)
                r->left->Ptree->roott = r->left->Ptree->deleteNode(r->left->Ptree->roott, r->id);
        }
        if (r->right) {
            if (r->right->Ptree->roott != NULL)
                r->right->Ptree->roott = r->right->Ptree->deleteNode(r->right->Ptree->roott, r->id);
        }

        if (r->left != NULL && (r->left->Ptree->roott == NULL || r->left->Ptree->roott->id > r->id)) {
            destroythisid(r->left);
            xoasachcayavl(r->left->Ptree->roott);
            delete r->left->Ptree->roott;
            r->left->Ptree->roott = nullptr;
            delete r->left;
            r->left = nullptr;
        }
        if (r->right != NULL && (r->right->Ptree->roott == NULL || r->right->Ptree->roott->id > r->id)) {
            destroythisid(r->right);
            xoasachcayavl(r->right->Ptree->roott);
            delete r->right->Ptree->roott;
            r->right->Ptree->roott = nullptr;
            delete r->right;
            r->right = nullptr;
        }
        return;
    }
    void xoasachcayavl(AVLTreeNode* r) {

        if (r != NULL)
        {
            xoasachcayavl(r->left);
            xoasachcayavl(r->right);
            delete(r);
            if (r->left != NULL)
                r->left = NULL;
            if (r->right != NULL)
                r->right = NULL;
            r = NULL;
        }
    }
    ConcatStringTree(const char* s) {
        this->root = new Treenode(s);
        if (id1 >= 10000000) {
            throw overflow_error("Id is overflow!");
        }
        id1++;
        this->root->Ptree->roott->id = id1;
        this->root->id = id1;
        string str = s;
        this->root->length = str.size();
    };
    ConcatStringTree(const ConcatStringTree& a) {
        root = a.root;
        root->Ptree->roott->id = a.root->Ptree->roott->id;
        root->length = a.root->length;
        root->leftlength = a.root->leftlength;
        root->data = a.root->data;
    }
    ConcatStringTree(Treenode* node, Treenode* others) {
        this->root = new Treenode();
        if (id1 >= 10000000) {
            throw overflow_error("Id is overflow!");
        }
        id1++;
        this->root->Ptree->roott->id = id1;
        this->root->id = this->root->Ptree->roott->id;
        this->root->left = node;
        this->root->right = others;
        this->root->leftlength = node->length;
        this->root->length = node->length + others->length;
        node->Ptree->roott = node->Ptree->insert(node->Ptree->roott, this->root->Ptree->roott->id);
        others->Ptree->roott = others->Ptree->insert(others->Ptree->roott, this->root->Ptree->roott->id);
    }
    ~ConcatStringTree() {
        this->root->Ptree->roott = this->root->Ptree->deleteNode(this->root->Ptree->roott, this->root->id);
        if (this->root->Ptree->roott == NULL) {
            destroythisid(this->root);
            delete this->root;
            this->root = nullptr;
        }
    };
    int length() const {
        return this->root->length;
    };
    char get(int index) {
        int len = root->length;
        if (index < 0 || index >= len) {
            throw out_of_range("Index of string is invalid!");
        }
        else {
            Treenode* p = root;
            string s1;
            while (p != NULL) {
                if (index >= p->leftlength && p->right != NULL) {

                    index -= p->leftlength;
                    p = p->right;

                }
                else if (index < p->leftlength && p->left != NULL) {
                    p = p->left;
                }
                if (p->leftlength == 0) {
                    s1 = p->data;
                    break;
                }
            }

            return s1[index];
        }
    };
    int indexOf(char c) {
        Treenode* p = root;
        string s1 = toString(p);
        return s1.find(c);
    };
    string toStringPreOrder(Treenode* r) const {
        stringstream ss;
        if (r != nullptr) {
            ss << "(" << "LL=" << r->leftlength << ",L=" << r->length << ",";
            if (r->data.size() == 0)
                ss << "<NULL>";
            else {
                char s1 = '"';
                ss << s1 << r->data << s1;

            }
            ss << ");";
            ss << toStringPreOrder(r->left);
            ss << toStringPreOrder(r->right);
        }
        return ss.str();
    };
    string toStringPreOrder() const {
        string str = "ConcatStringTree[" + toStringPreOrder(root);
        str.pop_back();
        str += "]";
        return str;
    };
    string toString(Treenode* r) const {
        stringstream ss;
        if (r != NULL) {
            ss << toString(r->left);
            ss << r->data;
            ss << toString(r->right);
        }
        return ss.str();
    }
    string toString() const {
        string str = "ConcatStringTree[\"" + toString(root);
        str += "\"]";
        return str;
    };
    Treenode* Copy(Treenode* r) {
        if (r == NULL) return NULL;
        Treenode* rcpy = new Treenode(r->data);
        rcpy->leftlength = r->leftlength;
        rcpy->left = Copy(r->left);
        rcpy->right = Copy(r->right);
    }
    ConcatStringTree concat(const ConcatStringTree& otherS) const {
        return ConcatStringTree(root, otherS.root);
    };

    Treenode* subString(int from, int to, Treenode* r) const {
        Treenode* cpy = new Treenode();
        if (r == NULL) return NULL;
        else if (r->leftlength == 0 && r->right==NULL) {
            string s1 = r->data;
            cpy->data = s1.substr(from, to - from);
            cpy->length = to - from;
            cpy->leftlength = 0;
            cpy->id = r->Ptree->roott->id;
            return cpy;
        }
        if (from >= r->leftlength) {
            cpy->id = r->Ptree->roott->id;
            cpy->leftlength = 0;
            cpy->length = to - from;
            cpy->right = subString(from - r->leftlength, to - r->leftlength, r->right);

        }
        else if (to <= r->leftlength) {
            cpy->id = r->Ptree->roott->id;
            cpy->leftlength = to - from;
            cpy->length = to - from;
            cpy->left = subString(from, to, r->left);

        }
        else {
            cpy->data = "";
            cpy->id = r->Ptree->roott->id;
            cpy->leftlength = r->leftlength - from;
            cpy->length = to - from;
            cpy->left = subString(from, r->leftlength, r->left);
            cpy->right = subString(0, to - r->leftlength, r->right);
        }
        return cpy;

    };

    ConcatStringTree subString(int from, int to) const {
        int len = root->length;
        if (from >= to) {
            throw logic_error("Invalid range");
        }
        if (from<0 || to>len || to < 0 || from >= len) {
            throw out_of_range("Index of string is invalid");
        }
        ConcatStringTree* list1 = new ConcatStringTree();
        list1->root = subString(from, to, root);
        return *list1;
    };

    Treenode* reverse1(Treenode* r) const {
        Treenode* rve = new Treenode();
        if (r == NULL) return NULL;
        else if (!r->leftlength && r->right==NULL) {
            string str = r->data;
            int i = 0;
            int n = r->length - 1;
            while (i <= n) {
                swap(str[i], str[n]);
                n = n - 1;
                i = i + 1;
            }
            rve->data = str;
            rve->id = r->Ptree->roott->id;
            rve->leftlength = 0;
            rve->length = r->length;
        }
        else {

            rve->data = "";
            rve->id = r->Ptree->roott->id;
            rve->length = r->length;
            rve->leftlength = r->length - r->leftlength;
            rve->left = reverse1(r->right);
            rve->right = reverse1(r->left);

        }
        return rve;
    }

    ConcatStringTree reverse() const {
        ConcatStringTree* list2 = new ConcatStringTree();
        list2->root = reverse1(root);
        return *list2;
    };

    int countnode(AVLTreeNode* r) const {
        if (r == NULL) return 0;
        return 1 + countnode(r->left) + countnode(r->right);
    }

    int getParTreeSize(const string& query, Treenode* r) const {
        string s2 = query;
        int n = query.size();
        int cnt = 0;
        Treenode* p = r;
        for (int i = 0; i < n; i++) {
            try {
                if (p != NULL) {
                    try {
                        if (query[i] == 'l') {
                            p = p->left;
                        }
                        else if (query[i] == 'r') {
                            p = p->right;
                        }
                        else {
                            throw runtime_error("Invalid character of query");
                        }
                    }
                    catch (runtime_error& ofr) {
                        cout << "Exception runtime_error: " << ofr.what() << endl;
                    }
                }
                else throw runtime_error("Invalid query: reaching NULL");
            }
            catch (runtime_error& ofr) {
                cout << "Exception runtimr_error: " << ofr.what() << endl;
            }
        }
        if (p != NULL) {
            cnt = p->Ptree->len;
        }
        else throw runtime_error("Invalid query: reaching NULL");

        return cnt;
    };

    int getParTreeSize(const string& query) const {
        return getParTreeSize(query, root);
    };
    string PreorderAVL(AVLTreeNode* r) const {
        stringstream ss;
        if (r != NULL)
        {
            ss << "(id=";
            ss << r->id << ");";
            ss << PreorderAVL(r->left);
            ss << PreorderAVL(r->right);
        }
        return ss.str();
    }
    string getParTreeStringPreOrder(const string& query, Treenode* r) const {
        int n = query.size();
        string s;
        for (int i = 0; i < n; i++) {
            if (r != NULL) {
                if (query[i] == 'l') {
                    r = r->left;
                }
                else if (query[i] == 'r') {
                    r = r->right;
                }
                else throw runtime_error("Invalid character of query");
            }
            else throw runtime_error("Invalid query: reaching NULL");
        }
        if (r == NULL) throw runtime_error("Invalid query: reaching NULL");
        else {
            s = "ParentsTree[" + PreorderAVL(r->Ptree->roott);
            s.pop_back();
            s += "]";
        }

        return s;
    };
    string getParTreeStringPreOrder(const string& query) const {
        return getParTreeStringPreOrder(query, root);
    };
};

//class ReducedConcatStringTree; // forward declaration


//class ReducedConcatStringTree; // forward declaration
//class LitStringHash; // forward declaration

class HashConfig {
private:
    int p;
    double c1, c2;
    double lambda;
    double alpha;
    int initSize;

    friend class ReducedConcatStringTree;
    friend class LitStringHash;
public:
    HashConfig() {
        this->p = 0;
        this->c1 = this->c2 = 0;
        this->lambda = 0;
        this->alpha = 0;
        this->initSize = 0;
    }
    HashConfig(int p, double c1, double c2, double lamda, int alpha, int initSize) {
        this->p = p;
        this->c1 = c1;
        this->c2 = c2;
        this->lambda = lamda;
        this->alpha = alpha;
        this->initSize = initSize;
    }
};

class LitStringHash {
public:
    LitStringHash(const HashConfig& hashConfig) {}
    int getLastInsertedIndex() const { return 0; }
    string toString() const { return ""; }
};

class ReducedConcatStringTree {
public:
    ReducedConcatStringTree(const char* s, LitStringHash* litStringHash) {


    }
    LitStringHash* litStringHash{  };
    string toString() const { return ""; }
};

#endif // __CONCAT_STRING_TREE_H__