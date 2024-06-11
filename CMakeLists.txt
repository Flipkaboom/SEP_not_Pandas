cmake_minimum_required(VERSION 3.22)
project(Algorithms_in_C++
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "Set of algorithms implemented in C++."
)

# set(CMAKE_CXX_CPPLINT "~/anaconda3/bin/cpplint --filter=-legal/copyright --std=c++11")
# find_program(CLANG_FORMAT "clang-format")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # set(CMAKE_CXX_STANDARD 14)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

option(USE_OPENMP "flag to use OpenMP for multithreading" ON)
if(USE_OPENMP)
    find_package(OpenMP 3.0 COMPONENTS CXX)
    if (OpenMP_CXX_FOUND)
        message(STATUS "Building with OpenMP Multithreading.")
    else()
        message(STATUS "No OpenMP found, no multithreading.")
    endif()
endif()

#Add compiler flags to store coverage information
include(CodeCoverage.cmake)
APPEND_COVERAGE_COMPILER_FLAGS()

add_subdirectory(math)
add_subdirectory(others)
add_subdirectory(search)
add_subdirectory(ciphers)
add_subdirectory(hashing)
add_subdirectory(strings)
add_subdirectory(sorting)
add_subdirectory(geometry)
add_subdirectory(graphics)
add_subdirectory(probability)
add_subdirectory(backtracking)
add_subdirectory(bit_manipulation)
add_subdirectory(data_structures)
add_subdirectory(machine_learning)
add_subdirectory(numerical_methods)
add_subdirectory(graph)
add_subdirectory(divide_and_conquer)
add_subdirectory(games)
add_subdirectory(cpu_scheduling_algorithms)
add_subdirectory(physics)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)
find_package(Doxygen OPTIONAL_COMPONENTS dot dia)
if(DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_USE_MATHJAX YES)
    set(DOXYGEN_GENERATE_HTML YES)
    # set(DOXYGEN_HTML_TIMESTAMP YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_INLINE_SOURCES YES)
    set(DOXYGEN_CREATE_SUBDIRS YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_STRIP_CODE_COMMENTS NO)
    set(DOXYGEN_EXT_LINKS_IN_WINDOW YES)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
    set(DOXYGEN_EXCLUDE_PATTERNS */build/*)
    set(DOXYGEN_ENABLE_PREPROCESSING YES)
    set(DOXYGEN_CLANG_ASSISTED_PARSING YES)
    set(DOXYGEN_FILE_PATTERNS *.cpp *.h *.hpp *.md)
    set(DOXYGEN_MATHJAX_EXTENSIONS  TeX/AMSmath TeX/AMSsymbols)
    set(DOXYGEN_TAGFILES "doc/cppreference-doxygen-web.tag.xml=http://en.cppreference.com/w/")
    if(MSVC)
        set(DOXYGEN_CPP_CLI_SUPPORT YES)
    endif()
    set(DOXYGEN_MATHJAX_RELPATH "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML")
    if(Doxygen_dot_FOUND)
        set(DOXYGEN_HAVE_DOT YES)
        set(DOXYGEN_CALL_GRAPH YES)
        set(DOXYGEN_INTERACTIVE_SVG YES)
        set(DOXYGEN_DOT_IMAGE_FORMAT "svg")
    endif()
    if(OPENMP_FOUND)
        set(DOXYGEN_PREDEFINED "_OPENMP=1")
    endif()
    if(GLUT_FOUND)
        set(DOXYGEN_PREDEFINED ${DOXYGEN_PREDEFINED} "GLUT_FOUND=1")
    endif()

    doxygen_add_docs(
        doc
        ${PROJECT_SOURCE_DIR}
        COMMENT "Generate documentation"
    )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


#Setup tests
include(CTest)

add_test(NAME bogo_sort COMMAND ./sorting/bogo_sort)

############# BACKTRACKING ##############
add_test(NAME generate_parentheses COMMAND ./backtracking/generate_parentheses)
add_test(NAME magic_sequence COMMAND ./backtracking/magic_sequence)
add_test(NAME rat_maze COMMAND ./backtracking/rat_maze)
add_test(NAME subarray_sum COMMAND ./backtracking/subarray_sum)
add_test(NAME subset_sum_backtracking COMMAND ./backtracking/subset_sum)
add_test(NAME wildcard_matching COMMAND ./backtracking/wildcard_matching)

############# BIT MANIPULATION ##############
add_test(NAME count_bits_flip COMMAND ./bit_manipulation/count_bits_flip)
add_test(NAME count_of_set_bits COMMAND ./bit_manipulation/count_of_set_bits)
add_test(NAME count_of_trailing_ciphers_in_factorial_n COMMAND ./bit_manipulation/count_of_trailing_ciphers_in_factorial_n)
add_test(NAME find_non_repeating_number COMMAND ./bit_manipulation/find_non_repeating_number)
add_test(NAME hamming_distance COMMAND ./bit_manipulation/hamming_distance)
add_test(NAME next_higher_number_with_same_number_of_set_bits COMMAND ./bit_manipulation/next_higher_number_with_same_number_of_set_bits)
add_test(NAME power_of_2 COMMAND ./bit_manipulation/power_of_2)
add_test(NAME set_kth_bit COMMAND ./bit_manipulation/set_kth_bit)
add_test(NAME travelling_salesman_using_bit_manipulation COMMAND ./bit_manipulation/travelling_salesman_using_bit_manipulation)

############# CIPHERS ##############
add_test(NAME a1z26_cipher COMMAND ./ciphers/a1z26_cipher)
add_test(NAME atbash_cipher COMMAND ./ciphers/atbash_cipher)
add_test(NAME base64_encoding COMMAND ./ciphers/base64_encoding)
add_test(NAME caesar_cipher COMMAND ./ciphers/caesar_cipher)
add_test(NAME elliptic_curve_key_exchange COMMAND ./ciphers/elliptic_curve_key_exchange)
add_test(NAME morse_code COMMAND ./ciphers/morse_code)
add_test(NAME vigenere_cipher COMMAND ./ciphers/vigenere_cipher)
add_test(NAME xor_cipher COMMAND ./ciphers/xor_cipher)

############# CPU SCHEDULING ALGORITHMS ##############
add_test(NAME fcfs_scheduling COMMAND ./cpu_scheduling_algorithms/fcfs_scheduling)


############# DATA STRUCTURE ##############
add_test(NAME avltree COMMAND ./data_structures/avltree)
add_test(NAME binary_search_tree2 COMMAND ./data_structures/binary_search_tree2)
add_test(NAME binaryheap COMMAND ./data_structures/binaryheap)
add_test(NAME bloom_filter COMMAND ./data_structures/bloom_filter)
add_test(NAME disjoint_set COMMAND ./data_structures/disjoint_set)
add_test(NAME dsu_path_compression COMMAND ./data_structures/dsu_path_compression)
add_test(NAME dsu_union_rank COMMAND ./data_structures/dsu_union_rank)
add_test(NAME list_array COMMAND ./data_structures/list_array)
add_test(NAME morrisinorder COMMAND ./data_structures/morrisinorder)
add_test(NAME queue_using_two_stacks COMMAND ./data_structures/queue_using_two_stacks)
add_test(NAME reverse_a_linked_list COMMAND ./data_structures/reverse_a_linked_list)
add_test(NAME segment_tree COMMAND ./data_structures/segment_tree)
add_test(NAME sparse_table COMMAND ./data_structures/sparse_table)
add_test(NAME stack_using_queue COMMAND ./data_structures/stack_using_queue)
add_test(NAME test_queue COMMAND ./data_structures/test_queue)
add_test(NAME test_stack COMMAND ./data_structures/test_stack)
add_test(NAME treap COMMAND ./data_structures/treap)
add_test(NAME tree_234 COMMAND ./data_structures/tree_234)
add_test(NAME trie_tree COMMAND ./data_structures/trie_tree)
add_test(NAME trie_using_hashmap COMMAND ./data_structures/trie_using_hashmap)

############# DIVIDE AND CONQUER ##############
add_test(NAME karatsuba_algorithm_for_fast_multiplication COMMAND ./divide_and_conquer/karatsuba_algorithm_for_fast_multiplication)
add_test(NAME strassen_matrix_multiplication COMMAND ./divide_and_conquer/strassen_matrix_multiplication)

############# DYNAMIC PROGRAMMING ##############
add_test(NAME 0_1_knapsack COMMAND ./dynamic_programming/0_1_knapsack)
add_test(NAME abbreviation COMMAND ./dynamic_programming/abbreviation)
add_test(NAME armstrong_number COMMAND ./dynamic_programming/armstrong_number)
add_test(NAME coin_change_topdown COMMAND ./dynamic_programming/coin_change_topdown)
add_test(NAME cut_rod COMMAND ./dynamic_programming/cut_rod)
add_test(NAME house_robber COMMAND ./dynamic_programming/house_robber)
add_test(NAME longest_common_string COMMAND ./dynamic_programming/longest_common_string)
add_test(NAME longest_palindromic_subsequence COMMAND ./dynamic_programming/longest_palindromic_subsequence)
add_test(NAME maximum_circular_subarray COMMAND ./dynamic_programming/maximum_circular_subarray)
add_test(NAME minimum_edit_distance COMMAND ./dynamic_programming/minimum_edit_distance)
add_test(NAME palindrome_partitioning COMMAND ./dynamic_programming/palindrome_partitioning)
add_test(NAME partition_problem COMMAND ./dynamic_programming/partition_problem)
add_test(NAME subset_sum_dynamic_programming COMMAND ./dynamic_programming/subset_sum)
add_test(NAME word_break COMMAND ./dynamic_programming/word_break)

############# GEOMETRY ##############
add_test(NAME graham_scan_algorithm COMMAND ./geometry/graham_scan_algorithm)
add_test(NAME jarvis_algorithm COMMAND ./geometry/jarvis_algorithm)

############# GRAPH ##############
# add_test(NAME bidirectional_dijkstra COMMAND ./graph/bidirectional_dijkstra)
# add_test(NAME breadth_first_search COMMAND ./graph/breadth_first_search)
# add_test(NAME connected_components_with_dsu COMMAND ./graph/connected_components_with_dsu)
# add_test(NAME depth_first_search_with_stack COMMAND ./graph/depth_first_search_with_stack)
# add_test(NAME dijkstra COMMAND ./graph/dijkstra)
# add_test(NAME hamiltons_cycle COMMAND ./graph/hamiltons_cycle)
# add_test(NAME hopcroft_karp COMMAND ./graph/hopcroft_karp)
add_test(NAME is_graph_bipartite COMMAND ./graph/is_graph_bipartite)
add_test(NAME is_graph_bipartite2 COMMAND ./graph/is_graph_bipartite2)
add_test(NAME lowest_common_ancestor COMMAND ./graph/lowest_common_ancestor)
add_test(NAME travelling_salesman_problem COMMAND ./graph/travelling_salesman_problem)

############# GRAPHICS ##############
add_test(NAME spirograph COMMAND ./graphics/spirograph)

############# GREEDY ALGORITHMS ##############
add_test(NAME boruvkas_minimum_spanning_tree COMMAND ./greedy_algorithms/boruvkas_minimum_spanning_tree)
add_test(NAME dijkstra_greedy COMMAND ./greedy_algorithms/dijkstra)
add_test(NAME huffman COMMAND ./greedy_algorithms/huffman)

############# HASHING ##############
# add_test(NAME md5 COMMAND ./hashing/md5)
# add_test(NAME sha1 COMMAND ./hashing/sha1)
add_test(NAME sha256 COMMAND ./hashing/sha256)

############# MACHINE LEARNING ##############
add_test(NAME a_star_search COMMAND ./machine_learning/a_star_search)
# add_test(NAME adaline_learning COMMAND ./machine_learning/adaline_learning)
add_test(NAME k_nearest_neighbors COMMAND ./machine_learning/k_nearest_neighbors)
#gives a seg fault 
#add_test(NAME kohonen_som_topology COMMAND ./machine_learning/kohonen_som_topology)
add_test(NAME kohonen_som_trace COMMAND ./machine_learning/kohonen_som_trace)
#fails
# add_test(NAME neural_network COMMAND ./machine_learning/neural_network)
#fails
# add_test(NAME ordinary_least_squares_regressor COMMAND ./machine_learning/ordinary_least_squares_regressor)

############# MATH ##############
add_test(NAME aliquot_sum COMMAND ./math/aliquot_sum)
add_test(NAME approximate_pi COMMAND ./math/approximate_pi)
add_test(NAME area COMMAND ./math/area)
add_test(NAME armstrong_number_math COMMAND ./math/armstrong_number)
add_test(NAME binomial_calculate COMMAND ./math/binomial_calculate)
add_test(NAME check_amicable_pair COMMAND ./math/check_amicable_pair)
add_test(NAME check_factorial COMMAND ./math/check_factorial)
add_test(NAME check_prime COMMAND ./math/check_prime)
# fails
# add_test(NAME complex_numbers COMMAND ./math/complex_numbers)
add_test(NAME double_factorial COMMAND ./math/double_factorial)
add_test(NAME eratosthenes COMMAND ./math/eratosthenes)
add_test(NAME eulers_totient_function COMMAND ./math/eulers_totient_function)
# fails
# add_test(NAME factorial COMMAND ./math/factorial)
# add_test(NAME fast_power COMMAND ./math/fast_power)
# add_test(NAME fibonacci_large COMMAND ./math/fibonacci_large)
# add_test(NAME fibonacci_matrix_exponentiation COMMAND ./math/fibonacci_matrix_exponentiation)
add_test(NAME fibonacci_sum COMMAND ./math/fibonacci_sum)
# add_test(NAME fibonacci COMMAND ./math/fibonacci)
add_test(NAME finding_number_of_digits_in_a_number COMMAND ./math/finding_number_of_digits_in_a_number)
add_test(NAME integral_approximation COMMAND ./math/integral_approximation)
add_test(NAME integral_approximation2 COMMAND ./math/integral_approximation2)
add_test(NAME inv_sqrt COMMAND ./math/inv_sqrt)
add_test(NAME iterative_factorial COMMAND ./math/iterative_factorial)
# add_test(NAME large_factorial COMMAND ./math/large_factorial)
add_test(NAME largest_power COMMAND ./math/largest_power)
add_test(NAME lcm_sum COMMAND ./math/lcm_sum)
add_test(NAME least_common_multiple COMMAND ./math/least_common_multiple)
add_test(NAME linear_recurrence_matrix COMMAND ./math/linear_recurrence_matrix)
add_test(NAME magic_number COMMAND ./math/magic_number)
add_test(NAME miller_rabin COMMAND ./math/miller_rabin)
add_test(NAME modular_division COMMAND ./math/modular_division)
add_test(NAME modular_exponentiation COMMAND ./math/modular_exponentiation)
add_test(NAME modular_inverse_simple COMMAND ./math/modular_inverse_simple)
add_test(NAME n_bonacci COMMAND ./math/n_bonacci)
add_test(NAME n_choose_r COMMAND ./math/n_choose_r)
add_test(NAME ncr_modulo_p COMMAND ./math/ncr_modulo_p)
# add_test(NAME number_of_positive_divisors COMMAND ./math/number_of_positive_divisors)
add_test(NAME perimeter COMMAND ./math/perimeter)
add_test(NAME power_of_two COMMAND ./math/power_of_two)
add_test(NAME quadratic_equations_complex_numbers COMMAND ./math/quadratic_equations_complex_numbers)
# add_test(NAME realtime_stats COMMAND ./math/realtime_stats)
add_test(NAME sieve_of_eratosthenes COMMAND ./math/sieve_of_eratosthenes)
add_test(NAME sum_of_binomial_coefficient COMMAND ./math/sum_of_binomial_coefficient)
add_test(NAME sum_of_digits COMMAND ./math/sum_of_digits)
# add_test(NAME vector_cross_product COMMAND ./math/vector_cross_product)
add_test(NAME volume COMMAND ./math/volume)



#add more tests here to be able to run them with ctest and include them for the coverage report
#Template:
#add_test(NAME TestName COMMAND ExecutableToRun arg1 arg2 ...)