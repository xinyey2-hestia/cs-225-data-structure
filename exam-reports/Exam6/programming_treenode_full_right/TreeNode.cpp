#include "TreeNode.h"

// Your function here

TreeNode *makeFullRight(int n) {
int count = 1;
TreeNode* root = new TreeNode(1,NULL,NULL);
makehelper(count,n,root);

return root;
}

void makehelper(int count, int n, TreeNode* subroot){
  if (count>=n)
  return;
  TreeNode* templeft = new TreeNode(++count,NULL,NULL);
  subroot->left_ = templeft;
  TreeNode* tempright = new TreeNode(++count,NULL,NULL);
  subroot->right_ = tempright;
  makehelper(count,n,subroot->right_);

}

// Methods and functions we provide following.
// You should not need to edit this code.

TreeNode::TreeNode(int data, TreeNode *left, TreeNode *right) :
    data_(data), left_(left), right_(right) {}

TreeNode::~TreeNode() {
    if (left_ != NULL)
        delete left_;
    if (right_ != NULL)
        delete right_;
}

bool equal(TreeNode *n1, TreeNode *n2) {
    if (n1 == NULL)
        return n2 == NULL;

    if (n2==NULL)
        return false;

    return (n1->getData() == n2->getData() &&
            equal(n1->getLeft(),n2->getLeft()) &&
            equal(n1->getRight(),n2->getRight()));
}

int TreeNode::getData() const {
    return data_;
}

TreeNode *TreeNode::getLeft() const {
    return left_;
}

TreeNode *TreeNode::getRight() const {
    return right_;
}
