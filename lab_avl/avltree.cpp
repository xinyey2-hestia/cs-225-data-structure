/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <iostream>
template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
typename AVLTree<K,V>::Node *& AVLTree<K,V>::findiop(Node*& root){
  if (root==NULL||root->right==NULL) return root;

  return findiop(root->right);
}
template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}



template <class K, class V>
int AVLTree<K, V>::height(Node* subtree){
  if (subtree==NULL)
  return -1;

  return subtree->height;
}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
     t->height = max(height(t->left), height(t->right))+1;
     t = temp;
     t->height = max(height(t->left), height(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    Node* temp  = t->left;
    t->left = temp->right;
    temp->right =t;
    t->height = max(height(t->left), height(t->right))+1;
    t = temp;
    t->height = max(height(t->left), height(t->right))+1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance = height(subtree->right) - height(subtree->left);


    if (balance==-2){
      int leftbalance = height(subtree->left->right) - height(subtree->left->left);
      if (leftbalance==-1)
      rotateRight(subtree);
      else
      rotateLeftRight(subtree);
    }

    if (balance==2){
      int leftbalance = height(subtree->right->right) - height(subtree->right->left);
      if (leftbalance==1) rotateLeft(subtree);
      else
      rotateRightLeft(subtree);
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);

}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree==NULL){
    subtree = new Node(key,value);

  }

    else if (subtree->key<key){
    insert(subtree->right, key, value);
    rebalance(subtree);
  }

    else if (subtree->key>key){
    insert (subtree->left,key,value);
    rebalance(subtree);
}

subtree->height = max(height(subtree->left),height(subtree->right))+1;
}




template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);


}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);

        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right,key);

        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            subtree = NULL;
            return;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here

            Node* &temp = findiop(subtree->left);

            swap (subtree, temp);

            remove(subtree->left,key);

        } else {
            /* one-child remove */
            // your code here
            if (subtree->left!=NULL){
                Node* &temp = subtree->left;
                swap (subtree,temp);
                temp = NULL;

            }
            else{
              Node* &temp = subtree->right;
              swap (subtree,temp);
              temp = NULL;

            }
        }

      subtree->height = max(height(subtree->left),height(subtree->right))+1;
       // your code here
    }


}
