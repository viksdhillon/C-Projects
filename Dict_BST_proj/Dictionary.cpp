/***
 * Vik Dhillon
 * vsdhillo
 * 2025 Winter CSE101 PA7
 * Dictionary.cpp
 * File to write Dictionary ADT
 ***/
#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

Dictionary::Node::Node(keyType k, valType v)
{
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary()
{
    nil = new Node("/", 0);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
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
        s += R->key + "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node *R, Node *N)
{
    if (R != N)
    {
        setValue(R->key, R->val);
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
    if (R == nil)
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
    Node *temp = search(root, k);
    if (temp != nil)
    {
        temp->val = v;
        return;
    }
    Node *r = root;
    Node *n = nil;
    while (r != nil)
    {
        n = r;
        if (k < r->key)
        {
            // std::cout << "Key r: " << k << std::endl;
            r = r->left;
        }
        else
        {
            // std::cout << "Key: " << k << std::endl;
            r = r->right;
        }
    }
    Node *N = new Node(k, v);
    N->left = nil;
    N->right = nil;
    if (root == nil)
    {
        root = N;
    }
    else if (k < n->key)
    {
        n->left = N;
    }
    else
    {
        n->right = N;
    }
    N->parent = n;
    num_pairs++;
}

void Dictionary::remove(keyType k)
{
    Node *z = search(root, k);
    if (z == nil)
        return;

    if (z == current)
    {
        current = nil;
    }

    if (z->left == nil)
    {
        Transplant(z, z->right);
    }

    else if (z->right == nil)
    {
        Transplant(z, z->left);
    }

    else
    {
        Node *y = findMin(z->right);

        if (y->parent != z)
        {
            Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
    }

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
    std::string s = "";
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
