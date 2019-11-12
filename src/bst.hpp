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
    // helper function for insert
    Node<T>* insertHelper(T data, Node<T>* node);
    // helper function for inorder traversal
    void inorderHelper(std::vector<T>* vec, Node<T>* node);
    // helper function for preorder traversal
    void preorderHelper(std::vector<T>* vec, Node<T>* node);
    // helper function for postorder traversal
    void postorderHelper(std::vector<T>* vec, Node<T>* node);
    // helper function for remove
    Node<T> *getParent(T val);
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
Node<T>* BST<T>::insertHelper(T new_data, Node<T>* node)
{
    // Base case, node is null, create new node and return its address.
    if(node == NULL)
    {
        Node<T>* tmp = new Node<T>;
        tmp->set_data(new_data);
        tmp->set_left(NULL);
        tmp->set_right(NULL);

        node_count++;

        return tmp;
    }
    // By checking if data is exclusively less than or greater than
    // current node, duplicates will be skipped
    else if(new_data < node->get_data())
    {
        node->set_left(insertHelper(new_data, node->get_left()));
    }
    else if(new_data > node->get_data())
    {
        node->set_right(insertHelper(new_data, node->get_right()));
    }
    else
    {
        std::cout << "Duplicate nodes are not allowed." << std::endl;
    }
    // If no insertion happens, return starting node so that we don't get undefined c++ behavior
    // this is the same as doing nothing.
    return node;
    
}

template<class T>
void BST<T>::insert(T new_data)
{
    root = insertHelper(new_data, root);
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    if(root == NULL)
    {
        return NULL;
    }

    Node<T>* node = root;
    while(node != NULL)
    {
        // Value found, return node pointer
        if(node->get_data() == val)
        {
            return node;
        }
        // Target less than node, search left child
        else if(val < node->get_data())
        {
            node = node->get_left();
        }
        // Target greater than node, search right child.
        else
        {
            node = node->get_right();
        }
    }
    // value not found
    return NULL;
}

template<class T>
Node<T> *BST<T>::getParent(T val)
{
    // If tree is empty or only contains one node return NULL
    if(root == NULL || (root->get_left() == NULL && root->get_right() == NULL))
    {
        return NULL;
    }

    Node<T>* node = root;
    Node<T>* parentTmp;

    while(node != NULL)
    {
        parentTmp = node;
        // Target less than node, search left child
        if(val < node->get_data())
        {
            node = node->get_left();
        }
        // Target greater than node, search right child.
        else if(val > node->get_data())
        {
            node = node->get_right();
        }

        if(node->get_data() == val)
        {
            return parentTmp;
        }
    }
    // value not found
    return NULL;
}

// Remove could be implemented with more recursion, similar to insertion.
template<class T>
void BST<T>::remove(T val)
{
    Node<T>* target = search(val);
    Node<T>* temp;

    //Case 1, node doesn't exist in tree
    if(target == NULL)
    {
        return;
    }
    // if target found, get target's parent.
    // getParent could be implemented in a modified version of the search function to prevent
    // having to walk the tree multiple times (once for getParent and once for search.)
    Node<T>* targetParent = getParent(val);
    
    // Case 2, node is leaf
    if(target->get_left() == NULL && target->get_right() == NULL)
    {
        if(target != root)
        {
            // If target is left child, parent sets left node to null, else set right node to null.
            targetParent->get_left() == target ? targetParent->set_left(NULL) : targetParent->set_right(NULL);
        }
        else
        {
            root = NULL;
        }
        
        node_count--;
        delete(target);
    } 
    // Case 3a, target has only left child.
    else if(target->get_left() != NULL && target->get_right() == NULL)
    {
        if(target != root)
        {
            // Need to keep track of which child matches the target so parent can update properly.
            // If target is left child, parent sets left node to left grandchild.
            targetParent->get_left() == target ?
                targetParent->set_left(target->get_left()) : targetParent->set_right(target->get_left());
        }
        else
        {
            root = root->get_left();
        }
        
        node_count--;
        delete(target);
    }
    // Case 3b, target has only right child.
    else if(target->get_right() != NULL && target->get_left() == NULL)
    {
        if(target != root)
        {
            // If target is left child, parent sets left node to right grandchild.
            targetParent->get_left() == target ?
                targetParent->set_left(target->get_right()) : targetParent->set_right(target->get_right());
        }
        else
        {
            root = root->get_right();
        }
        
        node_count--;
        delete(target);
    }
    // Case 4, target has two children.
    else if(target->get_left() != NULL && target->get_right() != NULL)
    {
        // Find maximum of left subtree
        Node<T>* maxParent = target;
        Node<T>* maxNode = target->get_left();
    
        while(maxNode->get_right() != NULL)
        {
            // Set parent to maxNode before updating maxNode, this way parent will always be
            // available for fixing-up pointers.
            maxParent = maxNode;
            maxNode = maxNode->get_right();            
        }

        T tempData = maxNode->get_data();
        // Set copy maxNode data into target node
        target->set_data(tempData);

        // Delete maxNode
        // Can only have a maximum of one left child since this is the maximum node.
        if(maxNode->get_left() != NULL)
        {
            if(maxNode != root)
            {
                maxParent->get_left() == maxNode ?
                    maxParent->set_left(maxNode->get_left()) : maxParent->set_right(maxNode->get_left());
            }
            else
            {
                root = root->get_left();
            }
            
            node_count--;
            delete(maxNode);
        }
        else if(maxNode->get_left() == NULL && maxNode->get_right() == NULL)
        {
                // Handle case for no children. No need to check if maxNode == root because that case is
                // handled above.
                maxParent->get_left() == maxNode ?
                    maxParent->set_left(NULL) : maxParent->set_right(NULL);
            
            node_count--;
            delete(maxNode);         
        }
    }
}

template<class T>
int BST<T>::get_size()
{
    return node_count;
}