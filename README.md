# Report for Assignment 1

## Project chosen

Name: The Algorithms - C++

URL: [https://github.com/TheAlgorithms/C-Plus-Plus](https://github.com/TheAlgorithms/C-Plus-Plus)

Number of lines of code and the tool used to count it: 31 KLOC (Measured using lizard)

Programming language: C++

## Coverage measurement

### Existing tool

<Inform the name of the existing tool that was executed and how it was executed>

<Show the coverage results provided by the existing tool with a screenshot>

### Your own coverage tool

#### <u>Alejandro Guerena Gonzalez</u>

###### bool Tree234::TryRightRotate(Node *parent, Node *to_child)
###### void Tree234::Traverse(Node *node)

**Link to commit:** [Commit hash: a04e95c](https://github.com/Flipkaboom/SEP_Pandas/commit/a04e95c7e558e7207822ba46c26297e12121c1a8)

This commit shows the map data structure used to track if statements in 2 branches for both functions are executed. This is displayed through the added functions print_right_rotate_coverage() and print_traverse_coverage() to show if these branches are hit.

**Link to commit:** [Commit hash: 7597e65](https://github.com/Flipkaboom/SEP_Pandas/commit/7597e65bcd5c14b6ffb5684cc8244cc290675db0)

This commit shows the addition of checking the 'invisible' else branch of TryRightRotate() function, in the case that neither of the two brances are executed. Totaling to 3 branches in the TryRightRotate() functino being checked, and 2 branches in Traverse() function

![Coverage results](old_coverage_img/Alejandro_old_coverage.png)

This image shows the coverage of TryRightRotate() and Traverse() functions through print_right_rotate_coverage() and print_traverse_coverage() before adding tests and improving the coverage.

#### <u>Flip Grim</u>

###### void _insert(int &x, int k)
###### void _erase(int &x, int k)

**Link to commit:** [Commit hash: 8b0f136](https://github.com/Flipkaboom/SEP_Pandas/commit/8b0f136ebd098611d33d93259d401a125ea277dc)

In this commit, branch coverage measurement is added to the functions listed above, located in
data_structures/treap.cpp. This is done using two maps that map each branch to a boolean value. After running all tests,
the coverage for each branch is printed, then the overall coverage per function is printed.

Results: 

![Coverage results](old_coverage_img/Flip_old_coverage.png)

## Coverage improvement

### Individual tests

#### <u>Alejandro Guerena Gonzalez</u>

###### void test_right_rotate()
###### void test_traverse()

**Link to commit:** [Commit hash: a04e95c](https://github.com/Flipkaboom/SEP_Pandas/commit/a04e95c7e558e7207822ba46c26297e12121c1a8)

This commit shows the addition of test_right_rotate() and test_traverse() which indirectly calls the functions described above, since they are private functions. The test_right_rotate() function inserts values to a 234-tree data structure and depending on the structure of the tree, when deleting a node (calling the Remove() function) it may internally call the test_right_rotate() function. Two different tree structures are created in this test function to meet the conditions of the branches when trying to rotate the tree right.

The test_traverse() function is far more simple, though similarly the Traverse(Node *node) function is private therefore the Traverse() public function is utilized to indirectly call the helper function. The Traverse(Node *node) function has two branches: one where the tree is empty and the other when it is not, therefore these two cases are implemented in the test_traverse() function.

**Link to commit:** [Commit hash: 7597e65](https://github.com/Flipkaboom/SEP_Pandas/commit/7597e65bcd5c14b6ffb5684cc8244cc290675db0)

The structure of the tree was changed here, by inserting different nodes to the tree to meet the conditions of the additional 'invisible' branch that was added.

![Old Coverage results](old_coverage_img/Alejandro_old_coverage.png)
![New Coverage results](new_coverage_img/Alejandro_new_coverage.png)

![Old Coverage report](report_img/Alejandro_old_report.png)
![New Coverage report](report_img/Alejandro_new_report.png)

The line coverage within tree_234.cpp was 56.2%. After the introduction of my tests I implemented, the line coverage improved to 78.7%. The branch coverage improved from 69.4% to 90.6% within the tree_234.cpp file. The coverage was improved with the addition of my tests because all the statements within bool Tree234::TryRightRotate(Node *parent, Node *to_child) and void Tree234::Traverse(Node *node) functions were executed atleast once. Prior to the introduction of the tests, none of the lines within these functions were executed.

#### <u>Flip Grim</u>

###### static void test()

**Link to commit:** [Commit hash: 3cd392c](https://github.com/Flipkaboom/SEP_Pandas/commit/3cd392c7f75dee210900b2e77fc0e31dfc0e76be)

Line coverage results before:

![Old Coverage report](report_img/Flip_old_report.png)

Branch coverage results before:

![Coverage results](old_coverage_img/Flip_old_coverage.png)

Line coverage results after:

![Old Coverage report](report_img/Flip_new_report.png)

Branch coverage results after:

![Coverage results](new_coverage_img/Flip_new_coverage.png)

The original line coverage of treap.cpp was 96.1%. After adding new tests to the test() function the line coverage has
improved to 99.3%.

The original branch coverage (on the instrumented functions) was 10/12 (83.3%) branches reached. After adding the tests
the branch coverages improved to 12/12 (100%).

The treap (the data structure implemented in treap.cpp) supports several of the same element being added to it. When
this happens it will find the identical element already present in the data structure and increase a counter on this
element. This is never tested by the original tests, neither is the code that decreases the counter when a duplicate
element is removed. The added tests add an identical element to an empty treap twice in a row, checking that the element
exists after each addition. The tests then erase that same element twice in a row, checking that it still exists after
the first erase (because there are two of them) and checking that it no longer exists after the second erase.

### Overall

<Provide a screenshot of the old coverage results by running an existing tool (the same as you already showed above)>

<Provide a screenshot of the new coverage results by running the existing tool using all test modifications made by the group>

## Statement of individual contributions

<Write what each group member did>
