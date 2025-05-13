
/***
 * Vik Dhillon
 * vsdhillo
 * 2025 Winter CSE101 PA8
 * Dictionary.cpp
 * File to write Dictionary ADT
 ***/
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

#define BLACK -21
#define RED -14
#define UNDEF -10

Dictionary::Node::Node(keyType k, valType v)
{
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
}

Dictionary::Dictionary()
{
    nil = new Node("/", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary &D)
{
    nil = new Node("", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;

    preOrderCopy(D.root, D.nil);
}

// Destructor

Dictionary::~Dictionary()
{
    postOrderDelete(root);
    delete nil;
}

// HELPERS
void Dictionary::inOrderString(std::string &s, Node *R) const
{
    if (R != nil)
    {
        inOrderString(s, R->left);
        s += R->key + " : " + std::to_string(R->val) + "\n";
        inOrderString(s, R->right);
    }
}

void Dictionary::preOrderString(std::string &s, Node *R) const
{
    if (R != nil)
    {
        s.append(R->key);
        if (R->color == BLACK)
        {
            s += "\n";
        }
        else if (R->color == RED)
        {
            s += " (RED)\n";
        }
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R != N)
    {
        Node *T = new Node(R->key, R->val);
        T->color = R->color;
        BST_Insert(T);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node *R)
{
    if (R == nullptr)
    {
        return;
    }
    if (R != nil)
    {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

Dictionary::Node *Dictionary::search(Node *R, keyType k) const
{
    if (R == nil || R == nullptr)
    {
        return nil;
    }
    if (R->key == k)
    {
        return R;
    }
    if (k < R->key)
    {
        return search(R->left, k);
    }
    return search(R->right, k);
}

Dictionary::Node *Dictionary::findMin(Node *R)
{
    if (R == nil || R == nullptr)
    {
        return nil;
    }
    if (R->left == nil)
    {
        return R;
    }
    return findMin(R->left);
}

Dictionary::Node *Dictionary::findMax(Node *R)
{
    if (R == nil || R == nullptr)
    {
        return nil;
    }
    if (R->right == nil)
    {
        return R;
    }
    return findMax(R->right);
}

Dictionary::Node *Dictionary::findNext(Node *N)
{
    if (N == nil)
    {
        return nil;
    }

    if (N->right != nil)
    {
        return findMin(N->right);
    }

    Node *par = N->parent;
    while (par != nil && N == par->right)
    {
        N = par;
        par = par->parent;
    }
    return par;
}

Dictionary::Node *Dictionary::findPrev(Node *N)
{
    if (N == nil)
    {
        return nil;
    }

    if (N->left != nil)
    {
        return findMax(N->left);
    }

    Node *par = N->parent;
    while (par != nil && N == par->left)
    {
        N = par;
        par = par->parent;
    }
    return par;
}

void Dictionary::Transplant(Node *u, Node *v)
{
    if (u->parent == nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    if (v != nil)
    {
        v->parent = u->parent;
    }
}

void Dictionary::BST_Insert(Node *N) {
    Node *y = nil;
    Node *x = root;

    while (x != nil)
    {
        y = x;
        if (N->key < x->key)
        {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    N->parent = y;
    if (y == nil)
    {
        root = N;
    }
    else if (N->key < y->key)
    {
        y->left = N;
    }
    else
    {
        y->right = N;
    }

    N->left = nil;
    N->right = nil;
    //z->color = RED;
    num_pairs++;

    //RB_InsertFixUp(z);
}

// RBT HELPERS

void Dictionary::LeftRotate(Node *N)
{
    Node *Y = N->right;

    N->right = Y->left;
    if (Y->left != nil) {
        Y->left->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == nil)
    {
        root = Y;
    }
    else if (N == N->parent->left)
    {
        N->parent->left = Y;
    }
    else
    {
        N->parent->right = Y;
    }

    Y->left = N;
    N->parent = Y;
}

void Dictionary::RightRotate(Node *N)
{
    Node *Y = N->left;

    N->left = Y->right;
    if (Y->right != nil) {
        Y->right->parent = N;
    }
    Y->parent = N->parent;
    if (N->parent == nil)
    {
        root = Y;
    }
    else if (N == N->parent->right)
    {
        N->parent->right = Y;
    }
    else
    {
        N->parent->left = Y;
    }

    Y->right = N;
    N->parent = Y;
}

void Dictionary::RB_InsertFixUp(Node *N)
{
    while (N->parent->color == RED)
    {
        // std::cout << "Fixing node: " << N->key << ", Parent: " << N->parent->key << std::endl; // Debug
        if (N->parent == N->parent->parent->left)
        {
            Node *Y = N->parent->parent->right;
            if (Y->color == RED)
            {
                // std::cout << "Case 1: Recoloring" << std::endl;
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
                if (N == nil)
                    break;
            }
            else
            {
                if (N == N->parent->right)
                {
                    // std::cout << "Case 2: Left Rotate" << std::endl;
                    N = N->parent;
                    LeftRotate(N);
                }
                // std::cout << "Case 3: Right Rotate" << std::endl;
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                RightRotate(N->parent->parent);
            }
        }
        else
        {
            Node *Y = N->parent->parent->left;
            if (Y->color == RED)
            {
                // std::cout << "Case 4: Recoloring" << std::endl;
                N->parent->color = BLACK;
                Y->color = BLACK;
                N->parent->parent->color = RED;
                N = N->parent->parent;
            }
            else
            {
                if (N == N->parent->left)
                {
                    // std::cout << "Case 5: Right Rotate" << std::endl;
                    N = N->parent;
                    RightRotate(N);
                }
                // std::cout << "Case 6: Left Rotate" << std::endl;
                N->parent->color = BLACK;
                N->parent->parent->color = RED;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node *u, Node *v)
{
    if (u->parent == nil)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    // if (v != nil)
    // {
    //     v->parent = u->parent;
    // }
    //u = nullptr;
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node *N)
{
    while (N != root && N->color == BLACK)
    {
        if (N == N->parent->left)
        {
            Node *W = N->parent->right;
            if (W->color == RED)
            {
                W->color = BLACK;
                N->parent->color = RED;
                LeftRotate(N->parent);
                W = N->parent->right;
            }
            if (W->left->color == BLACK && W->right->color == BLACK)
            {
                W->color = RED;
                N = N->parent;
            }
            else
            {
                if (W->right->color == BLACK)
                {
                    W->left->color = BLACK;
                    W->color = RED;
                    RightRotate(W);
                    W = N->parent->right;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->right->color = BLACK;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else
        {
            Node *W = N->parent->left;
            if (W->color == RED)
            {
                W->color = BLACK;
                N->parent->color = RED;
                RightRotate(N->parent);
                W = N->parent->left;
            }
            if (W->right->color == BLACK && W->left->color == BLACK)
            {
                W->color = RED;
                N = N->parent;
            }
            else
            {
                if (W->left->color == BLACK)
                {
                    W->right->color = BLACK;
                    W->color = RED;
                    LeftRotate(W);
                    W = N->parent->left;
                }
                W->color = N->parent->color;
                N->parent->color = BLACK;
                W->left->color = BLACK;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = BLACK;
}

void Dictionary::RB_Delete(Node *N)
{
    Node *Y = N;
    Node *X;
    int y_original = Y->color;
    if (N->left == nil)
    {
        X = N->right;
        RB_Transplant(N, N->right);
    }
    else if (N->right == nil)
    {
        X = N->left;
        RB_Transplant(N, N->left);
    }
    else
    {
        Y = findMin(N->right);
        y_original = Y->color;
        X = Y->right;
        if (Y->parent == N)
        {
            X->parent = Y;
        }
        else
        {
            RB_Transplant(Y, Y->right);
            Y->right = N->right;
            Y->right->parent = Y;
        }
        RB_Transplant(N, Y);
        Y->left = N->left;
        Y->left->parent = Y;
        Y->color = N->color;
    }

    if (y_original == BLACK)
    {
        RB_DeleteFixUp(X);
    }
}

// ACCESS FUNCTIONS
int Dictionary::size() const
{
    return num_pairs;
}

bool Dictionary::contains(keyType k) const
{
    return (search(root, k) != nil);
}

valType &Dictionary::getValue(keyType k) const
{
    if (contains(k))
    {
        Node *N = search(root, k);
        return N->val;
    }
    else
    {
        throw std::logic_error("Dictionary Error: getValue() called on non-existent key");
    }
}

bool Dictionary::hasCurrent() const
{
    return current != nil;
}

keyType Dictionary::currentKey() const
{
    if (!hasCurrent())
    {
        throw std::logic_error("Dictionary Error: currentKey() called on undefined current iterator");
    }
    return current->key;
}

valType &Dictionary::currentVal() const
{
    if (!hasCurrent())
    {
        throw std::logic_error("Dictionary Error: currentVal() called on undefined current iterator");
    }
    return current->val;
}

// Manipulation

void Dictionary::clear()
{
    postOrderDelete(root);
    current = nil;
    root = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v)
{
    Node *y = nil;
    Node *x = root;

    while (x != nil)
    {
        y = x;
        if (k < x->key)
        {
            x = x->left;
        }
        else if (k > x->key) {
            x = x->right;
        }
        else
        {
            x->val = v;
            return;
        }
    }
    Node *z = new Node(k, v);
    z->parent = y;
    if (y == nil)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }

    z->left = nil;
    z->right = nil;
    z->color = RED;
    num_pairs++;

    RB_InsertFixUp(z);
}

void Dictionary::remove(keyType k)
{
    Node *z = search(root, k);
    if (z == nil) {
        return;
    }
    if (current == z) {
        current = nil;
    }
    
    RB_Delete(z);
    delete z;
    num_pairs--;
}

void Dictionary::begin()
{
    if (root != nil)
    {
        current = findMin(root);
    }
}

void Dictionary::end()
{
    if (root != nil)
    {
        current = findMax(root);
    }
}

void Dictionary::next()
{
    if (!hasCurrent())
    {
        throw std::logic_error("Dictionary Error: next() called on undefined current");
    }
    current = findNext(current);
}

void Dictionary::prev()
{
    if (!hasCurrent())
    {
        throw std::logic_error("Dictionary Error: prev() called on undefined current");
    }
    current = findPrev(current);
}

// Other functions

std::string Dictionary::to_string() const
{
    std::string s = "";
    inOrderString(s, root);
    return s;
}

std::string Dictionary::pre_string() const
{
    std::string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary &D) const
{
    if (to_string().length() != D.to_string().length())
    {
        return false;
    }
    return to_string() == D.to_string();
}

std::ostream &operator<<(std::ostream &stream, Dictionary &D)
{
    stream << D.to_string();
    return stream;
}

bool operator==(const Dictionary &A, const Dictionary &B)
{
    return A.equals(B);
}

Dictionary &Dictionary::operator=(const Dictionary &D)
{
    if (this == &D)
    {
        return *this;
    }

    clear();
    preOrderCopy(D.root, D.nil);
    num_pairs = D.num_pairs;
    return *this;
}
