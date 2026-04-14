#include <cstdlib>
#include <vector>
#include "gtest/gtest.h"
#include "sorting.h"
#include "rapidcheck/gtest.h"
#include "test_helpers.h"

TEST(MakeSortedTests, SimpleSortSortedArray) {
    /*
     * Check that we can sort an array that is already sorted.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[7] = {1, 2, 3, 4, 5, 6, 7};
    make_sorted(array, 7);
    for (int i = 0; i < 7; i++)
    {
        EXPECT_EQ(i + 1, array[i]);
    }
}

TEST(MakeSortedTests, SimpleSortReverseSortedArray) {
    /*
     * Check that we can sort an array that is reverse sorted order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[7] = {-1, 0, 7, 23, 46, 81, 99};
    int array_sorted[7] = {-1, 0, 7, 23, 46, 81, 99};
    make_sorted(array, 7);
    for (int i = 0; i < 7; i++)
    {
        EXPECT_EQ(array[7], array_sorted[i]);
    }
}


TEST(MakeSortedTests, SimpleSortAverageArray) {
    /*
     * Check that we can sort an array where the elements in it are in random order.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[10] = {23, 25, 3, 77, 29, 9, 2, -5, -12, 6};
    int array_sorted[10] = {-12, -5, 2, 3, 6, 9, 23, 25, 29, 77};
    //int* sorted = get_sorted for the get sorted tests.
    // array[values.size()], then call copy vector to array for get sorted tests
    make_sorted(array, 10);
    for (int i = 0; i < 10; i++)
    {
        EXPECT_EQ(array_sorted[i], array[i]);
    }
}

TEST(MakeSortedTests, SimpleSortArrayWithDuplicates) {
    /*
     * Check that we can sort an array where there are duplicate elements in it.
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[11] = {2, 17, 90, 85, -1, 2, 90, 8, 17, 11, 2};
    int array_sorted[11] = {-1, 2, 2, 2, 8, 11, 17, 17, 85, 90, 90};
    make_sorted(array, 11);
    for (int i = 0; i < 11; i++)
    {
        EXPECT_EQ(array_sorted[i], array[i]);
    }
}

RC_GTEST_PROP(MakeSortedTests,
              PropertyAfterSortingValuesAreInAscendingOrder,
              ( std::vector<int> values)
) {
    /* Test that after sorting an array, the values are in ascending order
     * Don't forget to free any memory that was dynamically allocated as part of your test.
     */
    int array[values.size()] = malloc(sizeof(int) * values.size());
    copy_vector_to_array(values, array);
    make_sorted(array, values.size());

    RC_ASSERT(elements_in_vector_and_array_are_same(values, array));

    for (int i = 1; i < values.size(); i++)
    {
        // check that the current value is >= the previous value
        RC_ASSERT(array[i] >= array[i - 1]);
    }
    free(array);
}
