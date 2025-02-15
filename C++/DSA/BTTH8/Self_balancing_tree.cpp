/* Node is defined as :
typedef struct node
{
    int val;
    struct node* left;
    struct node* right;
    int ht;
} node; */


node * insert(node * root,int val){
    if(root == NULL) {
        node *newNode = new node();
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->ht = 0;
        return newNode;
    }
    if(val < root->val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    root->ht = 1 + max(root->left->ht, root->right->ht);
    int balance = root->left->ht - root->right->ht;
    if(balance > 1) {
        if(val < root->left->val) {
            // Left Left Case
            return rightRotate(root);
        } else {
            // Left Right Case
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    } else if(balance < -1) {
        if(val > root->right->val) {
            // Right Right Case
            return leftRotate(root);
        } else {
            // Right Left Case
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}