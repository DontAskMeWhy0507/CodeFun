#include <bits/stdc++.h>

using namespace std;


int MAX_SIZE = 7;   
int EMPTY = -1; // only push non-negative values
vector<int> hash_table(MAX_SIZE, EMPTY);

void insert(int x) {
    int hash = x % MAX_SIZE;
    while (hash_table[hash] != EMPTY) {
        hash = (hash + 1) % MAX_SIZE;
    }
    hash_table[hash] = x;
}

int find(int x) {
    int hash = x % MAX_SIZE;
    while (hash_table[hash] != EMPTY) {
        if (hash_table[hash] == x) return hash;
        hash = (hash + 1) % MAX_SIZE;
    }
    return -1;
}

void del(int x) {
    int i = find(x);
    if (i < 0) return;
    int j = i + 1;
    while (hash_table[j] != EMPTY) {
        int hash_ = hash_table[j] % MAX_SIZE;
        if (hash_ <= i) {
            hash_table[i] = hash_table[j];
            i = j;
        }
        j = (j + 1) % MAX_SIZE;
    }
    hash_table[i] = EMPTY;
}


int main() {
    insert(3);
    insert(10);
    insert(17);
    insert(24);
    insert(6);
    
    for (auto i : hash_table) cout << i << " ";
    cout << endl;
    
    
    if (find(10) >= 0) {
        cout << "found 10" ;
    }
    else cout << "not found 10";
    cout << endl;
    
    del(10);
    if (find(10) < 0) cout << "10 deleted\n";
    
    cout << endl;
    if (find(17) >= 0) cout << "found 17" ;
    else cout << "not found 17";
    cout << endl;
    for (auto i : hash_table) cout << i << " ";
    cout << endl;
    
    del(17);
    if (find(17) < 0) cout << " 17 deleted" ;
    cout << endl;
    
    for (auto i : hash_table) cout << i << " ";
    cout << endl;
    
}

Search entries or author
