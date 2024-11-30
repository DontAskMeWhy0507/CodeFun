/* 
The structure of the node is

typedef struct node
{
    int freq;
    char data;
    node * left;
    node * right;
    
}node;

*/
void decode_huff(node * root, string s) {
    node * current = root;
    for (char c : s) {
        if (c == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr) {
            cout << current->data;
            current = root;
        }
        
        

    }
}