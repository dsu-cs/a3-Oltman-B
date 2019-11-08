#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include <vector>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // helper function for insert(T)
    Node<T>* insertHelper(T data, Node<T>* node);
    // helper function for inorder traversal
    void inorderHelper(std::vector<T>* vec, Node<T>* node);
    // helper function for preorder traversal
    void preorderHelper(std::vector<T>* vec, Node<T>* node);
    // helper function for postorder traversal
    void postorderHelper(std::vector<T>* vec, Node<T>* node);
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

// Traversal functions handle the recursion and also adding node data to the vector.
template<class T>
void BST<T>::inorderHelper(std::vector<T>* vec, Node<T>* node)
{
    if(node == NULL)
    {
        return;
    }

    inorderHelper(vec, node->get_left());
    vec->push_back(node->get_data());
    inorderHelper(vec, node->get_right());
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    inorderHelper(vec, root);

    return vec;
}

// Traversal functions handle the recursion and also adding node data to the vector.
template<class T>
void BST<T>::preorderHelper(std::vector<T>* vec, Node<T>* node)
{
    if(node == NULL)
    {
        return;
    }

    vec->push_back(node->get_data());
    preorderHelper(vec, node->get_left());
    preorderHelper(vec, node->get_right());
}

template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    preorderHelper(vec, root);

    return vec;
}

// Traversal functions handle the recursion and also adding node data to the vector.
template<class T>
void BST<T>::postorderHelper(std::vector<T>* vec, Node<T>* node)
{
    if(node == NULL)
    {
        return;
    }

    postorderHelper(vec, node->get_left());
    postorderHelper(vec, node->get_right());
    vec->push_back(node->get_data());
}

template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    postorderHelper(vec, root);

    return vec;
}

template<class T>
Node<T>* BST<T>::insertHelper(T data, Node<T>* node)
{
    if(node == NULL)
    {
        Node<T>* tmp = new Node<T>;
        tmp->set_data(data);
        tmp->set_left(NULL);
        tmp->set_right(NULL);

        return tmp;
    }
    else if(data < node->get_data())
    {
        node->set_left(insertHelper(data, node->get_left()));
    }
    else if(data > node->get_data())
    {
        node->set_right(insertHelper(data, node->get_right()));
    }
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = insertHelper(new_data, root);
}


template<class T>
Node<T> *BST<T>::search(T val)
{

}



template<class T>
void BST<T>::remove(T val)
{

}



template<class T>
int BST<T>::get_size()
{

}