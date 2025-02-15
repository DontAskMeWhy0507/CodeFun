    void inorder(Node* root, vector<int> &a){
        if (root == nullptr) return;
        inorder(root->left, a);
        a.push_back(root->data);
        inorder(root->right, a);
    }
     
    bool checkBST(Node* root) {
        vector<int> a;
        inorder(root, a); 
        for (int i = 1; i < a.size(); i++) {
            if (a[i] <= a[i - 1]) return false;
        }   
        return true;
    }