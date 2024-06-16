/**
 * \file
 * \brief A simple tree implementation using nodes
 *
 * \todo update code to use C++ STL library features and OO structure
 * \warning This program is a poor implementation and does not utilize any of
 * the C++ STL features.
 */
#include <algorithm>  /// for std::max
#include <iostream>   /// for std::cout
#include <queue>      /// for std::queue
#include <map>
#include <string>

#define INSERT_BRANCHES_NUMBER 8
#define DELETENODE_BRANCHES_NUMBER 6

std::map<std::string, bool> insert_branches_covered = {{"branch_1", false},
                                                  {"branch_2", false},
                                                  {"branch_3", false},
                                                  {"branch_4", false},
                                                  {"branch_5", false},
                                                  {"branch_6", false},
                                                  {"branch_7", false},
                                                  {"branch_8", false}};

std::map<std::string, bool> deletenode_branches_covered = {{"branch_1", false},
                                                      {"branch_2", false},
                                                      {"branch_3", false},
                                                      {"branch_4", false},
                                                      {"branch_5", false},
                                                      {"branch_6", false}};

using node = struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
};

/**
 * @brief creates and returns a new node
 * @param[in] data value stored in the node
 * @return newly created node
 */
node *createNode(int data) {
    node *nn = new node();
    nn->data = data;
    nn->height = 0;
    nn->left = nullptr;
    nn->right = nullptr;
    return nn;
}

/**
 * @param[in] root the root of the tree
 * @return height of tree
 */
int height(node *root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + std::max(height(root->left), height(root->right));
}

/**
 * @param[in] root of the tree
 * @return difference between height of left and right subtree
 */
int getBalance(node *root) { return height(root->left) - height(root->right); }

/**
 * @param root of the tree to be rotated
 * @return node after right rotation
 */
node *rightRotate(node *root) {
    node *t = root->left;
    node *u = t->right;
    t->right = root;
    root->left = u;
    return t;
}

/**
 * @param root of the tree to be rotated
 * @return node after left rotation
 */
node *leftRotate(node *root) {
    node *t = root->right;
    node *u = t->left;
    t->left = root;
    root->right = u;
    return t;
}

/**
 * @param root of the tree
 * @returns node with minimum value in the tree
 */
node *minValue(node *root) {
    if (root->left == nullptr) {
        return root;
    }
    return minValue(root->left);
}

/**
 * @brief inserts a new element into AVL tree
 * @param root of the tree
 * @param[in] item the element to be insterted into the tree
 * @return root of the updated tree
 */
node *insert(node *root, int item) {                                                               
    if (root == nullptr) {
        insert_branches_covered["branch_1"] = true;
        return createNode(item);
    }
    if (item < root->data) {
        insert_branches_covered["branch_2"] = true;
        root->left = insert(root->left, item);
    } else {
        insert_branches_covered["branch_3"] = true;
        root->right = insert(root->right, item);
    }
    int b = getBalance(root);
    if (b > 1) {
        if (getBalance(root->left) < 0) {
            insert_branches_covered["branch_5"] = true;
            root->left = leftRotate(root->left);  // Left-Right Case
        }
        insert_branches_covered["branch_4"] = true;
        return rightRotate(root);  // Left-Left Case
    } else if (b < -1) {
        if (getBalance(root->right) > 0) {
            insert_branches_covered["branch_7"] = true;
            root->right = rightRotate(root->right);  // Right-Left Case
        }
        insert_branches_covered["branch_6"] = true;
        return leftRotate(root);  // Right-Right Case
    }
    insert_branches_covered["branch_8"] = true;
    return root;
}

/**
 * @brief removes a given element from AVL tree
 * @param root of the tree
 * @param[in] element the element to be deleted from the tree
 * @return root of the updated tree
 */
node *deleteNode(node *root, int element) {                                                        
    if (root == nullptr) {
        deletenode_branches_covered["branch_1"] = true;
        return root;
    }
    if (element < root->data) {
        deletenode_branches_covered["branch_2"] = true;
        root->left = deleteNode(root->left, element);
    } else if (element > root->data) {
        deletenode_branches_covered["branch_3"] = true;
        root->right = deleteNode(root->right, element);

    } else {
        // Node to be deleted is leaf node or have only one Child
        if (!root->right || !root->left) {
            deletenode_branches_covered["branch_5"] = true;
            node *temp = !root->right ? root->left : root->right;
            delete root;
            return temp;
        }
        deletenode_branches_covered["branch_4"] = true;
        // Node to be deleted have both left and right subtrees
        node *temp = minValue(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    deletenode_branches_covered["branch_6"] = true;
    // Balancing Tree after deletion
    return root;
}

/**
 * @brief calls delete on every node
 * @param root of the tree
 */
void deleteAllNodes(const node *const root) {
    if (root) {
        deleteAllNodes(root->left);
        deleteAllNodes(root->right);
        delete root;
    }
}

/**
 * @brief prints given tree in the LevelOrder
 * @param[in] root of the tree
 */
void levelOrder(node *root) {
    std::queue<node *> q;
    q.push(root);
    while (!q.empty()) {
        root = q.front();
        std::cout << root->data << " ";
        q.pop();
        if (root->left) {
            q.push(root->left);
        }
        if (root->right) {
            q.push(root->right);
        }
    }
}

void print_coverage() {
    int count_insert_branches = 0;
    int count_deletenode_branches = 0;

    for (const auto& pair : insert_branches_covered) {
        if (pair.second)
            count_insert_branches++;
    }

    for (const auto& pair : deletenode_branches_covered) {
        if (pair.second) 
            count_deletenode_branches++;
    }
    std::cout << std::endl;
    std::cout << "In the function insert " << count_insert_branches << "/" << INSERT_BRANCHES_NUMBER << " are covered." << std::endl;
    std::cout << "In the function deleteNode " << count_deletenode_branches << "/" << DELETENODE_BRANCHES_NUMBER << " are covered." << std::endl;
}

/**
 * @brief Main function
 * @returns 0 on exit
 */

void test_left_heavy_for_coverage() {     // created a case when the rotation would need Left-Right so the tree is left heavy
    node *root = nullptr;
    root = deleteNode(root, 1);        // tried to delete the root when it is null to cover first branch in deleteNode
    root = insert(root, 30);
    root = insert(root, 10);
    root = insert(root, 20);

    std::cout << "\nLevelOrder: ";
    levelOrder(root);
    deleteAllNodes(root);
}

void test_del_node_two_subtrees() {     //created a case that deleteNode tries to delete a node with both left and right subtrees
    node *root = nullptr;                       
    root = insert(root, 20);
    root = insert(root, 10);
    root = insert(root, 30);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 35);

    deleteNode(root, 20);               //to cover branch_4 of deleteNode
}

int main() {
    // Testing AVL Tree
    node *root = nullptr;
    int i = 0;
    //for (i = 1; i <= 7; i++) root = insert(root, i);            //the 2 commented lines instead of this will imporve coverage of insert by 2 (brances 2 and 7)
    for (i = 1; i <= 3; i++) root = insert(root, i);
    for (i = 7; i >=4; i--) root = insert(root, i);

    std::cout << "LevelOrder: ";
    levelOrder(root);
    root = deleteNode(root, 1);  // Deleting key with value 1
    std::cout << "\nLevelOrder: ";
    levelOrder(root);
    root = deleteNode(root, 4);  // Deletin key with value 4
    std::cout << "\nLevelOrder: ";
    levelOrder(root);
    deleteAllNodes(root);

    test_left_heavy_for_coverage();
    test_del_node_two_subtrees();

    print_coverage();

    return 0;
}



