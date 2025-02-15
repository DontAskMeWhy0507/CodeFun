Node * insert(Node * root, int data) {
    if (root == nullptr) {
        root = new Node(data);
        return root;
    }
    if (data < root -> data) {
        root -> left = insert(root -> left, data);
    } else {
        root -> right = insert(root -> right,data);
    }

    return root;
}
