/**
 * @file
 * @brief [Dynamic Array](https://en.wikipedia.org/wiki/Dynamic_array)
 *
 * @details
 * The list_array is the implementation of list represented using array.
 * We can perform basic CRUD operations as well as other operations like sorting
 * etc.
 *
 * ### Algorithm
 * It implements various method like insert, sort, search etc. efficiently.
 * You can select the operation and methods will do the rest work for you.
 * You can insert element, sort them in order, search efficiently, delete values
 * and print the list.
 */

#include <array>     /// for std::array
#include <cassert>   /// for assert
#include <iostream>  /// for io operations
#include <map>
#include <string>

#define INSERT_BRANCHES        7
#define BINARY_SEARCH_BRANCHES 5

std::map<std::string, bool> branchCoverageMapBinarySearch = {
    {"BinarySearch_1", false}, {"BinarySearch_2", false},
    {"BinarySearch_3", false}, {"BinarySearch_4", false},
    {"BinarySearch_5", false},
};

std::map<std::string, bool> branchCoverageMapInsert = {
    {"Insert_1", false}, {"Insert_2", false}, {"Insert_3", false},
    {"Insert_4", false}, {"Insert_5", false}, {"Insert_6", false},
    {"Insert_7", false},
};

/**
 * @namespace data_structures
 * @brief Algorithms with data structures
 */
namespace data_structures {
/**
 * @namespace list_array
 * @brief Functions for [Dynamic
 * Array](https://en.wikipedia.org/wiki/Dynamic_array) algorithm
 */
namespace list_array {
/**
 * @brief Structure of List with supporting methods.
 */
template <uint64_t N>
struct list {
    std::array<uint64_t, N> data{};  // Array that implement list
    uint64_t top = 0;                // Pointer to the last element
    bool isSorted = false;           // indicator whether list is sorted or not
    /**
     * @brief Search an element in the list using binarySearch.
     * @param dataArr list
     * @param first pointer to the first element in the remaining list
     * @param last pointer to the last element in the remaining list
     * @param val element that will be searched
     * @return index of element in the list if present else -1
     */
    uint64_t BinarySearch(const std::array<uint64_t, N> &dataArr,
                          const uint64_t &first, const uint64_t &last,
                          const uint64_t &val) {
        // If both pointer cross each other means no element present in the list
        // which is equal to the val
        if (last < first) {
            branchCoverageMapBinarySearch["BinarySearch_1"] = true;
            return -1;
        }
        uint64_t mid = (first + last) / 2;
        // check whether current mid pointer value is equal to element or not
        if (dataArr[mid] == val) {
            branchCoverageMapBinarySearch["BinarySearch_2"] = true;
            return mid;
        }
        // if current mid value is greater than  element we have to search in
        // first half
        else if (val < dataArr[mid]) {
            branchCoverageMapBinarySearch["BinarySearch_3"] = true;
            return (BinarySearch(dataArr, first, mid - 1, val));
        }
        // if current mid value is greater than  element we have to search in
        // second half
        else if (val > dataArr[mid]) {
            branchCoverageMapBinarySearch["BinarySearch_4"] = true;
            return (BinarySearch(dataArr, mid + 1, last, val));
        }

        std::cerr << __func__ << ":" << __LINE__ << ": Undefined condition\n";
        branchCoverageMapBinarySearch["BinarySearch_5"] = true;
        return -1;
    }

    /**
     * @brief Search an element using linear search
     * @param dataArr list
     * @param val element that will be searched
     * @return index of element in the list if present else -1
     */
    uint64_t LinearSearch(const std::array<uint64_t, N> &dataArr,
                          const uint64_t &val) const {
        // Going through each element in the list
        for (uint64_t i = 0; i < top; i++) {
            if (dataArr[i] == val) {
                return i;  // element found at ith index
            }
        }
        // element is not present in the list
        return -1;
    }

    /*
     * @brief Parent function of binarySearch and linearSearch methods
     * @param val element that will be searched
     * @return index of element in the list if present else -1
     */
    uint64_t search(const uint64_t &val) {
        uint64_t pos;  // pos variable to store index value of element.
        // if list is sorted, binary search works efficiently else linear search
        // is the only option
        if (isSorted) {
            pos = BinarySearch(data, 0, top - 1, val);
        } else {
            pos = LinearSearch(data, val);
        }
        // if index is equal to -1 means element does not present
        // else print the index of that element
        if (pos != -1) {
            std::cout << "\nElement found at position : " << pos;
        } else {
            std::cout << "\nElement not found";
        }
        // return the index of element or -1.
        return pos;
    }

    /**
     * @brief Sort the list
     * @returns void
     */
    void sort() {
        // Going through each element in the list
        for (uint64_t i = 0; i < top; i++) {
            uint64_t min_idx = i;  // Initialize the min variable
            for (uint64_t j = i + 1; j < top; j++) {
                // check whether any element less than current min value
                if (data[j] < data[min_idx]) {
                    min_idx = j;  // update index accordingly
                }
            }
            // swap min value and element at the ith index
            std::swap(data[min_idx], data[i]);
        }
        // mark isSorted variable as true
        isSorted = true;
    }

