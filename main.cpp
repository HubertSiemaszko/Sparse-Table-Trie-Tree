#include<iostream>

struct Node {
    int key;
    Node** children;


    Node(int key_)
        : key(-1), children(nullptr)
    {
    }

    ~Node() {

    }


    void makeChildren(int size) {
        if (!children) {
            children = new Node * [size];
            for (int i = 0; i < size; ++i)
                children[i] = nullptr;
        }
    }
};

class Trie {
private:
    int n, k;
    Node* root = nullptr;



public:
    Trie(int n_, int k_)
        : n(n_), k(k_)
    {
        root = new Node(0);
    }
    ~Trie() {
        delete root;
    }
    bool find(int key) {
        if (!root) {
            return false;
        }
        if (root->key == key) {
            return true;
        }
        if (root->key==-1 && !root->children)
            return false;
        Node* current = root;
        int rem = key % n;
        int quo = key / n;
        while (true) {
            int capacity = (current == root ? n : k);
            int idx = rem;
            if (!current->children)
                return false;
            if (current->children[idx] == nullptr) {
                return false;
            }
            current = current->children[idx];

            if (current->key == key)
                return true;

            if (current->key==-1)
                return false;


            rem = quo % k;
            quo = quo / k;
        }

    }

    void insert(int key) {
        if (find(key)) {
            printf("%d exist\n", key);
            return;
        }
        if (!root) {
            root = new Node(0);
            root->key = key;
            return;
        }
        if (root->key==-1) {
            root->key = key;
            return;
        }

        Node* current = root;
        int rem = key % n;
        int quo = key / n;

        while (true) {
            int capacity = (current == root ? n : k);
            current->makeChildren(capacity);
            int idx = rem;

            if (current->children[idx] == nullptr) {
                current->children[idx] = new Node(0);
                current = current->children[idx];
                current->key = key;
                return;
            }
            if (current->children[idx]->key==-1) {
                current = current->children[idx];
                current->key = key;
                return;
            }
            current = current->children[idx];


            rem = quo % k;
            quo = quo / k;
        }

    }

    void deleteNode(int key) {
        if (!find(key)) {
            printf("%d not exist\n", key);
            return;
        }

        if (root->key == key) {
            root->key = -1;
            return;
        }

        Node* nodes[32]; int idxs[32], depth = 0;
        Node* cur = root;
        int rem = key % n;
        int quo = key / n;

        while (true) {
            int capacity = (cur == root ? n : k);
            int idx = rem;
            if (!cur->children)
                return;
            nodes[depth] = cur;
            idxs[depth] = idx;
            depth++;
            cur = cur->children[idx];
            if (cur->key == key) break;
            if (cur->key==-1)
                return;
            rem = quo % k;
            quo /= k;
        }

        Node* parent = nodes[depth - 1];
        int   parentIdx = idxs[depth - 1];

        bool hasChild = (cur->children != nullptr);
        if (hasChild) {
            hasChild = false;
            for (int i = 0; i < k; ++i) {
                if (cur->children[i]) {
                    hasChild = true;
                    break;
                }
            }
        }
        if (!hasChild) {
            delete parent->children[parentIdx];
            parent->children[parentIdx] = nullptr;
        }
        else {

            Node* leftCandidate = cur;
            while (true) {
                bool went = false;
                if (leftCandidate->children) {
                    for (int i = 0; i < k; i++) {
                        if (leftCandidate->children[i]) {
                            nodes[depth] = leftCandidate;
                            idxs[depth] = i;
                            depth++;
                            leftCandidate = leftCandidate->children[i];
                            went = true;
                            break;
                        }
                    }
                }
                if (!went) break;
            }
            cur->key = leftCandidate->key;
            Node* leftCandidateParent = nodes[depth - 1];
            int   leftCandidateParentIdx = idxs[depth - 1];
            delete leftCandidateParent->children[leftCandidateParentIdx];
            leftCandidateParent->children[leftCandidateParentIdx] = nullptr;
        }
    }


    void findInfo(int key) {
        if (find(key)) {
            printf("%d exist\n", key);
        }
        else {
            printf("%d not exist\n", key);
        }
    }

    void inorder(Node* cur) {
        if (!cur) return;
        int ar = (cur == root ? n : k);

        if(cur->key != -1) {
            printf("%d ", cur->key);
        }
        if (cur->children) {
            for (int i = 0; i < ar; ++i)
                inorder(cur->children[i]);
        }
    }

    void printInorder() {
        inorder(root);
        printf("\n");
    }

};


int main() {
    int commands, minimum, maximum, n, k;
    scanf_s("%d", &commands);
    scanf_s("%d", &minimum);
    scanf_s("%d", &maximum);
    scanf_s("%d", &n);
    scanf_s("%d", &k);
    Trie trie(n, k);
    int com = getchar();
    while (com == '\n' || com == '\r') com = getchar();
    if (com != EOF) ungetc(com, stdin);


    for (int i = 0; i < commands; ++i) {
        char cmd = '\0';
        int  key;
        scanf_s(" %c", &cmd, 1);

        switch (cmd) {
            case 'I':
                scanf_s("%d", &key);
                trie.insert(key);
                break;
            case 'D':
                scanf_s("%d", &key);
                trie.deleteNode(key);
                break;
            case 'L':
                scanf_s("%d", &key);
                trie.findInfo(key);
                break;
            case 'P':
                trie.printInorder();
                break;
        }
    }






    return 0;
}