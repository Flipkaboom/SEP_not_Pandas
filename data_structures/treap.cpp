/**
 * @file
 * @brief A balanced binary search tree (BST) on the basis of binary search tree
 * and heap: the [Treap](https://en.wikipedia.org/wiki/Treap) algorithm
 * implementation
 *
 * @details
 * Implementation of the treap data structre
 *
 * Support operations including insert, erase, and query (the rank of specified
 * element or the element ranked x) as the same as BST
 *
 * But these operations take O(log N) time, since treap keeps property of heap
 * using rotate operation, and the desired depth of the tree is O(log N).
 * There's very little chance that it will degenerate into a chain like BST
 *
 * @author [Kairao ZHENG](https://github.com/fgmn)
 */

#include <array>     /// For array
#include <cassert>   /// For assert
#include <iostream>  /// For IO operations
#include <map>

std::map<std::string, bool> insert_branches_covered = {{"branch_1", false},
                                                       {"branch_2", false},
                                                       {"branch_3", false},
                                                       {"branch_4", false},
                                                       {"branch_5", false},
                                                       {"branch_6", false}};

std::map<std::string, bool> erase_branches_covered = {{"branch_1", false},
                                                      {"branch_2", false},
                                                      {"branch_3", false},
                                                      {"branch_4", false},
                                                      {"branch_5", false},
                                                      {"branch_6", false}};

/**
 * @namespace
 * @brief Data Structures
 */
namespace data_structures {
/**
 * @namespace
 * @brief Functions for the [Treap](https://en.wikipedia.org/wiki/Treap)
 * algorithm implementation
 */
namespace treap {
const int maxNode = 1e5 + 5;  ///< maximum number of nodes
/**
 * @brief Struct representation of the treap
 */
struct Treap {
    int root = 0;      ///< root of the treap
    int treapCnt = 0;  ///< Total number of current nodes in the treap
    std::array<int, maxNode> key = {};       ///< Node identifier
    std::array<int, maxNode> priority = {};  ///< Random priority
    std::array<std::array<int, 2>, maxNode> childs = {
        {}};  ///< [i][0] represents the
              ///< left child of node i, and
              ///[i][1] represents the right
    std::array<int, maxNode> cnt =
        {};  ///< Maintains the subtree size for ranking query
    std::array<int, maxNode> size = {};  ///< The number of copies per node
    /**
     * @brief Initialization
     */
    Treap() : treapCnt(1) {
        priority[0] = INT32_MAX;
        size[0] = 0;
    }
    /**
     * @brief Update the subtree size of the node
     * @param x The node to update
     */
    void update(int x) {
        size[x] = size[childs[x][0]] + cnt[x] + size[childs[x][1]];
    }
    /**
     * @brief Rotate without breaking the property of BST
     * @param x The node to rotate
     * @param t 0 represent left hand, while 1 right hand
     */
    void rotate(int &x, int t) {
        int y = childs[x][t];
        childs[x][t] = childs[y][1 - t];
        childs[y][1 - t] = x;
        // The rotation will only change itself and its son nodes
        update(x);
        update(y);
        x = y;
    }
    /**
     * @brief Insert a value into the specified subtree (internal method)
     * @param x Insert into the subtree of node x (Usually x=root)
     * @param k Key to insert
     */
    void _insert(int &x, int k) {
        if (x) {
            insert_branches_covered["branch_1"] = true;
            if (key[x] == k) {
                insert_branches_covered["branch_2"] = true;
                cnt[x]++;
            }  // If the node already exists, the number of copies is ++
            else {
                insert_branches_covered["branch_3"] = true;
                int t = (key[x] < k);  // Insert according to BST properties
                _insert(childs[x][t], k);
                // After insertion, the heap properties are retained by rotation
                if (priority[childs[x][t]] < priority[x]) {
                    insert_branches_covered["branch_4"] = true;
                    rotate(x, t);
                }
                else {
                    insert_branches_covered["branch_5"] = true;
                }
            }
        } else {  // Create a new node
            insert_branches_covered["branch_6"] = true;
            x = treapCnt++;
            key[x] = k;
            cnt[x] = 1;
            priority[x] = rand();  // Random priority
            childs[x][0] = childs[x][1] = 0;
        }
        update(x);
    }
    /**
     * @brief Erase a value from the specified subtree (internal method)
     * @param x Erase from the subtree of node x (Usually x=root)
     * @param k Key to erase
     */
    void _erase(int &x, int k) {
        if (key[x] == k) {
            erase_branches_covered["branch_1"] = true;
            if (cnt[x] > 1) {
                erase_branches_covered["branch_2"] = true;
                cnt[x]--;
            }  // If the node has more than one copy, the number of copies --
            else {
                erase_branches_covered["branch_3"] = true;
                if (childs[x][0] == 0 && childs[x][1] == 0) {
                    erase_branches_covered["branch_4"] = true;
                    x = 0;
                    return;
                }
                erase_branches_covered["branch_5"] = true;
                // If there are no children, delete and return
                // Otherwise, we need to rotate the sons and delete them
                // recursively
                int t = (priority[childs[x][0]] > priority[childs[x][1]]);
                rotate(x, t);
                _erase(x, k);
            }
        } else {  // Find the target value based on BST properties
            erase_branches_covered["branch_6"] = true;
            _erase(childs[x][key[x] < k], k);
        }
        update(x);
    }
    /**
     * @brief Find the KTH largest value (internal method)
     * @param x Query the subtree of node x (Usually x=root)
     * @param k The queried rank
     * @return The element ranked number k
     */
    int _get_k_th(int &x, int k) {
        if (k <= size[childs[x][0]]) {
            return _get_k_th(childs[x][0], k);
        }
        k -= size[childs[x][0]] + cnt[x];
        if (k <= 0) {
            return key[x];
        }
        return _get_k_th(childs[x][1], k);
    }
    /**
     * @brief Query the rank of specified element (internal method)
     * @param x Query the subtree of node x (Usually x=root)
     * @param k The queried element
     * @return The rank of element k
     */
    int _get_rank(int x, int k) {
        if (!x) {
            return 0;
        }
        if (k == key[x]) {
            return size[childs[x][0]] + 1;
        }
        else if (k < key[x]) {
            return _get_rank(childs[x][0], k);
        }
        else {
            return size[childs[x][0]] + cnt[x] + _get_rank(childs[x][1], k);
        }
    }
    /**
     * @brief Get the predecessor node of element k
     * @param k The queried element
     * @return The predecessor
     */
    int get_predecessor(int k) {
        int x = root, pre = -1;
        while (x) {
            if (key[x] < k) {
                pre = key[x], x = childs[x][1];
            } else {
                x = childs[x][0];
            }
        }
        return pre;
    }
    /**
     * @brief Get the successor node of element k
     * @param k The queried element
     * @return The successor
     */
    int get_next(int k) {
        int x = root, next = -1;
        while (x) {
            if (key[x] > k) {
                next = key[x], x = childs[x][0];
            } else {
                x = childs[x][1];
            }
        }
        return next;
    }
    /**
     * @brief Insert element (External method)
     * @param k Key to insert
     */
    void insert(int k) { _insert(root, k); }
    /**
     * @brief Erase element (External method)
     * @param k Key to erase
     */
    void erase(int k) { _erase(root, k); }
    /**
     * @brief Get the KTH largest value (External method)
     * @param k The queried rank
     * @return The element ranked number x
     */
    int get_k_th(int k) { return _get_k_th(root, k); }
    /**
     * @brief Get the rank of specified element (External method)
     * @param k The queried element
     * @return The rank of element k
     */
    int get_rank(int k) { return _get_rank(root, k); }
};
}  // namespace treap
}  // namespace data_structures

