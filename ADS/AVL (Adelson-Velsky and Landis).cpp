// #include <bits/stdc++.h>

// AVL Tree is a self-balancing binary search tree where the difference between heights of left and right subtrees cannot be more than one for all nodes.
// A AVL Tree can be used as a HEAP
// Insertion - Deletion - Searching - O(log n)
// getMin - getMax - O(log n)
// getHeight - rotations - O(1)

#include <iostream>
using namespace std;

class AVL
{
private:
    int height = 1;
    AVL *left = nullptr, *right = nullptr;

public:
    int val;
    AVL(int val = 0, AVL *left = nullptr, AVL *right = nullptr) : val(val), left(left), right(right) {}

    int getHeight(AVL *node)
    {
        if (!node)
            return 0;
        return node->height;
    }

    int getScore(AVL *node)
    {
        if (!node)
            return 0;
        return this->getHeight(node->left) - this->getHeight(node->right);
    }

    //   O   --> node
    //    \ 
    //     O --> newRoot
    //    / \
    //       O

    AVL *rotateLeft(AVL *node)
    {
        AVL *newRoot = node->right;
        node->right = newRoot->left; // Order matters
        newRoot->left = node;        // Order matters
        node->height = max(this->getHeight(node->left), this->getHeight(node->right)) + 1;
        newRoot->height = max(this->getHeight(newRoot->left), this->getHeight(newRoot->right)) + 1;
        return newRoot;
    }

    //     O   --> node
    //    /
    //   O  --> newRoot
    //  / \
    // O   O

    AVL *rotateRight(AVL *node)
    {
        AVL *newRoot = node->left;
        node->left = newRoot->right; // Order matters
        newRoot->right = node;       // Order matters
        node->height = max(this->getHeight(node->left), this->getHeight(node->right)) + 1;
        newRoot->height = max(this->getHeight(newRoot->left), this->getHeight(newRoot->right)) + 1;
        return newRoot;
    }

    AVL *insert(AVL *node, int val)
    {
        if (!node)
            return new AVL(val);
        if (val < node->val)
            node->left = this->insert(node->left, val);
        else if (val > node->val)
            node->right = this->insert(node->right, val);
        else
            return node; // Duplicate values are not allowed

        node->height = max(this->getHeight(node->left), this->getHeight(node->right)) + 1;
        int score = this->getScore(node);

        // Left Left Case
        if (score > 1 && val < node->left->val)
            return this->rotateRight(node);

        // Left Right Case
        if (score > 1 && val > node->left->val)
        {
            node->left = this->rotateLeft(node->left);
            return this->rotateRight(node);
        }

        // Right Right Case
        if (score < -1 && val > node->right->val)
            return this->rotateLeft(node);

        // Right Left Case
        if (score < -1 && val < node->right->val)
        {
            node->right = this->rotateRight(node->right);
            return this->rotateLeft(node);
        }

        return node;
    }

    AVL *_delete(AVL *root, int val)
    {
        if (!root)
            return root;
        if (val < root->val)
            root->left = this->_delete(root->left, val);
        else if (val > root->val)
            root->right = this->_delete(root->right, val);
        else
        {
            if (!root->left || !root->right)
            {
                AVL *temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    delete root; // Optional: free memory
                    return nullptr;
                }
                else
                    *root = *temp; // Copy the contents of the non-empty child
            }
            else
            {
                AVL *temp = root->right;
                while (temp->left)
                    temp = temp->left;                               // Find the inorder successor
                root->val = temp->val;                               // Copy the inorder successor's value
                root->right = this->_delete(root->right, temp->val); // Delete the inorder successor
            }

            if (!root)
                return root; // If the tree had only one node, return

            root->height = max(this->getHeight(root->left), this->getHeight(root->right)) + 1;
            int score = this->getScore(root);

            // Left Left Case
            if (score > 1 && this->getScore(root->left) >= 0)
                return this->rotateRight(root);

            // Left Right Case
            if (score > 1 && this->getScore(root->left) < 0)
            {
                root->left = this->rotateLeft(root->left);
                return this->rotateRight(root);
            }

            // Right Right Case
            if (score < -1 && this->getScore(root->right) <= 0)
                return this->rotateLeft(root);

            // Right Left Case
            if (score < -1 && this->getScore(root->right) > 0)
            {
                root->right = this->rotateRight(root->right);
                return this->rotateLeft(root);
            }
        }
        return root;
    }

    // USING AVL TREE AS MIN and MAX HEAP

    AVL *getMAX(AVL *root)
    {
        if (!root)
            return nullptr;
        while (root->right)
            root = root->right;
        return root;
    }

    AVL *getMIN(AVL *root)
    {
        if (!root)
            return nullptr;
        while (root->left)
            root = root->left;
        return root;
    }

    friend void getNMIN(AVL *root, int N); // get N - Min values

    void sortedInorder(AVL *root) // can also be used for sorting
    {
        if (!root)
            return;
        this->sortedInorder(root->left);
        cout << root->val << " ";
        this->sortedInorder(root->right);
    }
};

// make a count pointer while doing inorder traversel and when the count is equal to N stop further iteration
int _count = 0;
void getNMIN(AVL *root, int N)
{
    if (!root || _count >= N)
        return;
    getNMIN(root->left, N);
    if (_count >= N)
        return;
    cout << root->val << " ";
    _count++;
    getNMIN(root->right, N);
}

int main()
{
    cout << "AVL Tree Implementation" << endl;
    int insert[] = {10, 20, 30, 40, 50, 25};
    int del[] = {10, 20, 30, 40, 50, 25};
    AVL *root = nullptr;
    for (int i = 0; i < 6; i++)
    {
        root = root->insert(root, insert[i]);
        cout << "Inserted: " << insert[i] << endl;
    }
    cout << "Max: " << root->getMAX(root)->val << endl;
    cout << "Min: " << root->getMIN(root)->val << endl;
    cout << "Sorted Inorder: ";
    root->sortedInorder(root);
    cout << endl;
    cout << "N - Min: ";
    _count = 0; // reset count for N - Min
    getNMIN(root, 3);
    cout << endl; // get N - Min values
    cout << "Deleting nodes..." << endl;
    for (int i = 0; i < 6; i++)
    {
        root = root->_delete(root, del[i]);
        cout << "Deleted: " << del[i] << endl;
    }
    cout << "Max: " << root->getMAX(root)->val << endl;
    cout << "Min: " << root->getMIN(root)->val << endl;
    return 0;
}