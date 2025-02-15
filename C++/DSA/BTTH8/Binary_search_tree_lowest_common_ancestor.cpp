  
vector <Node*> find_ancestor (Node* root, int v) {
    vector <Node*> res;
    while (root) {
        res.push_back(root);
        if (root->data == v) return res;
        if (root->data > v) root = root->left;
        else root = root->right;
    }
    return res;
}

Node *lca(Node *root, int v1,int v2) {
    vector <Node*> a1 = find_ancestor(root, v1);
    vector <Node*> a2 = find_ancestor(root, v2);
    Node* res = NULL;
    for (int i = 0; i < min(a1.size(), a2.size()); i++) {
        if (a1[i] == a2[i]) res = a1[i];
        else break;
    }
    return res;    
}