    /**
     * @brief Insert the new element in the list
     * @param val element that will be inserted
     * @returns void
     */
    void insert(const uint64_t &val) {
        // overflow check
        if (top == N) {
            branchCoverageMapInsert["Insert_1"] = true;
            std::cout << "\nOverflow";
            return;
        }
        // if list is not sorted, insert at the last
        // otherwise place it to correct position
        if (!isSorted) {
            branchCoverageMapInsert["Insert_2"] = true;
            data[top] = val;
            top++;
        } else {
            uint64_t pos = 0;  // Initialize the index variable
            branchCoverageMapInsert["Insert_3"] = true;
            // Going through each element and find correct position for element
            for (uint64_t i = 0; i < top - 1; i++) {
                // check for the correct position
                branchCoverageMapInsert["Insert_4"] = true;
                if (data[i] <= val && val <= data[i + 1]) {
                    branchCoverageMapInsert["Insert_5"] = true;
                    pos = i + 1;  // assign correct pos to the index var
                    break;        // to get out from the loop
                }
            }
            // if all elements are smaller than the element
            if (pos == 0) {
                branchCoverageMapInsert["Insert_6"] = true;
                pos = top - 1;
            }
            // shift all element to make a room for new element
            for (uint64_t i = top; i > pos; i--) {
                branchCoverageMapInsert["Insert_7"] = true;
                data[i] = data[i - 1];
            }
            top++;  // Increment the value of top.
            data[pos] =
                val;  // Assign the value to the correct index in the array
        }
    }

    /**
     * @brief To remove the element from the list
     * @param val element that will be removed
     * @returns void
     */
    void remove(const uint64_t &val) {
        uint64_t pos = search(val);  // search the index of the value
        // if search returns -1, element does not present in the list
        if (pos == -1) {
            std::cout << "\n Element does not present in the list ";
            return;
        }
        std::cout << "\n"
                  << data[pos] << " deleted";  // print the appropriate message
        // shift all the element 1 left to fill vacant space
        for (uint64_t i = pos; i < top; i++) {
            data[i] = data[i + 1];
        }
        top--;  // decrement the top variable to maintain last index
    }

    /**
     * @brief Utility function to print array
     * @returns void
     */
    void show() {
        // Going through each element in the list
        std::cout << '\n';
        for (uint64_t i = 0; i < top; i++) {
            std::cout << data[i] << " ";  // print the element
        }
    }
};  // structure list
}  // namespace list_array
}  // namespace data_structures

/**
 * @brief Test implementations
 * @returns void
 */
static void test() {
    data_structures::list_array::list<50> L;

    // Insert testing
    L.insert(11);
    L.insert(12);
    assert(L.top == 2);
    L.insert(15);
    L.insert(10);
    L.insert(12);
    L.insert(20);
    L.insert(18);
    assert(L.top == 7);
    L.show();  // To print the array

    // Remove testing
    L.remove(12);  // Remove Duplicate value in the list
    L.remove(15);  // Remove the existing value in the list
    assert(L.top == 5);
    L.remove(50);  // Try to remove the non-existing value in the list
    assert(L.top == 5);

    // LinearSearch testing
    assert(L.search(11) == 0);  // search for the existing element
    assert(L.search(12) == 2);
    assert(L.search(50) == -1);  // search for the non-existing element

    // Sort testing
    L.sort();
    assert(L.isSorted == true);
    L.show();

    // BinarySearch testing
    assert(L.search(11) == 1);  // search for the existing element
    assert(L.search(12) == 2);
    assert(L.search(50) == -1);  // search for the non-existing element
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main() {
    test();  // Execute the tests
    int coveredBranchesBinarySearch = 0;
    int coveredBranchesInsert = 0;
    for (const auto &pair : branchCoverageMapBinarySearch) {
        if (pair.second) {
            coveredBranchesBinarySearch++;
        }
    }

    for (const auto &pair : branchCoverageMapInsert) {
        if (pair.second) {
            coveredBranchesInsert++;
        }
    }

    double coveragePercentageBinarySearch =
        static_cast<double>(coveredBranchesBinarySearch) /
        BINARY_SEARCH_BRANCHES * 100;
    std::cout << "Branch Coverage in Binary Search: "
              << coveragePercentageBinarySearch << "%" << std::endl;

    double coveragePercentageInsert =
        static_cast<double>(coveredBranchesInsert) / INSERT_BRANCHES * 100;
    std::cout << "Branch Coverage in Insert: " << coveragePercentageInsert
              << "%" << std::endl;

    double totalCoveragePercentage =
        static_cast<double>(
            (coveredBranchesBinarySearch + coveredBranchesInsert)) /
        (BINARY_SEARCH_BRANCHES + INSERT_BRANCHES) * 100;
    std::cout << "Total Branch Coverage across Both: "
              << totalCoveragePercentage << "%" << std::endl;

    return 0;
}