/**
 * @brief Self-test implementations
 * @returns void
 */
static void test() {
    data_structures::treap::Treap mTreap;  ///< Treap object instance

    mTreap.insert(1);
    mTreap.insert(2);
    mTreap.insert(3);
    assert(mTreap.get_k_th(2) == 2);
    mTreap.insert(4);
    mTreap.insert(5);
    mTreap.insert(6);
    assert(mTreap.get_next(4) == 5);
    mTreap.insert(7);
    assert(mTreap.get_predecessor(7) == 6);
    mTreap.erase(4);
    assert(mTreap.get_k_th(4) == 5);
    assert(mTreap.get_rank(5) == 4);
    mTreap.insert(10);
    assert(mTreap.get_rank(10) == 7);
    assert(mTreap.get_predecessor(10) == 7);

    //Improving coverage for insert and erase
    data_structures::treap::Treap mTreap2;
    mTreap2.insert(1);
    assert(mTreap2.get_next(0) == 1);
    mTreap2.insert(1);
    assert(mTreap2.get_next(0) == 1);
    mTreap2.erase(1);
    assert(mTreap2.get_next(0) == 1);
    mTreap2.erase(1);
    assert(mTreap2.get_next(0) == -1);

    std::cout << "All tests have successfully passed!\n";
}

/**
 * @brief Print coverage results for a single function
 * @param coverage_map Map containing coverage info per branch
 * @param name Name to be printed
 */
static void print_coverage(std::map<std::string, bool> &coverage_map, const std::string &name){
    int covered_count = 0;

    std::cout << "Coverage for " << name << ": " << std::endl;
    for (auto const& branch : coverage_map){
        std::string branch_name = branch.first;
        bool covered = branch.second;
        std::cout << "        " << branch_name << ": " << (covered ? "Covered" : "Not covered") << std::endl;
        if(covered) covered_count++;
    }
    std::cout << "    Total covered: " << covered_count << "/" << coverage_map.size()
                << " (" << ((float)covered_count / coverage_map.size() * 100) << "%)" << std::endl;
}

/**
 * @brief Print coverage information for all modified functions
 */
static void print_coverage_all(){
    print_coverage(insert_branches_covered, "insert");
    print_coverage(erase_branches_covered, "erase");
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // run self-test implementations
    print_coverage_all();
    return 0;
}
