
#ifndef FINALPROJEXAMPLES_AVLTREE_H
#define FINALPROJEXAMPLES_AVLTREE_H
#define DEBUG

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;

// AvlTree class

template <typename K, typename V>
class AvlTree
{
private:
    struct AvlNode
    {
        K element;
        V value;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const K &ele, const V &v, AvlNode *lt, AvlNode *rt, int h = 0)
                : element{ele}, value{v}, left{lt}, right{rt}, height{h} {}
    };

    AvlNode *root;

public:
    /**
     * @brief Construct a new Avl Tree object
     */
    AvlTree() : root{nullptr}
    {
    }

    /**
     * @brief Copy constructor
     */
    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Copy assignment operator
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
        return *this;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const K &x) const
    {
        return contains(x, root);
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTreeSort(ostream &out = cout) const
    {
        if (isEmpty())
            out << "Empty tree" << endl;
        else
            printTreeSort(root, out);
    }

    /**
     * Print the tree structure.
     */
    void prettyPrintTree() const
    {
        prettyPrintTree("", root, false);
    }

//    ofstream& writeOut(ofstream& ofs) const
//    {
//        writeOut(ofs, root);
//    }

    /**
     * Make the tree empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const K &x, const V &y)
    {
        insert(x, y, root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(const K &x)
    {
        remove(x, root);
    }
    AvlNode* access(const K &x){
       return access(x, root);
    }

    void convertToMap(unordered_map<string, unordered_map<int,int>>& r)
    {
        convertToMap(r, root);
    }

private:
    void convertToMap(unordered_map<string, unordered_map<int,int>>& r, AvlNode* t)
    {
        if (t == nullptr)
        {return;}
        else {
            if (t->element == "december"){
                cout << "DECEMBER FOUND" << endl;
            }
            if (t->element!=" ") {
                r[t->element] = t->value;
            }
                convertToMap(r, t->right);
                convertToMap(r, t->left);

        }
    }
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const K &x, const V &y, AvlNode *&t)
    {
        if (t == nullptr)
        {
            t = new AvlNode{x, y, nullptr, nullptr, 0};
            return; // a single node is always balanced
        }

        if (x < t->element)
            insert(x, y, t->left);
        else if (t->element < x)
            insert(x, y, t->right);
        else
        {
        } // Duplicate; do nothing

        // This will call balance on the way back up the tree. It will only balance
        // once at node the where the tree got imbalanced (called node alpha in the textbook).
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(const K &x, AvlNode *&t)
    {
        // same as in a binary search tree
        if (t== NULL) {
            return;
        }
        if(x> t->element){
           // cout << "move to tht right" << endl;
            remove(x, t->right);
        } else if(x < t->element){
           // cout << "move to tht left" << endl;
            remove(x, t->left);
        } else{
            //the t->element and x are equal
            if(t->left == NULL && t->right == NULL){
                delete t;
                t = nullptr;
            }
                //if it has a right branch
            else if(t->right != NULL){
                //if it has a left branch
                if(t->left != NULL){

                    t->right->left = t->left;
                }
                t=t->right;
                delete t->right;
                t->right = NULL;
            }
                //if it has only a left branch
            else if(t->left != NULL){
                t=t->left;
                delete t->left;
                t->left = NULL;
            }
        }
        // don't forget to balance
        balance(t);
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        if (t->left == nullptr)
            return t;

        return findMin(t->left);
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const K &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;

        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }
    /****** NONRECURSIVE VERSION*************************
        bool contains( const K & x, AvlNode *t ) const
        {
            while( t != nullptr )
                if( x < t->element )
                    t = t->left;
                else if( t->element < x )
                    t = t->right;
                else
                    return true;    // Match
            return false;   // No match
        }
    *****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;

        return new AvlNode{t->element, t->value, clone(t->left), clone(t->right), t->height};
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     * This is inorder traversal (LNR)
     */
    void printTreeSort(AvlNode *t, ostream &out) const
    {
        if (t == nullptr)
            return;

        // recursion
        printTreeSort(t->left, out);
        out << t->element << endl;
        printTreeSort(t->right, out);
    }

    AvlNode* access(const K &x, AvlNode *&t) {
        if (t == NULL) {
            throw std::invalid_argument("No results found for given terms");
        }
        if (x > t->element) {
           // cout << "move to tht right" << endl;
            return access(x, t->right);
        } else if (x < t->element) {
           // cout << "move to tht left" << endl;
            return access(x, t->left);
        } else {
            //the t->element and x are equal
            return t;
        }
    }

    // Modified from: https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c
    void prettyPrintTree(const std::string &prefix, const AvlNode *node, bool isRight) const
    {
        if (node == nullptr)
            return;

//        std::cout << prefix;
//        std::cout << (isRight ? "├──" : "└──");
        // print the value of the node
       // std::cout << node->element << std::endl;

        // enter the next tree level - left and right branch
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->right, true);
        prettyPrintTree(prefix + (isRight ? "│   " : "    "), node->left, false);
    }
//    ofstream& writeOut( ofstream& os, AvlNode *&t ) const {
//        if (t == NULL) {
//            return os;
//        }
//        os << t;
//        if (t->right != nullptr) {
//            os << writeOut(t->right);
//        } else if (t->left != nullptr) {
//            os << writeOut(t->left);
//        }
//        return os;
//    }
//    // Avl manipulations
//    friend ofstream& operator<<(ofstream& os, const AvlNode*& rhs)
//    {
//        if (rhs == NULL) {
//            return os;
//        }
//        os << rhs->element << ":";
//        for (auto &x : rhs->value) {
//            os << x.first << " " << x.second << ",";
//        }
//        return os;
//    }
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    static const int ALLOWED_IMBALANCE = 1; // 1 is the default; more will make balancing cheaper
    // but the search less efficient.

    // Assume t is balanced or within one of being balanced since we check this after each manipulation
    // t represents alpha in the textbook
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)  // unbalancing insertion was left
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t); // case 1 (outside)
            else
                doubleWithLeftChild(t); // case 2 (inside)
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) // unbalancing insertion was right
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t); // case 4 (outside)
            else
                doubleWithRightChild(t); // case 3 (inside)
        }

        // update height
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
#ifdef DEBUG
//        cout << "need to rotateWithLeftChild for node " << k2->element << endl;
//        cout << "Before:" << endl;
        prettyPrintTree();
#endif

        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
#ifdef DEBUG
      //  cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
//        cout << "need to rotateWithRightChild for node " << k1->element << endl;
//        cout << "Before:" << endl;
        prettyPrintTree();

#endif

        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
#ifdef DEBUG
       // cout << "After:" << endl;
        prettyPrintTree();
#endif
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
#ifdef DEBUG
//        cout << "doubleWithLeftChild" << endl;
#endif
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
#ifdef DEBUG
  //      cout << "doubleWithRightChild" << endl;
#endif
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif //FINALPROJEXAMPLES_AVLTREE_H
