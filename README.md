# Report for Assignment 1

## Project chosen

Name: The Algorithms - C++

URL: [https://github.com/TheAlgorithms/C-Plus-Plus](https://github.com/TheAlgorithms/C-Plus-Plus)

Number of lines of code and the tool used to count it: 31 KLOC (Measured using lizard)

Programming language: C++

## Coverage measurement

### Existing tool

To measure the coverage we used lcov. To execute it we made a small script that generates coverage information and
automatically creates an HTML report.

generate_coverage.sh:
```
lcov -c -d ./ -o coverage.run
genhtml -o ./html/ coverage.run
```

For lcov to be able to capture coverage data we had to add some flags in the CMakeLists.txt:
```
include(CodeCoverage.cmake)
APPEND_COVERAGE_COMPILER_FLAGS()
```

After setting up cmake with `cmake .`, compiling the project using `make` and running the tests with `ctest`, the 
coverage report can be generated using generate_coverage.sh.

Because lcov coverage can only go up when re-running tests, never down, we made a small script that removes all
existing coverage data, called reset_coverage.sh.

Coverage results:

![Full Old Coverage report](report_img/Full_old_report.png)

### Your own coverage tool

#### <u>Alejandro Guerena Gonzalez</u>

###### bool Tree234::TryRightRotate(Node *parent, Node *to_child)
###### void Tree234::Traverse(Node *node)

**Link to commit:** [Commit hash: d7ea02e](https://github.com/Flipkaboom/SEP_not_Pandas/commit/d7ea02e9e652519af13ef7e286294ecd4b9af172)

This commit shows the map data structure used to track if statements in 2 branches for both functions are executed. This is displayed through the added functions print_right_rotate_coverage() and print_traverse_coverage() to show if these branches are hit.

**Link to commit:** [Commit hash: efaa53a](https://github.com/Flipkaboom/SEP_not_Pandas/commit/efaa53a35da0d582ba89821849abc86e4caeabf8)

This commit shows the addition of checking the 'invisible' else branch of TryRightRotate() function, in the case that neither of the two brances are executed. Totaling to 3 branches in the TryRightRotate() functino being checked, and 2 branches in Traverse() function

![Coverage results](old_coverage_img/Alejandro_old_coverage.png)

This image shows the coverage of TryRightRotate() and Traverse() functions through print_right_rotate_coverage() and print_traverse_coverage() before adding tests and improving the coverage.

#### <u>Flip Grim</u>

###### void _insert(int &x, int k)
###### void _erase(int &x, int k)

**Link to commit:** [Commit hash: fed6d31](https://github.com/Flipkaboom/SEP_not_Pandas/commit/fed6d31446934a74023aabfbc42e1225d4c13b01)

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

**Link to commit:** [Commit hash: d7ea02e](https://github.com/Flipkaboom/SEP_not_Pandas/commit/d7ea02e9e652519af13ef7e286294ecd4b9af172)

This commit shows the addition of test_right_rotate() and test_traverse() which indirectly calls the functions described above, since they are private functions. The test_right_rotate() function inserts values to a 234-tree data structure and depending on the structure of the tree, when deleting a node (calling the Remove() function) it may internally call the test_right_rotate() function. Two different tree structures are created in this test function to meet the conditions of the branches when trying to rotate the tree right.

The test_traverse() function is far more simple, though similarly the Traverse(Node *node) function is private therefore the Traverse() public function is utilized to indirectly call the helper function. The Traverse(Node *node) function has two branches: one where the tree is empty and the other when it is not, therefore these two cases are implemented in the test_traverse() function.

**Link to commit:** [Commit hash: efaa53a](https://github.com/Flipkaboom/SEP_not_Pandas/commit/efaa53a35da0d582ba89821849abc86e4caeabf8)

The structure of the tree was changed here, by inserting different nodes to the tree to meet the conditions of the additional 'invisible' branch that was added.

![Old Coverage results](old_coverage_img/Alejandro_old_coverage.png)
![New Coverage results](new_coverage_img/Alejandro_new_coverage.png)

![Old Coverage report](report_img/Alejandro_old_report.png)
![New Coverage report](report_img/Alejandro_new_report.png)

The line coverage within tree_234.cpp was 56.2%. After the introduction of my tests I implemented, the line coverage improved to 78.7%. The branch coverage improved from 69.4% to 90.6% within the tree_234.cpp file. The coverage was improved with the addition of my tests because all the statements within bool Tree234::TryRightRotate(Node *parent, Node *to_child) and void Tree234::Traverse(Node *node) functions were executed atleast once. Prior to the introduction of the tests, none of the lines within these functions were executed.

#### <u>Flip Grim</u>

###### static void test()

**Link to commit:** [Commit hash: 617aba4](https://github.com/Flipkaboom/SEP_not_Pandas/commit/617aba47ea0e95fd84f0a6e69d90bea0f382e552)

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

Old coverage result:

![Full Old Coverage report](report_img/Full_old_report.png)

New coverage result:

![Full New Coverage report](report_img/Full_new_report.png)

## Statement of individual contributions

#### <u>Flip Grim</u>
- Finding github project to use
- Figuring out how to setup/compile project
- Setup testing
- Setup coverage measurement
- Instrumenting and improving coverage for data_structures/treap.cpp
- Adding overall coverage results to readme

<Write what each group member did>
